/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    10.11.2014
 */

#include <assert.h>
#include <util/array.h>

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#include "libleddrv_ll.h"

struct leddrv_desc {
	GPIO_TypeDef *gpio;
	unsigned long pin;
};

static const struct leddrv_desc leddrv_leds[] = {
	{ GPIOD, GPIO_Pin_12 },
	{ GPIOD, GPIO_Pin_13 },
	{ GPIOD, GPIO_Pin_14 },
	{ GPIOD, GPIO_Pin_15 },
};
static_assert(ARRAY_SIZE(leddrv_leds) == LEDDRV_LED_N);

void leddrv_ll_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* NOTE GPIOD hardcoded */

	/* Enable GPIOs clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Set GPIO for output */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void leddrv_ll_update(unsigned char leds_state[LEDDRV_LED_N]) {
	int i;

	for (i = 0; i < LEDDRV_LED_N; i++) {
		const struct leddrv_desc *led = &leddrv_leds[i];

		if (leds_state[i]) {
			GPIO_SetBits(led->gpio, led->pin);
		} else {
			GPIO_ResetBits(led->gpio, led->pin);
		}
	}
}
