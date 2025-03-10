
#include "syscfg.h"
#include "main.h"
#include "hal_usart.h"
#include "hal_gpio.h"
#include "board_config.h"
#include "ds1302.h"

#define CLOCK_SPEED_MHZ 72

/* For simplicity, I dont use timer here, so the delay is
significantly inaccurate. 2us -> 13us */
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
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  ds1302_com_init();

  datetime_t time_keeper;
  datetime_t set_time = DATETIME_INIT(30, 59, 23, 31, 12, 7, 1); /// 30 secs to happy new year!!!
  ds1302_en_write();
  ds1302_write_time(&set_time, REG_WRITE_BURST);

  while (1)
  {
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
    HAL_Delay(1000);

    /* Read all of the time variables*/
    ds1302_read_time(&time_keeper, REG_READ_BURST);

    hal_uart_prinf("%d:%d:%d:%d:%d:%d:%d \n",
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
