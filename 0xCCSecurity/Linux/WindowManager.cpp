#include "WindowManager.h"
#include "Window.h"

_0xCC::WindowManager::WindowManager(){
	Xdisplay = XOpenDisplay(NULL);
	if (!Xdisplay) {
		fprintf(stderr, "Couldn't connect to X server\n");
		created = false;
		return ;
	}
	Xscreen = DefaultScreen(Xdisplay);
	Xroot = RootWindow(Xdisplay, Xscreen);
	visual = new XVisualInfo;
	XMatchVisualInfo(Xdisplay, DefaultScreen(Xdisplay), 32, TrueColor, visual);
	cmap = XCreateColormap(Xdisplay, Xroot, visual->visual, AllocNone);
}

_0xCC::WindowManager::~WindowManager(){
	delete visual;
}

int _0xCC::WindowManager::DoMessageLoop(){
	while (HandleMessage()) {
		for (auto v : wins) {
			v->RenderEvent();
		}
	}
	return 0;
}

int _0xCC::WindowManager::SingleMessageLoop(){
	if (HandleMessage()) {
		for (auto v : wins) {
			v->RenderEvent();
		}
		return 1;
	}
	return 0;
}

int _0xCC::WindowManager::HandleMessage(){
	XEvent event;
	while (XPending(Xdisplay)){
		XNextEvent(Xdisplay, &event);
		for (auto v : wins) 
			if (v->HandleMessage(event) == 0)
				return 0;
	}
	return 1;
}
