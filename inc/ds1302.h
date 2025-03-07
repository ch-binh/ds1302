#ifndef DS1302_H
#define DS1302_H

#include "ds1302_hw.h"
#include "ds1302_reg.h"


/*======================== COMMON FUNCTIONS ===========================*/

uint8_t bcd2dec(uint8_t val);
uint8_t dec2bcd(uint8_t val);

#endif // DS1302_H