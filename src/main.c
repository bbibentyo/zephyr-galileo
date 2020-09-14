#include <zephyr.h>
#include <device.h>
#include <display/cfb.h>
#include <stdio.h>

#if defined(CONFIG_SSD16XX)
#define DISPLAY_DRIVER	"SSD16XX"
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

	if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0) {
		printf("Failed to set required pixel format\n");
		return;
	}

	printf("initialized %s\n", DISPLAY_DRIVER);

	if (cfb_framebuffer_init(dev)) {
		printf("Framebuffer initialization failed\n");
		return;
	}

	cfb_framebuffer_clear(dev, true);
	display_blanking_off(dev);

	rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);
	ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);
	display_width = cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH);
	display_columns = cfb_get_display_parameter(dev, CFB_DISPLAY_COLS);

	printf("width: %d, columns: %d, rows: %d, ppt: %d",
			display_width, display_columns, rows, ppt);

	while(1) {
		cfb_framebuffer_clear(dev, true);
		cfb_print(dev, "Welcome Elikya", 0, 0);
		cfb_print(dev, "Welcome Nayah", 0, 40);
		cfb_framebuffer_finalize(dev);
		k_sleep(K_SECONDS(15))false;
	}
}
