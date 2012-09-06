#include <utf8v.h>
#include <thc.h>

void
    test_valid_first_range(void)
{
    uint8_t valid_byte = 0x00;
    ENSURE(1 == valid_first_range(valid_byte));
}

void
    test_invalid_first_range(void)
{
    uint8_t valid_byte = 0x8F;
    ENSURE(0 == valid_first_range(valid_byte));
}

void
    test_valid_second_range(void)
{
    uint8_t valid_bytes[] = {0xC2, 0x80};
    ENSURE(1 == valid_second_range(valid_bytes[0], valid_bytes[1]));
}

void
    test_invalid_second_range(void)
{
    uint8_t valid_bytes[] = {0xC2, 0x70};
    ENSURE(0 == valid_second_range(valid_bytes[0], valid_bytes[1]));
}

void
    test_valid_third_range_first_subrange(void)
{
    uint8_t valid_bytes[] = {0xE0, 0xA1, 0x80};
    ENSURE(1 == valid_third_range(valid_bytes[0],
                                  valid_bytes[1],
                                  valid_bytes[2]));
}

void
    test_valid_third_range_second_subrange(void)
{
    uint8_t valid_bytes[] = {0xE0, 0xA1, 0x80};
    ENSURE(1 == valid_third_range(valid_bytes[0],
                                  valid_bytes[1],
                                  valid_bytes[2]));
}

void
    test_valid_fourth_range_first_subrange(void)
{

    uint8_t valid_bytes[] = {0xF0, 0x90, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_valid_fourth_range_second_subrange(void)
{

    uint8_t valid_bytes[] = {0xF2, 0x80, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_valid_fourth_range_third_subrange(void)
{

    uint8_t valid_bytes[] = {0xF4, 0x80, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_extract_sequence_length_zero_length(void)
{
    uint8_t valid_byte = 0x00;
    ENSURE(0 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_one_length(void)
{
    uint8_t valid_byte = 0xC2;
    ENSURE(1 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_two_length(void)
{
    uint8_t valid_byte = 0xE0;
    ENSURE(2 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_three_length(void)
{
    uint8_t valid_byte = 0xF4;
    ENSURE(3 == extract_sequence_length(valid_byte));
}

void
    test_validate_just_null(void)
{
    uint8_t just_null[] = {0x00};
    ENSURE(0 == utf8v_validate(just_null, 1));
}

void
    test_validate_highest_byte(void)
{
    uint8_t highest_byte[] = {0xFF};
    ENSURE(1 == utf8v_validate(highest_byte, 1));
}

void
    test_validate_ascii_only(void)
{
    /*                  H     e     l     l     o  */
    uint8_t hello[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    ENSURE(0 == utf8v_validate(hello, 5));
}

int
    main(int argc, char **argv)
{
    thc_addtest(test_valid_first_range);
    thc_addtest(test_invalid_first_range);
    thc_addtest(test_valid_second_range);
    thc_addtest(test_invalid_second_range);
    thc_addtest(test_valid_third_range_first_subrange);
    thc_addtest(test_valid_third_range_second_subrange);
    thc_addtest(test_valid_fourth_range_first_subrange);
    thc_addtest(test_valid_fourth_range_second_subrange);
    thc_addtest(test_valid_fourth_range_third_subrange);
    thc_addtest(test_extract_sequence_length_zero_length);
    thc_addtest(test_extract_sequence_length_one_length);
    thc_addtest(test_extract_sequence_length_two_length);
    thc_addtest(test_extract_sequence_length_three_length);
    thc_addtest(test_validate_just_null);
    thc_addtest(test_validate_highest_byte);
    thc_addtest(test_validate_ascii_only);
    return thc_run(THC_VERBOSE);
}
