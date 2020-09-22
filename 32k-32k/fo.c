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
   crtc[ZOOM] = 0xffff;

   crtc[FO0] = 256;
   crtc[FO1] = 2;

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   for (int n = 0; n < 3; ++n) {
     s0[512 *  11 +      16 + n] = rgb15(31, 31, 0);
     s0[512 * (11 + n) + 16    ] = rgb15(31, 31, 0);
     s0[512 *  18 +      23 - n] = rgb15(31, 31, 0);
     s0[512 * (18 - n) + 23    ] = rgb15(31, 31, 0);
     s0[512 *  11 +      23 - n] = rgb15(31, 31, 0);
     s0[512 * (11 + n) + 23    ] = rgb15(31, 31, 0);
     s0[512 *  18 +      16 + n] = rgb15(31, 31, 0);
     s0[512 * (18 - n) + 16    ] = rgb15(31, 31, 0);

     s1[512 *  13  +     18 + n] = rgb15( 0, 31, 0);
     s1[512 *  16  +     19 + n] = rgb15( 0, 31, 0);
     s1[512 * (14 + n) + 18    ] = rgb15( 0, 31, 0);
     s1[512 * (13 + n) + 21    ] = rgb15( 0, 31, 0);
   }

   getch();
   return 0;
}
