#include "Window.h"

using namespace _0xCC;

bool _0xCC::Window::Create(int x, int y){
	int attr_mask;
	XSizeHints hints;
	XWMHints *startup_state;
	XTextProperty textprop;
	
	auto Xdisplay = wm->GetDisplay();
	auto Xroot = wm->GetRoot();
	auto visual = wm->GetVisual();

	auto cmap = wm->GetColorMap();

	XSetWindowAttributes attr = {0,};
	attr.colormap = cmap;
	attr.background_pixmap = None;
	attr.border_pixmap = None;
	attr.border_pixel = 0;
	attr.event_mask =
		StructureNotifyMask |
		EnterWindowMask |
		LeaveWindowMask |
		ExposureMask |
		ButtonPressMask |
		ButtonReleaseMask |
		OwnerGrabButtonMask |
		KeyPressMask |
		KeyReleaseMask;
	attr.override_redirect  = true;

	attr_mask =
		CWBackPixmap|
		CWColormap|
		CWBorderPixel|
		CWEventMask;

	int sWidth = DisplayWidth(Xdisplay, DefaultScreen(Xdisplay));
	int sHeight = DisplayHeight(Xdisplay, DefaultScreen(Xdisplay));
	if (width == -1)
		width = sWidth;
	if (height == -1)
		height = sHeight;
	if (x == -1) x = sWidth / 2 - width / 2;
	if (y == -1) y = sHeight / 2 - height / 2;

	window_handle = XCreateWindow(Xdisplay,
			Xroot,
			x, y, width, height,
			0,
			visual->depth,
			InputOutput,
			visual->visual,
			attr_mask, &attr);

	if (!window_handle) {
		fprintf(stderr, "Couldn't create the window\n");
		created = false;
		return false;
	}

	int glXattr[] = { None };
	glX_window_handle = window_handle;

	textprop.value = (unsigned char*)wTitle;
	textprop.encoding = XA_STRING;
	textprop.format = 8;
	textprop.nitems = strlen(wTitle);

	hints.x = x;
	hints.y = y;
	hints.width = width;
	hints.height = height;
	hints.flags = USPosition|USSize;

	startup_state = XAllocWMHints();
	startup_state->initial_state = NormalState;
	startup_state->flags = StateHint;

	XSetWMProperties(Xdisplay, window_handle,&textprop, &textprop,
		NULL, 0,
		&hints,
		startup_state,
		NULL);


	XFree(startup_state);
	
	XMapWindow(Xdisplay, window_handle);

	XFlush(Xdisplay);

	if ((del_atom = XInternAtom(Xdisplay, "WM_DELETE_WINDOW", 0)) != None) {
		XSetWMProtocols(Xdisplay, window_handle, &del_atom, 1);
	}

	{
		struct MwmHints {
			unsigned long flags;
			unsigned long functions;
			unsigned long decorations;
			long input_mode;
			unsigned long status;
		};
		enum {
			MWM_HINTS_FUNCTIONS = (1L << 0),
			MWM_HINTS_DECORATIONS =  (1L << 1),

			MWM_FUNC_ALL = (1L << 0),
			MWM_FUNC_RESIZE = (1L << 1),
			MWM_FUNC_MOVE = (1L << 2),
			MWM_FUNC_MINIMIZE = (1L << 3),
			MWM_FUNC_MAXIMIZE = (1L << 4),
			MWM_FUNC_CLOSE = (1L << 5)
		};

		Atom mwmHintsProperty = XInternAtom(Xdisplay, "_MOTIF_WM_HINTS", 0);
		MwmHints hints;
		hints.flags = MWM_HINTS_DECORATIONS;
		hints.decorations = 0;
		XChangeProperty(Xdisplay, window_handle, mwmHintsProperty, mwmHintsProperty, 32,
				PropModeReplace, (unsigned char *)&hints, 5);

	}
	int dummy;
	if (!glXQueryExtension(Xdisplay, &dummy, &dummy)) {
		fprintf(stderr, "OpenGL not supported by X server\n");
		created = false;
		return false;
	}

	render_context = glXCreateContext(Xdisplay, visual, 0, True);
	if (!render_context) {
		fprintf(stderr, "Failed to create a GL context\n");
		created = false;
		return false;
	}

	XEvent xev;
	long evmask = SubstructureRedirectMask | SubstructureNotifyMask;

	Atom state = XInternAtom(Xdisplay, "_NET_WM_STATE", False);
	Atom full_screen = XInternAtom(Xdisplay, "_NET_WM_STATE_FULLSCREEN", False);

	xev.type = ClientMessage;
	xev.xclient.window = window_handle;
	xev.xclient.message_type = state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 2;
	xev.xclient.data.l[1] = full_screen;
	xev.xclient.data.l[2] = 0;  /* no second property to toggle */
	xev.xclient.data.l[3] = 1;  /* source indication: application */
	xev.xclient.data.l[4] = 0;  /* unused */

	XSendEvent(Xdisplay, Xroot, 0, evmask, &xev);
	XFlush(Xdisplay);

	created = true;
	return true;
}

int _0xCC::Window::HandleMessage(XEvent event) {
	XConfigureEvent *xc;
	if (event.xany.window != window_handle)
		return 1;
	switch (event.type) {
		case ClientMessage:
			if (event.xclient.data.l[0] == del_atom) {
				return 0;
			}
		break;
		case ConfigureNotify:
			xc = &(event.xconfigure);
			width = xc->width;
			height = xc->height;
			break;
	}
	if (handleMessageEvent(event) == 1 /* curropt */ ){
		return 0;
	}
	return 1;
}

void _0xCC::Window::RenderEvent(){
	glXMakeContextCurrent(wm->GetDisplay(), glX_window_handle, glX_window_handle, render_context);
	handleRenderEvent();
	glXSwapBuffers(wm->GetDisplay(), glX_window_handle);
	// glXWaitGL();
}