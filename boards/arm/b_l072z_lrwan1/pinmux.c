/*
 * Copyright (c) 2018 Aleksandr Makarov <aleksandr.o.makarov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include "pinmux/stm32/pinmux_stm32.h"

/* pin assignments for STMicroelectronics B-L072Z-LRWAN1 Discovery board */
static const struct pin_config pinconf[] = {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart1), okay)
	{STM32_PIN_PA9, STM32L0_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32L0_PINMUX_FUNC_PA10_USART1_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart2), okay)
	{STM32_PIN_PA2, STM32L0_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32L0_PINMUX_FUNC_PA3_USART2_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay)
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA15, STM32L0_PINMUX_FUNC_PA15_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB3, STM32L0_PINMUX_FUNC_PB3_SPI1_SCK},
	{STM32_PIN_PA6, STM32L0_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32L0_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi2), okay)
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PB12, STM32L0_PINMUX_FUNC_PB12_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB13, STM32L0_PINMUX_FUNC_PB13_SPI2_SCK},
	{STM32_PIN_PB14, STM32L0_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32L0_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay)
	{STM32_PIN_PB8, STM32L0_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32L0_PINMUX_FUNC_PB9_I2C1_SDA},
#endif
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
