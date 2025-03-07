#ifndef DS1302_HW_H
#define DS1302_HW_H

#include <stdint.h>

typedef struct
{
    int (*write)(uint8_t reg, uint8_t *data, uint8_t size);
    int (*read)(uint8_t reg, uint8_t *data, uint8_t size);
} ds1302_hw_ops_t;

void ds1302_set_hw_spec(ds1302_hw_ops_t *ops);

int ds1302_write_reg(uint8_t reg, uint8_t *data, uint8_t size);
int ds1302_read_reg(uint8_t reg, uint8_t *data, uint8_t size);

#endif // DS1302_HW_H