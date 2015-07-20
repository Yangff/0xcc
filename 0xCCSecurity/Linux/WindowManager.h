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
#include <set>

namespace _0xCC {
	class Window;
	class WindowManager {
	private:
		Display *Xdisplay;
		Colormap cmap;
		XVisualInfo *visual;
		int Xscreen;
		::Window Xroot;
		bool created;
		int HandleMessage();
		std::set<_0xCC::Window *> wins;
	public:
		WindowManager();
		~WindowManager();

		int DoMessageLoop();
		int SingleMessageLoop();

		::Window GetRoot(){
			return Xroot;
		}
		Display *GetDisplay(){
			return Xdisplay;
		}
		XVisualInfo * GetVisual(){
			return visual;
		}
		Colormap GetColorMap(){
			return cmap;
		}
		void AddWindow(_0xCC::Window *win) {
			wins.insert(win);
		};
		void RemoveWindow(_0xCC::Window *win) {
			wins.erase(win);
		};
	};
}
