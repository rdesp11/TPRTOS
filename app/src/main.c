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
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
    #define LED1_PIN    DT_GPIO_PIN(LED1_NODE, gpios)
    #define LED1_FLAGS  DT_GPIO_FLAGS(LED1_NODE, gpios)
#else
    #error "Unsupported board: led1 devicetree alias is not defined"
#endif



#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
    #define LED2_PIN    DT_GPIO_PIN(LED2_NODE, gpios)
    #define LED2_FLAGS  DT_GPIO_FLAGS(LED2_NODE, gpios)
#else
    #error "Unsupported board: led2 devicetree alias is not defined"
#endif


#if DT_NODE_HAS_STATUS(LED3_NODE, okay)
    #define LED3_PIN    DT_GPIO_PIN(LED3_NODE, gpios)
    #define LED3_FLAGS  DT_GPIO_FLAGS(LED3_NODE, gpios)
#else
    #error "Unsupported board: led3 devicetree alias is not defined"
#endif


int main(void)
{
		printk("Zephyr CO2 measurement device base Application %s\n", APP_VERSION_STRING);
        const struct device *dev1 = DEVICE_DT_GET(DT_GPIO_CTLR(LED1_NODE, gpios));
        const struct device *dev2 = DEVICE_DT_GET(DT_GPIO_CTLR(LED2_NODE, gpios));
        const struct device *dev3 = DEVICE_DT_GET(DT_GPIO_CTLR(LED3_NODE, gpios));

        int ret;
        bool led1_state = true;
        bool led2_state = true;
        bool led3_state = true;

        if (!device_is_ready(dev3)) {
				LOG_ERR("Sensor not ready");
                return 0;
        }

        ret = gpio_pin_configure(dev3, LED3_PIN, GPIO_OUTPUT);
        if (ret < 0) {
				LOG_ERR("Could not configure gpio (%d)", ret);
                return 0;
        }

        ret = gpio_pin_toggle(dev3, LED3_PIN);
        if (ret < 0) {
				LOG_ERR("Could not toggle led (%d)", ret);
                return 0;
        }

        while (1) {
                ret = gpio_pin_toggle(dev3, LED3_PIN);
                if (ret < 0) {
						LOG_ERR("Could not toggle led (%d)", ret);
                        return 0;
                }

                led3_state = !led3_state;
                printf("LED state: %s\n", led3_state ? "ON" : "OFF");
                k_msleep(SLEEP_TIME_MS);
        }

        ret = gpio_pin_configure(dev1, LED1_PIN, GPIO_OUTPUT);
        if (ret < 0) {
				LOG_ERR("Could not configure gpio (%d)", ret);
                return 0;
        }

        ret = gpio_pin_toggle(dev1, LED1_PIN);
        if (ret < 0) {
				LOG_ERR("Could not toggle led (%d)", ret);
                return 0;
        }

        while (1) {
                ret = gpio_pin_toggle(dev1, LED1_PIN);
                if (ret < 0) {
						LOG_ERR("Could not toggle led (%d)", ret);
                        return 0;
                }

                led1_state = !led1_state;
                printf("LED state: %s\n", led1_state ? "ON" : "OFF");
                k_msleep(SLEEP_TIME_MS);
        }
        ret = gpio_pin_configure(dev2, LED2_PIN, GPIO_OUTPUT);
        if (ret < 0) {
				LOG_ERR("Could not configure gpio (%d)", ret);
                return 0;
        }

        ret = gpio_pin_toggle(dev2, LED2_PIN);
        if (ret < 0) {
				LOG_ERR("Could not toggle led (%d)", ret);
                return 0;
        }

        while (1) {
                ret = gpio_pin_toggle(dev2, LED2_PIN);
                if (ret < 0) {
						LOG_ERR("Could not toggle led (%d)", ret);
                        return 0;
                }

                led2_state = !led2_state;
                printf("LED state: %s\n", led2_state ? "ON" : "OFF");
                k_msleep(SLEEP_TIME_MS);
        }
        return 0;
}