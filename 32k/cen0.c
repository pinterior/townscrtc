#include <conio.h>

#include "common.h"
#include "settings.h"

static crtc_set_t crtc = CRTC_SET_28;
static video_set_t video = VIDEO_SET_28;

int main(int argc, char *argv[]) {

   uint16_t _Far *s0 = vram0();
   uint16_t _Far *s1 = vram1();

   for (int i = 0; i < 128 * 1024; ++i) {
      s0[i] = 0x8000;
      s1[i] = 0x8000;
   }

   crtc[HDE0] += crtc[HDE0] - crtc[HDS0];
   crtc[HDE1] += crtc[HDE1] - crtc[HDS1];
   crtc[VDE0] += crtc[VDE0] - crtc[VDS0];
   crtc[VDE1] += crtc[VDE1] - crtc[VDS1];
   crtc[CR0] &= 0xffcf;
   crtc[CR0] |= 0x0010; // CEN0 = 1, CEN1 = 0
   crtc[ZOOM] = 0xffff;

   crtc[FA0] = (512 - 20) / 2;
   crtc[FA1] = (512 - 20) / 2;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   for (int j = 0; j < 40; ++j) {
      uint16_t c = 0x7fff;
      if (j == 0) c = rgb15(0, 31, 0);
      if (j == 39) c = rgb15(31, 0, 0);

      uint32_t b0 = 512 - 20 + 512 *  1;
      uint32_t b1 = 512 - 20 + 512 * 28;

      s0[(b0 + j) & 0x1ffff] = c;
      s1[(b1 & 0x1fe00) | ((b1 + j) & 0x1ff)] = c;
   }

   getch();
   return 0;
}
