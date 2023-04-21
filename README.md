# tifb
A tiny, singleheader X11 frame buffer which allows you to open a window, receive keyboard inputs as well as draw single pixels.
## Usage
Include the [tifb.h](https://github.com/Flederossi/tifb/blob/main/tifb.h) header in your project, add the compiler flag `-lX11` and you are ready to go!

*Note: If it will not compile you may have to install the packages libx11 and libx11-dev on your distro.*

> Minimal example:
```c
#include "tifb.h"

int main(){
  // Create the window
  tifb_window w;
  w.title = "tifb - window";
  w.width = 800;
  w.height = 600;
  
  // Initialize the pixel buffer and open the window
  tifb_init(&w);
  
  int running = 1;
  while (running){
    // Check if ESC-Key is in pointer of pressed keys
    for (int i = 0; i < sizeof(w.keys) / sizeof(long); i++){
      if (w.keys[i] == XK_Escape) running = 0;
    }
    
    // To find the index of a coordinate in the buffer you can use w.buffer[y * width + x]
    // The following line draws a white pixel at (0|0)
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
A tifb window has the following arguments which you can access:
```c
typedef struct {
  char *title; // The title of the window
  int width, height; // The dimensions of the window
  uint32_t *buffer; // The pixel buffer (consists of the pixel colors)
  long *keys; // The pointer which contains the pressed keys (gets updated by tifb_update())
}
``` 

## Keysyms
To see all available keysyms to check in the keys pointer, you can run:
```
cat /usr/include/X11/keysymdef.h
```
