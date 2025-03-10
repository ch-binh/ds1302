#include "ds1302_hw.h"

static ds1302_hw_ops_t hw_ops;

/** INSTRUCTIONS: this is hardware abstraction, look up to example to
 * see how to use this
 *
 */

void ds1302_set_hw_spec(ds1302_hw_ops_t *ops)
{
    hw_ops = *ops; // Copy the function pointers
}

int ds1302_rst_write(uint8_t val)
{
    if (hw_ops.rst_write)
    {
        hw_ops.rst_write(val);
        return 0;
    }
    return -1; // Error: function not set
}

int ds1302_clk_write(uint8_t val)
{
    if (hw_ops.clk_write)
    {
        hw_ops.clk_write(val);
        return 0;
    }
    return -1; // Error: function not set
}

int ds1302_dat_set_mode(uint8_t mode)
{
    if (hw_ops.dat_set_mode)
    {
        hw_ops.dat_set_mode(mode);
        return 0;
    }
    return -1; // Error: function not set
}

int ds1302_dat_write(uint8_t val)
{
    if (hw_ops.dat_write)
    {
        hw_ops.dat_write(val);
        return 0;
    }
    return -1; // Error: function not set
}

int ds1302_dat_read(void)
{
    if (hw_ops.dat_read)
    {
        return hw_ops.dat_read();
    }
    return -1; // Error: function not set
}

int ds1302_delay_us(uint8_t us)
{
    if (hw_ops.delay_us)
    {
        hw_ops.delay_us(us);
        return 0;
    }
    return -1; // Error: function not set
}
