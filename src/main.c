#include <zephyr.h>
#include <device.h>
#include <display/cfb.h>
#include <stdio.h>

#if defined(CONFIG_SSD16XX)
#define DISPLAY_DRIVER	"SSD16XX"
#endif

#ifndef DISPLAY_DRIVER 
#define DISPLAY_DRIVER "DISPLAY"
#endif

void main(void)
{
	const struct device *dev;
	int err;

	uint16_t rows;
	uint8_t ppt;
	uint8_t font_width;
	uint8_t font_height;
	uint8_t display_width;
	uint8_t display_columns;

	dev = device_get_binding(DISPLAY_DRIVER);

	if (dev == NULL) {
		printf("device not found... aborting!\n");
		return;
	}

	printf("initialized %s\n", DISPLAY_DRIVER);

	if (cfb_framebuffer_init(dev)) {
		printf("Framebuffer initialization failed\n");
		return;
	}

	cfb_framebuffer_clear(dev, true);
	// display_blanking_off(dev);

	rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);  // on reel board value is set to 15
	ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);  // on reel board value is set to 8
	display_width = cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH);  // on reel board value is set to 250
	display_columns = cfb_get_display_parameter(dev, CFB_DISPLAY_COLS);  // on reel board value is set to 250

	printf("width: %d, columns: %d, rows: %d, ppt: %d",
			display_width, display_columns, rows, ppt);
	char line[32];
	int second_line;
	int third_line;
	const int MAX_LINE_LIMIT = (rows-2) * ppt;

	while(1) {
		for (int i = 0; i < rows-1; i++) {
			cfb_framebuffer_clear(dev, false);
			second_line = (i*ppt)+16;
			third_line = (i*ppt)+32;
			// snprintf(line, 20, "Row: %d - Pos: %d", i, i*ppt);
			// TODO - Change text so that if we >= MAX (rows * ppt), we use modulus instead
			cfb_print(dev, "Welcome Elikya", 0, i*ppt);
			cfb_print(dev, "Welcome Nayah", 0, second_line);
			cfb_print(dev, "Welcome Boss", 0, third_line);
			cfb_framebuffer_finalize(dev);
			k_sleep(K_MSEC(100));
		}
	}
}
