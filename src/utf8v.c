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
