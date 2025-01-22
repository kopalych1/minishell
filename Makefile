# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 13:20:29 by akostian          #+#    #+#              #
#    Updated: 2025/01/22 14:27:23 by vcaratti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME					= minishell

VPATH					= src:src/hm:src/parse:src/builtin:src/exec:src/get_next_line

SRC_DIR					= src
SRCS					= main.c \
						  minishell_interactive_utils.c \
						  parse.c process_arg.c get_var_length.c calculate_argc.c parse_utils.c pipe_readline.c pipe_readline_tools.c\
						  hm_free.c hm_get.c hm_set.c hm_init.c hm_delete.c hm_key_exists.c hm_sort_keys.c hm_to_array.c\
						  ft_cd.c ft_echo.c ft_pwd.c ft_env.c ft_unset.c ft_export.c \
						  free_arr.c \
						  cmd_path.c exec_free.c exec_init.c exec_init_tools.c exec_io.c exec_tools.c exec_child.c exec_tokenise.c\
						  list_tools.c list_convert.c heredoc.c heredoc_tools.c exec_builtins.c exec_builtins_special.c executor.c \
						  get_next_line.c get_next_line_utils.c

INC_DIR					= include
INCLUDES				= -I$(INC_DIR)
READLINE_LINK			= -lreadline

BUILD_DIR				= build
LIBFT_DIR				= libft
LIBFT					= $(LIBFT_DIR)/libft.a
OBJS					= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))

CC						= cc
CFLAGS					= -Wall -Wextra -Werror -g3 -static-libasan

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
