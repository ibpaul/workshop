/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "math/Matrix.h"
#include "filter/gaussian.h"
#include "filter/operations.h"
#include "image/patterns.h"

//using namespace std::chrono;

unsigned char output_image[256*256];

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

class A {

};

int main(void)
{
    auto ret {0};

    lts::filter::KernelFast<float, 3, 3> kernel;
    lts::filter::load_gaussian(kernel);

    auto input = lts::image::vertical_lines(256, 256, 1);

	/*if (!device_is_ready(led.port)) {
		return 1;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 1;
	}*/

	while (1) {
        auto start = HAL_GetTick();
        lts::filter::convolute(kernel, input.get(), 256, 256, 1, output_image);
        auto end = HAL_GetTick();
        auto diff = end - start;

        printk("%d ms\n", diff);

		/*ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 1;
		}
		k_msleep(SLEEP_TIME_MS);*/
	}
}
