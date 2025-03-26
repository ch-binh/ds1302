
#include "syscfg.h"
#include "main.h"
#include "hal_usart.h"
#include "hal_gpio.h"
#include "board_config.h"
#include "ds1302.h"

#define CLOCK_SPEED 8000000

/* For simplicity, I dont use timer here, so the delay is
significantly inaccurate. 2us -> 13us */
void sw_udelay(uint32_t us)
{
  uint32_t clock_ticks = us * (uint32_t)(CLOCK_SPEED / 1000000);
  for (uint32_t i = 0; i < clock_ticks; i++)
  {
    __NOP();
  }
}

/* Link the STM32 HAL to ds1302 operations*/
void ds1302_com_init(void)
{
  ds1302_hw_ops_t ds1302_hw = {
      .rst_write = hal_gpio_ds1302_rst_write,
      .clk_write = hal_gpio_ds1302_clk_write,
      .dat_set_mode = hal_gpio_ds1302_dat_set_mode,
      .dat_write = hal_gpio_ds1302_dat_write,
      .dat_read = hal_gpio_ds1302_dat_read,
      .delay_us = sw_udelay,
  };
  ds1302_set_hw_spec(&ds1302_hw);
}

int main(void)
{
  /* Initiate STM32 hardware peripherals */
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  ds1302_com_init();

  /* Write clock */
  datetime_t time_keeper;
  datetime_t set_time = DATETIME_INIT(30, 59, 23, 31, 12, 7, 1); /// 30 secs to happy new year!!!
  ds1302_en_write();
  ds1302_write_time(&set_time, REG_WRITE_BURST);

  while (1)
  {
    /* Blink for visual */
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
    HAL_Delay(1000);

    /* Read all of the time variables*/
    ds1302_read_time(&time_keeper, REG_READ_BURST);

    hal_uart_printf("%d:%d:%d:%d:%d:%d:%d \n",
                   time_keeper.seconds,
                   time_keeper.minutes,
                   time_keeper.hours,
                   time_keeper.date,
                   time_keeper.months,
                   time_keeper.weekday,
                   time_keeper.years);
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
