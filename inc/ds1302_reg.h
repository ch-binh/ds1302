#ifndef DS1302_REG_H
#define DS1302_REG_H

#define REG_READ_SECONDS 0x81
#define REG_READ_MINUTES 0x83
#define REG_READ_HOURS 0x85
#define REG_READ_DATE 0x87
#define REG_READ_MONTH 0x89
#define REG_READ_WEEKDAY 0x8B
#define REG_READ_YEAR 0x8D

#define REG_READ_BURST 0xBF // Read all parameters

#define REG_WRITE_SECONDS 0x80
#define REG_WRITE_MINUTES 0x82
#define REG_WRITE_HOURS 0x84
#define REG_WRITE_DATE 0x86
#define REG_WRITE_MONTH 0x88
#define REG_WRITE_WEEKDAY 0x8A
#define REG_WRITE_YEAR 0x8C

#define REG_WRITE_BURST 0xBE // write all parameters

#define REG_WRITE_PROTECT 0x8E

#endif
