# Project Name
NAME = get_next_line.a

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source Files
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

# Header File
HEADER = get_next_line.h

# Makefile Rules
all: $(NAME)

# Build the library
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Library $(NAME) created successfully!"

# Compile .c files to .o files
%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< into $@"

# Remove object files
clean:
	@rm -f $(OBJS)
	@echo "Object files removed."

# Remove object files and the library
fclean: clean
	@rm -f $(NAME)
	@echo "Library $(NAME) removed."

# Rebuild everything
re: fclean all

# Phony Targets
.PHONY: all clean fclean re
