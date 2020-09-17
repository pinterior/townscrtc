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
   crtc[ZOOM] = 0x1111;

   --crtc[HAJ0];

   stop_display();
   set_crtc(crtc);
   set_video(video);
   start_display();

   uint16_t c = rgb15(31, 31, 0);

   uint32_t o0 = 512 * 60 + 35;
   uint32_t om = 512 * 60 + 35 + 60 + 35;
   uint32_t o1 = 512 * 60 + 35 + 60 + 35 + 60 + 35;

   for (int y = 0; y < 120; ++y) {
      int x = y / 2;
      int d = 512 * y + x;
      s0[o0 + d] = c;
      (y % 2 == 0 ? s0 : s1)[om + d] = c;
      s1[o1 + d] = c;
   }

   getch();
   return 0;
}
