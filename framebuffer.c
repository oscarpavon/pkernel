#include "framebuffer.h"


#include "font.h"

FrameBuffer frame_buffer;

void plot_pixel(int x, int y, uint32_t pixel){
*((uint32_t*)(frame_buffer.frame_buffer 
			+ 4 * frame_buffer.pixel_per_scan_line
			* y + 4 * x)) = pixel;
}

void draw_character(unsigned char character, int x, int y,
		int foreground, int background)
{
	int cx,cy;
	int mask[8]={128,64,32,16,8,4,2,1};
	unsigned char *glyph=font+(int)character*16;

	for(cy=0;cy<16;cy++){
		for(cx=0;cx<8;cx++){
			plot_pixel(x+cx, y+cy, glyph[cy]&mask[cx]?foreground:background);
		}
	}
}
