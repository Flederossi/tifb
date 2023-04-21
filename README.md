# tifb
A tiny, singleheader X11 frame buffer which allows you to open a window, receive keyboard inputs as well as draw single pixels.
## Usage
Include the [tifb.h](https://github.com/Flederossi/tifb/blob/main/tifb.h) header in your project, add the compiler flag `-lX11` and you are ready to go!

*Note: If there is a compiler error you may have to install the packages libx11 and libx11-dev on your distro.*

> Minimal example:
```c
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
```

## Window Struct
A tifb window consists of following arguments you can access and modify:
```c
typedef struct {
  char *title;        // The title of the window
  int width, height;  // The dimensions of the window
  uint32_t *buffer;   // The pixel buffer (consists of the pixel colors as uint32_t)
  long *keys;         // The pointer which contains the pressed keys each update
}
``` 

## Keysyms
To get all keysyms you can check for on your distro, just run:
```
cat /usr/include/X11/keysymdef.h
```
