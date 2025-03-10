
#include "hal_gpio.h"
#include "main.h"

static pin_mode_e _data_pin_state;

void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  GPIOD_CLK_ENABLE();
  hal_gpio_builtin_led_init();
  hal_gpio_ds1302_init();
}

void hal_gpio_ds1302_init(void)
{
  hal_gpio_ds1302_clk_pin_init();
  hal_gpio_ds1302_dat_pin_init(PIN_MODE_OUTPUT);
  hal_gpio_ds1302_rst_pin_init();
}

void hal_gpio_ds1302_deinit(void)
{
  hal_gpio_ds1302_clk_pin_deinit();
  hal_gpio_ds1302_dat_pin_deinit();
  hal_gpio_ds1302_rst_pin_deinit();
}

void hal_gpio_builtin_led_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOC_CLK_ENABLE();
  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = BUILTIN_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUILTIN_LED_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN, GPIO_PIN_RESET);
}

void hal_gpio_builtin_led_deinit()
{
  HAL_GPIO_DeInit(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
}

void hal_gpio_ds1302_clk_pin_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = DS1302_CLK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS1302_CLK_PORT, &GPIO_InitStruct);

  HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, GPIO_PIN_RESET);
}

void hal_gpio_ds1302_clk_pin_deinit()
{
  HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, GPIO_PIN_RESET);
  HAL_GPIO_DeInit(DS1302_CLK_PORT, DS1302_CLK_PIN);
}

void hal_gpio_ds1302_dat_pin_init(pin_mode_e mode)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = DS1302_DAT_PIN;
  if (mode == PIN_MODE_OUTPUT)
  {
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  }
  else
  { // INPUT MODE
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  }
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;

  HAL_GPIO_Init(DS1302_DAT_PORT, &GPIO_InitStruct);

  if (mode == PIN_MODE_OUTPUT)
  {
    HAL_GPIO_WritePin(DS1302_DAT_PORT, GPIO_MODE_OUTPUT_PP, GPIO_PIN_RESET);
  }

  _data_pin_state = mode;
}

void hal_gpio_ds1302_dat_pin_deinit()
{
  HAL_GPIO_WritePin(DS1302_DAT_PORT, GPIO_MODE_OUTPUT_PP, GPIO_PIN_RESET);
  HAL_GPIO_DeInit(DS1302_DAT_PORT, DS1302_DAT_PIN);
}

void hal_gpio_ds1302_rst_pin_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = DS1302_RST_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DS1302_RST_PORT, &GPIO_InitStruct);

  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, GPIO_PIN_RESET);
}

/*====================== ================== ============================*/
/*====================== HAL FOR DS1302 OPS ============================*/
/*====================== ================== ============================*/

void hal_gpio_ds1302_rst_pin_deinit()
{
  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, GPIO_PIN_RESET);
  HAL_GPIO_DeInit(DS1302_RST_PORT, DS1302_RST_PIN);
}

int hal_gpio_ds1302_rst_write(uint8_t val)
{
  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, val);
  return 0;
}

int hal_gpio_ds1302_clk_write(uint8_t val)
{
  HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, val);
  return 0;
}
int hal_gpio_ds1302_dat_set_mode(uint8_t mode)
{
  if (mode == _data_pin_state)
  {
    return 0;
  }
  // hal_gpio_ds1302_deinit();
  hal_gpio_ds1302_dat_pin_init(mode);
  return 0;
}
int hal_gpio_ds1302_dat_write(uint8_t val)
{
  HAL_GPIO_WritePin(DS1302_DAT_PORT, DS1302_DAT_PIN, val);
  return 0;
}

int hal_gpio_ds1302_dat_read(void)
{
  return HAL_GPIO_ReadPin(DS1302_DAT_PORT, DS1302_DAT_PIN);
};
