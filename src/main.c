#include "tifb.h"

void draw_rect(tifb_window *w, int x, int y, int width, int height, uint32_t color){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			w->buffer[(y + j) * w->width + (x + i)] = color;
		}
	}
}

int main(){
	tifb_window w;
	w.title = "Test";
	w.width = 800;
	w.height = 600;

	tifb_init(&w);

	int x = 350;
	int y = 250;

	int running = 1;
	while(running){
		for (int i = 0; i < sizeof(w.keys) / sizeof(long); i++){
			if (w.keys[i] == XK_Escape) running = 0;
			if (w.keys[i] == XK_Left && x > 0) x -= 10;
			if (w.keys[i] == XK_Right && x < 700) x += 10;
			if (w.keys[i] == XK_Up && y > 0) y -= 10;
			if (w.keys[i] == XK_Down && y < 500) y += 10;
		}

		draw_rect(&w, 0, 0, w.width, w.height, 0x333333);
		draw_rect(&w, x, y, 100, 100, 0x00FF00);
		tifb_update(&w);
	}

	tifb_close(&w);

	return 0;
}
