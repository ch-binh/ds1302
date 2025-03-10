#include <ds1302.h>

// reset pin write
// clk pin wrt
// data pin read / wrt


int ds1302_read_time(datetime_t *time, uint8_t reg)
{
    uint8_t loop = 1;
    int resp = 0;
    uint8_t *time_ptr = (uint8_t *)time;
    if (reg == REG_READ_BURST)
    {
        loop = sizeof(datetime_t);
    }

    ds1302_rst_write(HIGH); // select the ds1302
    ds1302_delay_us(U_DELAY);
    ds1302_dat_set_mode(OUTPUT);

    /* Write the registers */
    for (int i = 0; i < 8; i++)
    {
        ds1302_dat_write(reg & 0x01);
        reg >>= 1;
        ds1302_clk_write(LOW);
        ds1302_delay_us(U_DELAY);
        ds1302_clk_write(HIGH);
        ds1302_delay_us(U_DELAY);
    }
    ds1302_dat_write(LOW); // make sure that dat is low after write
    ds1302_dat_set_mode(INPUT);
    for (int k = 0; k < loop; k++)
    {
        /* Read response */
        for (int i = 0; i < 8; i++)
        {
            ds1302_clk_write(LOW);
            if (ds1302_dat_read() == HIGH)
            {
                resp |= (HIGH << i);
            }
            ds1302_delay_us(U_DELAY);
            ds1302_clk_write(HIGH);
            ds1302_delay_us(U_DELAY);
        }
        time_ptr[k] = ds1302_bcd2dec(resp);
        resp = 0;
    }
    /* RESET */
    ds1302_rst_write(LOW); // de-select the ds1302
    ds1302_dat_set_mode(OUTPUT);
    return resp;
}

int ds1302_write_time(datetime_t *time, uint8_t reg)
{
    uint8_t loop = 1;
    int resp = 0;
    uint8_t *time_ptr = (uint8_t *)time;
    uint8_t write_bit_mask = 0;
    if (reg == REG_WRITE_BURST)
    {
        loop = sizeof(datetime_t);
    }
    else
    {
        write_bit_mask = ds1302_dec2bcd(time_ptr[(reg - 0x80) >> 1]);
    }

    ds1302_rst_write(HIGH); // select the ds1302
    ds1302_delay_us(U_DELAY);
    ds1302_dat_set_mode(OUTPUT);

    /* Write the registers */
    for (int i = 0; i < 8; i++)
    {
        ds1302_dat_write(reg & 0x01);
        reg >>= 1;
        ds1302_clk_write(LOW);
        ds1302_delay_us(U_DELAY);
        ds1302_clk_write(HIGH);
        ds1302_delay_us(U_DELAY);
    }
    ds1302_dat_write(LOW); // make sure that dat is low after write
    for (int k = 0; k < loop; k++)
    {
        if (loop != 1)
        {
            write_bit_mask = ds1302_dec2bcd(time_ptr[k]);
        }

        for (int i = 0; i < 8; i++)
        {
            ds1302_dat_write(write_bit_mask & 0x01);
            write_bit_mask >>= 1;
            ds1302_clk_write(LOW);
            ds1302_delay_us(U_DELAY);
            ds1302_clk_write(HIGH);
            ds1302_delay_us(U_DELAY);
        }
    }
    /* RESET */
    ds1302_rst_write(LOW); // de-select the ds1302
    return resp;
}

int ds1302_en_write(void)
{
    uint8_t loop = 1;
    int resp = 0;
    uint8_t reg = REG_WRITE_PROTECT;
    uint8_t write_bit_mask = 0;

    ds1302_rst_write(HIGH); // select the ds1302
    ds1302_delay_us(U_DELAY);
    ds1302_dat_set_mode(OUTPUT);

    /* Write the registers */
    for (int i = 0; i < 8; i++)
    {
        ds1302_dat_write(reg & 0x01);
        reg >>= 1;
        ds1302_clk_write(LOW);
        ds1302_delay_us(U_DELAY);
        ds1302_clk_write(HIGH);
        ds1302_delay_us(U_DELAY);
    }
    ds1302_dat_write(LOW); // make sure that dat is low after write

    for (int i = 0; i < 8; i++)
    {
        ds1302_dat_write(write_bit_mask & 0x01);
        write_bit_mask >>= 1;
        ds1302_clk_write(LOW);
        ds1302_delay_us(U_DELAY);
        ds1302_clk_write(HIGH);
        ds1302_delay_us(U_DELAY);
    }
    /* RESET */
    ds1302_rst_write(LOW); // de-select the ds1302
    return resp;
}

/*======================== COMMON FUNCTIONS ===========================*/
uint8_t ds1302_bcd2dec(uint8_t val)
{
    return ((val >> 4) & 0x0F) * 10 + (val & 0x0F);
}

uint8_t ds1302_dec2bcd(uint8_t val)
{
    uint8_t tens = (val * 205) >> 11; // 11 bit = 2048 -> 205/2024 almost but larger than 1, make it ~1/10
    uint8_t ones = val - (tens * 10);

    return (tens << 4) | ones;
}