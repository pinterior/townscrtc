#include <conio.h>
#include <stdlib.h>

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
   crtc[CR0]  |= 0x0030; // CEN0=1, CEN1=1
   crtc[ZOOM] = 0x3131;

   crtc[LO0] = 0xffff;
   crtc[LO1] = 1;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   s0[0] = rgb15(0, 31, 0);
   s0[1] = rgb15(0, 31, 0);
   s1[318] = rgb15(31, 0, 0);
   s1[319] = rgb15(31, 0, 0);

   getch();
   return 0;
}
