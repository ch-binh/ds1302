#ifndef DS1302_HW_H
#define DS1302_HW_H

#include <stdint.h>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1


typedef struct
{
    int (*rst_write)(uint8_t val);
    int (*clk_write)(uint8_t val); // ACCEPT HIGH (1) or LOW(0)
    int (*dat_set_mode)(uint8_t mode);
    int (*dat_write)(uint8_t val);
    int (*dat_read)(void);
    int (*delay_us)(uint8_t us);
} ds1302_hw_ops_t;

void ds1302_set_hw_spec(ds1302_hw_ops_t *ops);

int ds1302_rst_write(uint8_t val);
int ds1302_clk_write(uint8_t val);
int ds1302_dat_set_mode(uint8_t mode);
int ds1302_dat_write(uint8_t val);
int ds1302_dat_read(void);
int ds1302_delay_us(uint8_t us);

#endif // DS1302_HW_H