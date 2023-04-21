#include "tifb.h"

// Function to draw a rectangle on the screen
void draw_rect(tifb_window *w, int x, int y, int width, int height, uint32_t color){
	for (int dy = 0; dy < height; dy++){
		for (int dx = 0; dx < width; dx++){
			w->buffer[(y + dy) * w->width + (x + dx)] = color;
		}
	}
}

int main(){
	// Create the window
	tifb_window w;
	w.title = "example - rectangles";
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

		// Draw the background color (clear the screen)
		draw_rect(&w, 0, 0, w.width, w.height, 0x333333);
		
		// Draw three rectangles
		draw_rect(&w, 100, 100, 50, 50, 0xff0000);
		draw_rect(&w, 200, 300, 100, 70, 0x00ff00);
		draw_rect(&w, 500, 200, 100, 200, 0x00ffff);

		// Update the window
		tifb_update(&w);
	}

	// Close the window and free the pixel buffer
	tifb_close(&w);
	return 0;
}
