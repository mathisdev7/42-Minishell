# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/01/09 14:31:23 by mazeghou          #+#    #+#              #
#    Updated: 2025/01/09 14:31:23 by mazeghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/include/readline -g
LDFLAGS = -L/usr/lib -lreadline -lncurses
SRCS = src/main.c src/minishell.c src/utils/utils.c src/commands/echo.c src/utils/exec.c src/commands/cd.c src/commands/pwd.c src/commands/export.c src/commands/unset.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
