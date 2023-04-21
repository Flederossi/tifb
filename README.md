# tifb
A tiny, singleheader X11 frame buffer which allows you to open a window, receive keyboard inputs as well as draw single pixels.
# Usage
Include the [tifb.h](https://github.com/Flederossi/tifb/blob/main/tifb.h) header in your project, add the compiler flag `-lX11` and you are ready to go!
*Note: If it will not compile you may have to install the packages libx11 and libx11-dev on your distro.*

> Minimal example:
```c
#include "tifb.h"

int main(){
  tifb_window w;
  w.title = "tifb - window";
  w.width = 800;
  w.height = 600;
  
  tifb_init(&w);
  
  int running = 1;
  while (running){
    for (int i = 0; i < sizeof(w.keys) / sizeof(long); i++){
      if (w.keys[i] == XK_Escape) running = 0;
    }
    tifb_update(&w);
  }
  
  tifb_close(&w);
  return 0;
}
```
