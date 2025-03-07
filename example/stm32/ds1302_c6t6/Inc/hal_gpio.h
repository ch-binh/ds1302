
#ifndef __GPIO_H__
#define __GPIO_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define BIT_1 GPIO_PIN_SET
#define BIT_0 GPIO_PIN_RESET

typedef enum
{
  PIN_MODE_INPUT,
  PIN_MODE_OUTPUT
} pin_mode_e;

void MX_GPIO_Init(void);

void hal_gpio_ds1302_init(void);
void hal_gpio_ds1302_deinit(void);

void hal_gpio_builtin_led_init(void);
void hal_gpio_builtin_led_deinit(void);

void hal_gpio_ds1302_clk_pin_init(void);
void hal_gpio_ds1302_clk_pin_deinit(void);

void hal_gpio_ds1302_dat_pin_init(pin_mode_e mode);
void hal_gpio_ds1302_dat_pin_deinit(void);

void hal_gpio_ds1302_rst_pin_init(void);
void hal_gpio_ds1302_rst_pin_deinit();


int hal_gpio_ds1302_read(uint8_t reg, uint8_t *data, uint8_t size);
int hal_gpio_ds1302_write(uint8_t reg, uint8_t *data, uint8_t size);



#endif /*__ GPIO_H__ */
