#include <stdio.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/sensor.h>
#include <drivers/gpio.h>

#include "display.h"
//#include "cfb_image.h"

#define TEMP_DEVICE_NAME "HDC1010"
#define ACCE_DEVICE_NAME "MMA8652FC"
#define DISP_DEVICE_NAME "SSD16XX"

const struct device *temp_humidity_device;
const struct device *accelerometer_device;
const struct device *display_device;

void main(void)
{
	temp_humidity_device = device_get_binding(TEMP_DEVICE_NAME);
	if (temp_humidity_device == NULL) {
		printk("Failed to initialize Temperature & Humidity device... aborting!\n");
		return;
	} else {
		printk("Temperature and humidity device has been initialized\n");
	}

	accelerometer_device = device_get_binding(ACCE_DEVICE_NAME);
	if(accelerometer_device == NULL){
		printk("Failed to initialize accelerometer device\n");
		return;
	} else {
		printk("Accelerometer has been initialized to %s\n", ACCE_DEVICE_NAME);
	}

	display_device = device_get_binding(DISP_DEVICE_NAME);
	if (display_device == NULL) {
		printk("Failed to initialize display device");
		return;
	} else {
		printk("Display device has been initialized... %s\n", DISP_DEVICE_NAME);
		if (cfb_framebuffer_init(display_device)) {
			printk("Framebuffer initialization failed\n");
			return;
		}
		display_blanking_off(display_device);
	}
	
	struct sensor_value temp;
	struct sensor_value humidity;
	struct sensor_value coord[3];
	char name[] = "Boss Bibentyo";

	while(1) {
		printk("Fetching temperature & humidity...\n");
		sensor_sample_fetch(temp_humidity_device);
		sensor_channel_get(temp_humidity_device, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(temp_humidity_device, SENSOR_CHAN_HUMIDITY, &humidity);

		printk("Fetching accelerometer data...\n");
		sensor_sample_fetch(accelerometer_device);
		sensor_channel_get(accelerometer_device, SENSOR_CHAN_ACCEL_XYZ, coord);

		cfb_framebuffer_clear(display_device, false);
		
		write_name_to_screen(display_device, name);
		write_separator(display_device);
		write_temp_to_screen(display_device, &temp);
		write_humidity_to_screen(display_device, &humidity);
		write_coordinates_to_screen(display_device, coord);
		cfb_framebuffer_finalize(display_device);

		k_sleep(K_SECONDS(15));
	}
}
