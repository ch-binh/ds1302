#include "ds1302_hw.h"

static ds1302_hw_ops_t hw_ops;

void ds1302_set_hw_spec(ds1302_hw_ops_t *ops)
{
    hw_ops = *ops; // Copy the function pointers
}

int ds1302_write_reg(uint8_t reg, uint8_t *data, uint8_t size)
{
    if (hw_ops.read)
    {
        return hw_ops.read(reg, data, size);
    }
    return -1; // Error: function not set
}

int ds1302_read_reg(uint8_t reg, uint8_t *data, uint8_t size)
{
    if (hw_ops.read)
    {
        hw_ops.read(reg, data, size);
        return 0;
    }
    return -1; // Error: function not set
}