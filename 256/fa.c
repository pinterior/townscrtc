#include <conio.h>

#include "common.h"
#include "settings.h"
#include "palette.h"

static crtc_set_t crtc = CRTC_SET_1;
static video_set_t video = VIDEO_SET_1;

int main(int argc, char *argv[]) {

   uint8_t _Far *s0 = vram0();
   uint8_t _Far *s1 = vram1();

   for (int i = 0; i < 256 * 1024; ++i) {
      s0[i] = 0x00;
      s1[i] = 0x00;
   }

   crtc[FA0] = 0x4000;
   crtc[FA1] = 0x8000;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   for (int c = 0; c < 256; ++c) {
      set_palette(c, c, c, c);
   }

   for (int y = 0; y < 256; ++y) {
      for (int x = 0; x < 256; ++x) {
         if (x + y < 256) {
            uint8_t c = 256u - (x + y);
            if (x % 8 < 4) {
               uint32_t a = y * 512 + x - (x / 8) * 4;
               s0[(0x4000 * 4 + a) & 0x3ffff] = c;
            } else {
               uint32_t a = y * 512 + x - 4 - (x / 8) * 4;
               s1[(0x8000 * 4 + a) & 0x3ffff] = c;
            }
         }
      }
   }

   getch();
   return 0;
}
