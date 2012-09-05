#include <stdio.h>
#include <stdint.h>

#ifndef UTF8V_H
#define UTF8V_H

#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

/* utf8v_validate
 *
 * validate a byte 'array'
 * return 0 if is valid
 * return 1 if error
 */

int
    utf8v_validate(uint8_t*, int);

int
    valid_first_range(uint8_t byte);

int
    valid_second_range(uint8_t byte, uint8_t second);

int
    valid_third_range(uint8_t byte, uint8_t second, uint8_t third);

int
    valid_fourth_range(uint8_t byte,
                       uint8_t second,
                       uint8_t third,
                       uint8_t fourth);

#if TEST

#endif /* TEST */
#endif /* UTF8V_H */
