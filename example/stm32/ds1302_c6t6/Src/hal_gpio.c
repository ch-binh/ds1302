
#include "hal_gpio.h"
#include "main.h"
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
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(DS1302_DAT_PORT, &GPIO_InitStruct);

  if (mode == PIN_MODE_OUTPUT)
  {
    HAL_GPIO_WritePin(DS1302_DAT_PORT, GPIO_MODE_OUTPUT_PP, GPIO_PIN_RESET);
  }
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

void hal_gpio_ds1302_rst_pin_deinit()
{
  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, GPIO_PIN_RESET);
  HAL_GPIO_DeInit(DS1302_RST_PORT, DS1302_RST_PIN);
}

#define U_DELAY 2

int hal_gpio_ds1302_read(uint8_t reg, uint8_t *data, uint8_t size)
{
  int resp = 0;

  hal_gpio_ds1302_rst_pin_init();
  hal_gpio_ds1302_clk_pin_init();
  hal_gpio_ds1302_dat_pin_init(PIN_MODE_OUTPUT);

  /* SEND REGISTERS */
  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, BIT_1);
  sw_udelay(U_DELAY);
  for (int i = 0; i < 8; i++)
  {
    

    HAL_GPIO_WritePin(DS1302_DAT_PORT, DS1302_DAT_PIN, (reg & 0x01));
    reg >>= 1;
    HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, BIT_0);
    sw_udelay(U_DELAY);
    HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, BIT_1);
    sw_udelay(U_DELAY);
  }
  HAL_GPIO_WritePin(DS1302_DAT_PORT, DS1302_DAT_PIN, BIT_0);
  
  hal_gpio_ds1302_dat_pin_deinit();
  hal_gpio_ds1302_dat_pin_init(PIN_MODE_INPUT);

  for (int i = 0; i < 8; i++)
  {
    HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, BIT_0);
    if (HAL_GPIO_ReadPin(DS1302_DAT_PORT, DS1302_DAT_PIN) == BIT_1)
    {
      resp |= (BIT_1 << (8 - i));
    }
    sw_udelay(U_DELAY);
    HAL_GPIO_WritePin(DS1302_CLK_PORT, DS1302_CLK_PIN, BIT_1);
    sw_udelay(U_DELAY);
  }

  HAL_GPIO_WritePin(DS1302_RST_PORT, DS1302_RST_PIN, BIT_0);
  hal_gpio_ds1302_dat_pin_deinit();
  hal_gpio_ds1302_dat_pin_init(PIN_MODE_OUTPUT);
  return resp;
}



int hal_gpio_ds1302_write(uint8_t reg, uint8_t *data, uint8_t size)
{
  return 0;
}
