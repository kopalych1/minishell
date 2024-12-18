# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 13:20:29 by akostian          #+#    #+#              #
#    Updated: 2024/12/18 15:30:45 by vcaratti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME					= minishell

VPATH					= src:src/hm:src/parse:src/builtin:src/exec

SRC_DIR					= src
SRCS					= main.c \
						  parse.c process_arg.c get_var_length.c calculate_argc.c \
						  hm_free.c hm_get.c hm_set.c hm_init.c \
						  ft_cd.c ft_echo.c ft_pwd.c ft_env.c \
						  free_arr.c	\
						  cmd_path.c exec_free.c exec_init.c exec_io.c exec_tools.c \
						  list_tools.c executor.c

INC_DIR					= include
INCLUDES				= -I$(INC_DIR)
READLINE_LINK			= -lreadline

BUILD_DIR				= build
LIBFT_DIR				= libft
LIBFT					= $(LIBFT_DIR)/libft.a
OBJS					= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))

CC						= gcc #?
CFLAGS					= -Wall -Wextra -Werror -static-libasan #-ggdb3 -fsanitize=address

NORMINETTE				= norminette
NORMINETTE_FLAGS		= --use-gitignore

RM						= rm -rf



all: $(NAME)
#


$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(READLINE_LINK) $(LIBFT)
#


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
#


$(LIBFT):
	make -C $(LIBFT_DIR)
#


$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#


run: all
	./$(NAME)
#


vrun: all
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./$(NAME)
#


norm:
	norminette $(NORMINETTE_FLAGS) $(SRC_DIR) $(INC_DIR)
#


clean:
	make clean -C $(LIBFT_DIR)

	$(RM) $(BUILD_DIR)
#


fclean:
	make fclean -C $(LIBFT_DIR)

	$(RM) $(BUILD_DIR) $(NAME)
#


re: fclean all
#



.PHONY: all clean fclean re
