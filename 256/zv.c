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

   crtc[ZOOM] = 0xf040;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   set_palette(0, 128, 0,   0);
   set_palette(1,   0, 0, 128);

   int x, y;
   for (y = 0; y < 96; ++y) {
      for (x = 0; x < 320; ++x) {
         s0[y * 512 + x] = ((y / 16) + (x / 40)) % 2;
      }
   }
   for (y = 0; y < 30; ++y) {
      for (x = 0; x < 320; ++x) {
         s1[y * 512 + x] = ((y / 5) + (x / 40)) % 2;
      }
   }

   getch();
   return 0;
}
