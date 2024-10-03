/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
    #define LED0_PIN    DT_GPIO_PIN(LED0_NODE, gpios)
    #define LED0_FLAGS  DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
    #error "Unsupported board: led0 devicetree alias is not defined"
#endif

int main(void)
{
		printk("Zephyr CO2 measurement device base Application %s\n", APP_VERSION_STRING);
        const struct device *const dev = DEVICE_DT_GET(DT_GPIO_CTLR(LED0_NODE, gpios));

        int ret;
        bool led_state = true;

        if (!device_is_ready(dev)) {
				LOG_ERR("Sensor not ready");
                return 0;
        }

        ret = gpio_pin_configure(dev, LED0_PIN, GPIO_OUTPUT);
        if (ret < 0) {
				LOG_ERR("Could not configure gpio (%d)", ret);
                return 0;
        }

        ret = gpio_pin_toggle(dev, LED0_PIN);
        if (ret < 0) {
				LOG_ERR("Could not toggle led (%d)", ret);
                return 0;
        }

        while (1) {
                ret = gpio_pin_toggle(dev, LED0_PIN);
                if (ret < 0) {
						LOG_ERR("Could not toggle led (%d)", ret);
                        return 0;
                }

                led_state = !led_state;
                printf("LED state: %s\n", led_state ? "ON" : "OFF");
                k_msleep(SLEEP_TIME_MS);
        }
        return 0;
}