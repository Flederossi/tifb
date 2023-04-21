#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *title;
	int width, height;
	uint32_t *buffer;
	long *keys;
	Display *display;
	Window window;
	XEvent event;
	XImage *image;
} tifb_window;

void tifb_init(tifb_window *w){
	w->display = XOpenDisplay(NULL);
	int screen = DefaultScreen(w->display);
	w->window = XCreateSimpleWindow(w->display, RootWindow(w->display, screen), 0, 0, w->width, w->height, 1, BlackPixel(w->display, screen), WhitePixel(w->display, screen));
	XStoreName(w->display, w->window, w->title);
	XSelectInput(w->display, w->window, ExposureMask | KeyPressMask);
	XMapWindow(w->display, w->window);
	XFlush(w->display);
	w->buffer = malloc(w->width * w->height * sizeof(uint32_t));
	memset(w->buffer, 0, w->width * w->height * sizeof(uint32_t));
	w->image = XCreateImage(w->display, DefaultVisual(w->display, screen), 24, ZPixmap, 0, (char *) w->buffer, w->width, w->height, 32, 0);
	w->keys = malloc(0);
}

void tifb_update(tifb_window *w){
	int i = 0;
	w->keys = realloc(w->keys, 0);
	while (XPending(w->display) > 0){
		XNextEvent(w->display, &w->event);
		if (w->event.type == KeyPress){
			i++;
			w->keys = realloc(w->keys, i * sizeof(long));
			w->keys[i - 1] = XLookupKeysym(&w->event.xkey, 0);
		}
	}
	XPutImage(w->display, w->window, DefaultGC(w->display, DefaultScreen(w->display)), w->image, 0, 0, 0, 0, w->width, w->height);
	XFlush(w->display);
}

void tifb_close(tifb_window *w){
	free(w->keys);
	XDestroyImage(w->image);
	XDestroyWindow(w->display, w->window);
	XCloseDisplay(w->display);
}
