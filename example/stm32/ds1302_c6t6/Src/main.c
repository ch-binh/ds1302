
#include "syscfg.h"
#include "main.h"
#include "hal_usart.h"
#include "hal_gpio.h"
#include "board_config.h"
#include "ds1302.h"

#define CLOCK_SPEED_MHZ 72

void sw_udelay(uint32_t us)
{
  for (int i = 0; i < us; i++)
  {
    for (int j = 0; j < CLOCK_SPEED_MHZ; j++)
      ; // one us
  }
}

void ds1302_com_init(void)
{

  ds1302_hw_ops_t ds1302_hw = {
      .write = hal_gpio_ds1302_write,
      .read = hal_gpio_ds1302_read,
  };
  ds1302_set_hw_spec(&ds1302_hw);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  ds1302_com_init();

  uint8_t size = 2;
  uint8_t buffer[size];
  uint8_t seconds[2];

  while (1)
  {
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
    HAL_Delay(1000);

    seconds[0] = bcd2dec(hal_gpio_ds1302_read(0x81, buffer, size)) + '0';
    seconds[1] = '\n';
    //HAL_UART_Transmit(&huart1, (uint8_t *)"Hello, UART!\n", 12, HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1, seconds, 2, HAL_MAX_DELAY);
  }
  return 0;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
