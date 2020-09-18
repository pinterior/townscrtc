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

   crtc[FA0] = 0x4000;
   crtc[FA1] = 0x8000;
   crtc[ZOOM] = 0x1111;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   for (int y = 0; y < 96; ++y) {
      for (int x = 0; x < 96; ++x) {
         int p = x + y;
         if (p < 96) {
            uint16_t c = 0;

            switch (p) {
            case 0..31:
               c = rgb15(31 - p, p, 0);
               break;
            case 32..63:
               c = rgb15(0, 63 - p, p - 32);
               break;
            case 64..95:
               c = rgb15(p - 64, 0, 95 - p);
               break;
            }

            if (x % 4 < 2) {
               uint32_t a = y * 256 + x - (x / 4) * 2;
               s0[(0x4000 * 2 + a) & 0x3ffff] = c;
            } else {
               uint32_t a = y * 256 + x - 2 - (x / 4) * 2;
               s1[(0x8000 * 2 + a) & 0x3ffff] = c;
            }
         }
      }
   }

   getch();
   return 0;
}
