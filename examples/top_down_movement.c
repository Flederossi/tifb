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
	w.title = "example - top_down_movement";
	w.width = 800;
	w.height = 600;

	// Initialize the pixel buffer and open the window
	tifb_init(&w);

	// Set the start position
	int x = 100;
	int y = 100;

	int running = 1;
	while (running){
		// Check if ESC- or Arrow-Keys are pressed
		for (int i = 0; i < sizeof(w.keys) / sizeof(long); i++){
			if (w.keys[i] == XK_Escape) running = 0;

			// Update the position if Arrow-Key is pressed
			if (w.keys[i] == XK_Up && y - 25 > 0) y -= 5;
			if (w.keys[i] == XK_Down && y + 25 < w.height) y += 5;
			if (w.keys[i] == XK_Left && x - 25 > 0) x -= 5;
			if (w.keys[i] == XK_Right && x + 25 < w.width) x += 5;
		}

		// Draw the background color (clear the screen)
		draw_rect(&w, 0, 0, w.width, w.height, 0x333333);

		// Draw the player
		draw_rect(&w, x - 25, y - 25, 50, 50, 0x00ff00);

		// Update the window
		tifb_update(&w);
	}

	// Close the window and free the pixel buffer
	tifb_close(&w);
	return 0;
}
