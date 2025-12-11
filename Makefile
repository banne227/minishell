# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banne <banne@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 15:02:14 by jhauvill          #+#    #+#              #
#    Updated: 2025/12/11 09:23:18 by banne            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
LIBFT_PATH = libft/libft.a

SOURCES = \
    main.c \
	parsing/build_cmd.c \
	parsing/lexer.c \
	parsing/tokenizer.c \
	parsing/expand.c \
	parsing/quotes.c \
	signals/signal.c \
	signals/signals_heredoc.c \
	exec/close_all.c \
	exec/exec_pipeline.c \
	exec/exec_single_cmd.c \
	exec/exec.c \
	exec/find_path.c \
	exec/free_pipe.c \
	exec/heredoc.c \
	exec/pipeline_utils.c \
	exec/redirection.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/pwd.c \
	builtins/set_envp_path.c \
	builtins/unset.c \
	builtins/update_env.c \
	utils/init_utils.c \
	utils/export_utils.c \
	utils/export_copy.c \
	utils/cleanup.c \
	utils/env_init.c \
	utils/print_export.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes.

RM = rm -f
CC = cc

all: $(LIBFT_DIR)/libft.a $(NAME)

$(LIBFT_DIR)/libft.a :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_PATH) -lreadline

clean:
	$(RM) $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
