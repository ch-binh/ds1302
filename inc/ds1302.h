#ifndef DS1302_H
#define DS1302_H

#include <stdint.h>
#include <stdbool.h>

#include "ds1302_hw.h"
#include "ds1302_reg.h"

#define U_DELAY 2 // delay for 2 us

#define DATETIME_INIT(sec, min, hr, date, month, weekday, year) \
    ((datetime_t){(sec), (min), (hr), (date), (month), (weekday), (year)})

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t date;
    uint8_t months;
    uint8_t weekday;
    uint8_t years;
} datetime_t;

/**
 * @brief Reads the current time from the DS1302 RTC module.
 *
 * This function reads the current time from the DS1302 RTC module and
 * populates the provided datetime_t structure with the read values.
 *
 * @param time Pointer to a datetime_t structure where the read time will be stored.
 * @param reg The register address to read the time from.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int ds1302_read_time(datetime_t *time, uint8_t reg);


/**
 * @brief Writes the provided time to the DS1302 RTC module.
 *
 * This function writes the provided time to the DS1302 RTC module using
 * the values from the provided datetime_t structure.
 *
 * @param time Pointer to a datetime_t structure containing the time to be written.
 * @param reg The register address to write the time to.
 * 
 * @note This function can use as a single register write (i.e REG_WRITE_SECONDS)
 * or as a burst write (i.e REG_WRITE_BURST).
 * 
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int ds1302_write_time(datetime_t *time, uint8_t reg);


/**
 * @brief Enables write operations to the DS1302 RTC module.
 *
 * This function enables write operations to the DS1302 RTC module by
 * setting the appropriate control register.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int ds1302_en_write(void);

/*======================== COMMON FUNCTIONS ===========================*/
/**
 * @brief Converts a BCD (Binary-Coded Decimal) value to a decimal value.
 *
 * This function takes an 8-bit BCD value and converts it to its corresponding
 * decimal value.
 *
 * @param val The BCD value to be converted.
 * @return uint8_t The converted decimal value.
 */
uint8_t ds1302_bcd2dec(uint8_t val);

/**
 * @brief Converts a decimal value to a BCD (Binary-Coded Decimal) value.
 *
 * This function takes an 8-bit decimal value and converts it to its corresponding
 * BCD value.
 *
 * @param val The decimal value to be converted.
 * @return uint8_t The converted BCD value.
 */
uint8_t ds1302_dec2bcd(uint8_t val);

#endif // DS1302_H