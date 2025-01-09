# 42 School Libft Project
> [!NOTE]
> I chose not to complete the bonus part as I preferred to move forward with other projects that interested me more.

![Final Score](https://i.ibb.co/DCtw70t/image.png)

## Project Journey
This project was quite a learning experience. I had to retry it 3 times due to:
- A missing file in the Makefile during first submission
- Issues with the `ft_substr` function not passing the Moulinette tests
- Finally got it right on the third attempt!

## About the Project
Libft is the first project at 42 School where we recreate various standard C library functions. This library will be used in future 42 projects.

### Key Functions Implemented
- Memory manipulation functions (memset, memcpy, memmove, etc.)
- String manipulation functions (strlen, strchr, strrchr, etc.)
- Character check functions (isalpha, isdigit, isalnum, etc.)
- String conversion functions (atoi, itoa)
- Memory allocation functions (calloc, strdup)
- File descriptor functions (putchar_fd, putstr_fd, putendl_fd, putnbr_fd)

### Lessons Learned
1. Importance of thorough testing
2. Memory management in C
3. Attention to detail in function implementation
4. Proper Makefile configuration

## Building the Library
```bash
make        # Compile the library
make clean  # Remove object files
make fclean # Remove object files and library
make re     # Recompile everything
```

## Note
This project taught me the importance of careful implementation and thorough testing. The multiple attempts helped me understand the intricacies of C programming and proper memory management.

## Author
- mazeghou (42 Login)
