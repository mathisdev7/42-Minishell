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

SRCS = src/main.c src/minishell.c \
src/utils/utils.c src/builtins/echo.c \
src/utils/exec.c src/builtins/cd.c src/builtins/pwd.c \
src/builtins/export.c src/builtins/unset.c src/utils/ft.c \
src/builtins/env.c

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = include/libft
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

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) >/dev/null
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

re: fclean all

.PHONY: all clean fclean re
