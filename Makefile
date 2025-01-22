# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 04:20:50 by nopareti          #+#    #+#              #
#    Updated: 2025/01/14 04:20:50 by nopareti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

SPIN_CHARS = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏
CURRENT_FILE = 0

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I/usr/include/readline -g
LDFLAGS = -L/usr/lib -lreadline -lncurses

SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft
PRINTF_DIR = printf

SRC_FILES = main.c init.c free.c utils.c parsing/parsing.c \
exec/exec.c builtins/echo.c builtins/cd.c builtins/pwd.c \
builtins/unset.c builtins/export.c builtins/exit.c utils_env.c utils_args.c \
utils_cmd.c utils_env2.c parsing/redirections.c exec/redirections.c \
exec/cmd.c parsing/quotes.c parsing/cmd.c parsing/cmd2.c parsing/env.c \
parsing/get_redir.c signals.c parsing/pipes.c prompt.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a

define show_spinner
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval SPIN_IDX=$(shell echo $$(($(CURRENT_FILE) % 10))))
	$(eval SPINNER=$(shell echo "$(SPIN_CHARS)" | cut -d' ' -f$(shell echo $$(($(SPIN_IDX) + 1)))))
	printf "\r$(BLUE)$(SPINNER)$(RESET) $(GREEN)%-50s$(RESET)" $(notdir $1)
endef

define clean_spinner
	for i in $(SPIN_CHARS); do \
		printf "\r$(RED)$$i$(RESET) $(GREEN)Cleaning...$(RESET)"; \
		sleep 0.1; \
	done
	printf "\r$(GREEN)✓ All clean!$(RESET)                    \n"
endef

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call show_spinner,$<)

$(LIBFT):
	@printf "\r$(BLUE)⠋$(RESET) $(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1
	@printf "\r$(GREEN)✓ Libft ready!$(RESET)                    \n"

$(PRINTF):
	@printf "\r$(BLUE)⠋$(RESET) $(GREEN)Building printf...$(RESET)"
	@$(MAKE) -C $(PRINTF_DIR) >/dev/null 2>&1
	@printf "\r$(GREEN)✓ Printf ready!$(RESET)                    \n"

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(LDFLAGS) -o $(NAME) >/dev/null
	@printf "\r$(GREEN)✓ Build complete!$(RESET)                                        \n"

clean:
	@$(call clean_spinner)
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory >/dev/null

fclean:
	@$(call clean_spinner)
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory >/dev/null
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory >/dev/null

re: fclean all

.PHONY: all clean fclean re
