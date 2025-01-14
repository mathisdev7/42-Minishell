# ft_printf

![42 Project Score - 100/100](https://i.ibb.co/DCtw70t/image.png)

## Project Description
A custom implementation of the printf function as part of the 42 School curriculum. This project involves recreating the famous printf function from the C standard library, handling various format specifiers including:

- `%c` for characters
- `%s` for strings
- `%p` for pointers
- `%d` and `%i` for integers
- `%u` for unsigned integers
- `%x` and `%X` for hexadecimal numbers
- `%%` for the percent sign

## Features
- Handles all basic printf conversions
- Returns the exact number of characters printed
- Properly manages null pointers and edge cases
- Clean and modular code structure

## Implementation Details
The project is structured with a main printf function that handles the parsing of format strings and delegates the actual printing to specialized functions for each format specifier. Key files include:

- `ft_printf.c`: Core printf implementation
- `ft_printf.h`: Header file with function prototypes
- Various utility functions in the `lib/` directory for handling different format specifiers

## Personal Experience
This project was an enjoyable experience that provided deep insights into variadic functions and string formatting in C. The implementation was straightforward and fun, allowing me to better understand the inner workings of one of C's most commonly used functions.

## Building the Project
```bash
make        # Compile the library
make clean  # Remove object files
make fclean # Remove object files and library
make re     # Recompile everything
```

## Usage
After compilation, link with your program:
```bash
cc -Wall -Wextra -Werror your_program.c libftprintf.a
```

Example usage:
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s! Number: %d\n", "World", 42);
    return (0);
}
```
