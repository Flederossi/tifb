#include "tifb.h"

int main(){
	// Create the window
	tifb_window w;
	w.title = "example - minimal";
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
    
		// Draw a white pixel at (0|0)
		w.buffer[0 * w.width + 0] = 0xffffff;
    
		// Update the window
		tifb_update(&w);
	}
  
	// Close the window and free the pixel buffer
	tifb_close(&w);
	return 0;
}
