#include "tifb.h"
#include <math.h>

// Function to draw a circle on the screen
void draw_circle(tifb_window *w, int x, int y, int r, uint32_t color){
	for (int dy = -r; dy < r; dy++){
		for (int dx = -r; dx < r; dx++){
			if (sqrt(dx*dx + dy*dy) <= r)
				w->buffer[(y + dy) * w->width + (x + dx)] = color;
		}
	}
}

int main(){
	// Create the window
	tifb_window w;
	w.title = "example - circles";
	w.width = 800;
	w.height = 600;

	// Initialize the pixel buffer and open the window
	tifb_init(&w);

	int running = 1;
	while (running){
		// Check if ESC-Key is pressed
		for (int i = 0; i < sizeof(w.keys) / sizeof(long); i++){
			if (w.keys[i] == XK_Escape) running = 0;
		}

		// Draw three circles;
		draw_circle(&w, 100, 100, 20, 0xff0000);
		draw_circle(&w, 500, 300, 50, 0xff00ff);
		draw_circle(&w, 200, 500, 30, 0xffffff);

		// Update the window
		tifb_update(&w);
	}

	// Close the window and free the pixel buffer
	tifb_close(&w);
	return 0;
}
