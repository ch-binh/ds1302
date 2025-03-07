#include <ds1302.h>


/*======================== COMMON FUNCTIONS ===========================*/

uint8_t bcd2dec(uint8_t val)
{
    return ((val >> 4) & 0x0F) * 10 + (val & 0x0F);
}

uint8_t dec2bcd(uint8_t val)
{
    uint8_t tens = (val * 205) >> 11; // 11 bit = 2048 -> 205/2024 almost but larger than 1, make it ~1/10
    uint8_t ones = val - (tens * 10);

    return (tens << 4) | ones;
}