#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

void main(void)
{
	const struct device *display_dev;
	lv_obj_t *display_label;

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found... aborting!");
		return;
	}
	if (IS_ENABLED(CONFIG_LVGL_POINTER_KSCAN)) {
		lv_obj_t *display_button;

		display_button = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_align(display_button, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_btn_set_fit(display_button, LV_FIT_TIGHT);
		display_label = lv_label_create(display_button, NULL);
	} else {
		display_label = lv_label_create(lv_scr_act(), NULL);
	}
	lv_label_set_text(display_label, "Hello Boss!!!");
	lv_obj_align(display_label, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_task_handler();
	display_blanking_off(display_dev);
}
