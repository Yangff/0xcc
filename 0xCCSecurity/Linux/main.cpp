/*
	TODO: handle /dev/input/event* 
	TODO: display text on screen
	TODO: interactive with backend
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

#include "Window.h"
#include "WindowManager.h"

using namespace _0xCC;

int main(int argc, char *argv[]) {
	if ((getuid ()) != 0)
		return -1;
	WindowManager wm;
	_0xCC::Window win(&wm, "0xcc sec handle", -1, -1);
	win.SetMessageEvent([&] (XEvent event) -> bool{
		if (event.type == KeyPress) return true;
		return false; 
	});

	win.SetRenderEvent([&] () -> void {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0,0.0,0.0,.8);
	});
	if (win.Create()){
		wm.AddWindow(&win);
		while (wm.SingleMessageLoop()){;}
	}
}
