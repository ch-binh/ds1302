# Overview
This example show the basic use of DS1302, such as write and read clock in burst mode.

```c
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
```

## How to use the example

You can find the comment in main.c for more detail