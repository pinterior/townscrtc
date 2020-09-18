#include <conio.h>

#include "common.h"
#include "settings.h"

static crtc_set_t crtc = CRTC_SET_31;
static video_set_t video = VIDEO_SET_31;

int main(int argc, char *argv[]) {

   uint16_t _Far *s0 = vram0();
   uint16_t _Far *s1 = vram1();

   for (int i = 0; i < 128 * 1024; ++i) {
      s0[i] = 0x8000;
      s1[i] = 0x8000;
   }

   crtc[ZOOM] = 0xf040;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   int x, y;
   uint16_t c[2] = {
      rgb15(16, 0,  0),
      rgb15( 0, 0, 16)
   };

   for (y = 0; y < 96; ++y) {
      for (x = 0; x < 256; ++x) {
         s0[y * 256 + x] = c[((y / 16) + (x / 40)) % 2];
      }
   }
   for (y = 0; y < 30; ++y) {
      for (x = 0; x < 256; ++x) {
         s1[y * 256 + x] = c[((y / 5) + (x / 40)) % 2];
      }
   }

   getch();
   return 0;
}
