#include <utf8v.h>

/*
 * legal utf-8 byte sequence
 * http://www.unicode.org/versions/corrigendum1.html
 */

#define FIRST_UTF8_RANGE(value) \
    (value <= 0x7F) ? 1 : 0

#define SECOND_UTF8_RANGE(value1, value2) \
    (value1 >= 0xC2 && value1 <= 0xDF) && \
    (value2 >= 0x80 && value2 <= 0xBF) ? 1 : 0

#define THIRD_UTF8_RANGE(value1, value2, value3) \
    ((value1 == 0xE0 && \
      value2 >= 0xA0 && value2 <= 0xBF && \
      value3 >= 0x80 && value3 <= 0xBF) || \
     (value1 >= 0xE1 && value1 <= 0xEF && \
      value2 >= 0x80 && value2 <= 0xBF && \
      value3 >= 0x80 && value3 <= 0xBF)) ? 1 : 0

#define FOURTH_UTF8_RANGE(value1, value2, value3, value4) \
    ((value1 == 0xF0 && \
      value2 >= 0x90 && value2 <= 0xBF && \
      value3 >= 0x80 && value3 <= 0xBF && \
      value4 >= 0x80 && value4 <= 0xBF) || \
     (value1 >= 0xF1 && value1 <= 0xF3 && \
      value2 >= 0x80 && value2 <= 0xBF && \
      value3 >= 0x80 && value3 <= 0xBF && \
      value4 >= 0x80 && value4 <= 0xBF) || \
     (value1 == 0xF4 && \
      value2 >= 0x80 && value2 <= 0xBF && \
      value3 >= 0x80 && value3 <= 0xBF && \
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
    int invalid = 0;
    int missing = 0;

    for (i = 0; i < size; i++) {

        if (!FIRST_UTF8_RANGE(data[i])) {
            if (i == size-1)
                return 1;
            invalid = 1;
        } 

        //printf("-- %d\n", SECOND_UTF8_RANGE(data[i], data[i+1]));

        if (invalid == 1 && !SECOND_UTF8_RANGE(data[i], data[i+1])) {
            return 1;
        }

        if (invalid)
            return 1;

    }
    return 0;
}
