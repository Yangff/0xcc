#pragma once
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <cstring>
#include <cstdio>
#include <functional>
#include "WindowManager.h"

namespace _0xCC {
	class Window {
	private:
		
		Atom del_atom, wintype_atom;
		GLXContext render_context;
		::Window window_handle;
		GLXWindow glX_window_handle;
		int width, height;
		char *wTitle;
		bool created;
		WindowManager *wm;

		std::function<void()> handleRenderEvent;
		std::function<bool(XEvent event)> handleMessageEvent;

		const int VisData[17] = {
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_DOUBLEBUFFER, True,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 8,
			GLX_DEPTH_SIZE, 16,
			None
		};
	public:
		void SetRenderEvent(std::function<void()> _handleRenderEvent){
			handleRenderEvent = _handleRenderEvent;
		}
		void SetMessageEvent(std::function<bool(XEvent event)> _handleMessageEvent){
			handleMessageEvent = _handleMessageEvent;
		}
		Window(WindowManager *wm, const char *_title = "WoW", int width = 640, int height = 480):
		width(width), 
		height(height),
		wm(wm) {
			created = false;
			int title_len = strlen(_title);
			wTitle = new char[title_len + 1]; wTitle[title_len] = 0;
			for (int i = 0; i < title_len; i++)
				wTitle[i] = _title[i];

		}
		bool Create(int x = -1, int y = -1) ;

		int HandleMessage(XEvent event);
		void RenderEvent();

		int GetWidth(){
			return width;
		}

		int GetHeight() {
			return height;
		}
	};
};