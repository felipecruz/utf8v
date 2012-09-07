utf8v
=====

This is a basic UTF-8 byte sequence validator in C.

[![Build Status](https://secure.travis-ci.org/felipecruz/utf8v.png)](http://travis-ci.org/felipecruz/utf8v)

How to Use it
-------------

First step:

```c
#include <utf8v.h>
```

You can use the main function (signature below):

```c
int utf8v_validate(uint8_t* data, int size);
```

Return codes description:

* **-1** - wrong size information
* **1** - invalid byte sequences
* **0** - sequence is valid.

If you need, there is also the functions used to make `utv8v_validate` work:

```c
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
int
    extract_sequence_length(uint8_t first_byte);

```

Tests
-----

Run:

`make test`

Coverage Report
---------------

In order to run coverage reports you'll have to install "lcov" package.

`make coverage`

Then, open `coverage/index.html`

Contact
-------

felipecruz@loogica.net
