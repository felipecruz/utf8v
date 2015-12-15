#include <utf8v.h>

/*
 * legal utf-8 byte sequence
 * http://www.unicode.org/versions/Unicode6.0.0/ch03.pdf - page 94
 *
 *  Code Points        1st       2s       3s       4s
 * U+0000..U+007F     00..7F
 * U+0080..U+07FF     C2..DF   80..BF
 * U+0800..U+0FFF     E0       A0..BF   80..BF
 * U+1000..U+CFFF     E1..EC   80..BF   80..BF
 * U+D000..U+D7FF     ED       80..9F   80..BF
 * U+E000..U+FFFF     EE..EF   80..BF   80..BF
 * U+10000..U+3FFFF   F0       90..BF   80..BF   80..BF
 * U+40000..U+FFFFF   F1..F3   80..BF   80..BF   80..BF
 * U+100000..U+10FFFF F4       80..8F   80..BF   80..BF
 *
 */

#define FIRST_UTF8_RANGE(value)                            \
    (value <= 0x7F) ? 1 : 0

#define SECOND_UTF8_RANGE(value1, value2)                  \
    (value1 >= 0xC2 && value1 <= 0xDF) &&                  \
    (value2 >= 0x80 && value2 <= 0xBF) ? 1 : 0

#define THIRD_UTF8_RANGE(value1, value2, value3)           \
    ((value1 == 0xE0                    &&                 \
      value2 >= 0xA0 && value2 <= 0xBF  &&                 \
      value3 >= 0x80 && value3 <= 0xBF) ||                 \
     (value1 >= 0xE1 && value1 <= 0xEC  &&                 \
      value2 >= 0x80 && value2 <= 0xBF  &&                 \
      value3 >= 0x80 && value2 <= 0xBF) ||                 \
     (value1 == 0xED                    &&                 \
      value2 >= 0x80 && value2 <= 0x9F  &&                 \
      value3 >= 0x80 && value2 <= 0xBF) ||                 \
     (value1 >= 0xEE && value1 <= 0xEF  &&                 \
      value2 >= 0x80 && value2 <= 0xBF  &&                 \
      value3 >= 0x80 && value3 <= 0xBF)) ? 1 : 0

#define FOURTH_UTF8_RANGE(value1, value2, value3, value4)  \
    ((value1 == 0xF0 &&                                    \
      value2 >= 0x90 && value2 <= 0xBF  &&                 \
      value3 >= 0x80 && value3 <= 0xBF  &&                 \
      value4 >= 0x80 && value4 <= 0xBF) ||                 \
     (value1 >= 0xF1 && value1 <= 0xF3  &&                 \
      value2 >= 0x80 && value2 <= 0xBF  &&                 \
      value3 >= 0x80 && value3 <= 0xBF  &&                 \
      value4 >= 0x80 && value4 <= 0xBF) ||                 \
     (value1 == 0xF4                    &&                 \
      value2 >= 0x80 && value2 <= 0x8F  &&                 \
      value3 >= 0x80 && value3 <= 0xBF  &&                 \
      value4 >= 0x80 && value4 <= 0xBF)) ? 1 : 0

int
    valid_first_range(uint8_t byte)
{
    return FIRST_UTF8_RANGE(byte);
}

int
    valid_second_range(uint8_t first, uint8_t second)
{
    return SECOND_UTF8_RANGE(first, second);
}

int
    valid_third_range(uint8_t first, uint8_t second, uint8_t third)
{
    return THIRD_UTF8_RANGE(first, second, third);
}

int
    valid_fourth_range(uint8_t first,
                       uint8_t second,
                       uint8_t third,
                       uint8_t fourth)
{
    return FOURTH_UTF8_RANGE(first, second, third, fourth);
}

int
    extract_sequence_length(uint8_t first_byte)
{
    if (first_byte >> 3 == 0x1E) {
        return 3;
    } else if (first_byte >> 4 == 0x0E) {
        return 2;
    } else if (first_byte >> 5 == 0x06) {
        return 1;
    } else if (first_byte >> 7 == 0x00) {
        return 0;
    }
    return -1;
}

int
    utf8v_validate(uint8_t *data, int size)
{
    int i;
    int bytes_left = 0;

    if (size == 0) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        bytes_left = extract_sequence_length(data[i]);
        switch (bytes_left) {
            case 0:
                if (!FIRST_UTF8_RANGE(data[i])) {
                    return 1;
                }
                break;
            case 1:
                if (i+1 >= size) {
                    return -1;
                }
                if (!SECOND_UTF8_RANGE(data[i], data[i+1])) {
                    return 1;
                } else {
                    i += 1;
                }
            break;

            case 2:
                if (i+1 >= size || i+2 >= size) {
                    return -1;
                }
                if (!THIRD_UTF8_RANGE(data[i], data[i+1], data[i+2])) {
                    return 1;
                } else {
                    i += 2;
                }
            break;

            case 3:
                if (i+1 >= size || i+2 >= size || i+3 >= size) {
                    return -1;
                }
                if (!FOURTH_UTF8_RANGE(data[i],
                                       data[i+1],
                                       data[i+2],
                                       data[i+3])) {
                    return 1;
                } else {
                    i += 3;
                }
            break;

            default:
            return 1;
        }

    }
    return 0;
}
