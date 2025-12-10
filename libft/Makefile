# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 11:12:20 by jhauvill          #+#    #+#              #
#    Updated: 2025/12/08 12:07:55 by jhauvill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_isascii.c ft_memcmp.c ft_putchar_fd.c\
          ft_strlen.c ft_memcpy.c ft_memset.c ft_strlcpy.c ft_memmove.c ft_memchr.c ft_strdup.c\
          ft_tolower.c ft_toupper.c ft_bzero.c ft_atoi.c ft_strlcat.c ft_strchr.c ft_strncmp.c\
		  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strrchr.c ft_strnstr.c ft_calloc.c ft_substr.c\
		  ft_strmapi.c ft_strjoin.c ft_strtrim.c ft_striteri.c ft_itoa.c ft_split.c \
		  ft_printf/ft_printf.c ft_printf/utils.c ft_printf/utils2.c \
		  gnl/get_next_line.c gnl/get_next_line_utils.c is_isspace.c ft_strcmp.c \

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS:.c=.o)

FT_PRINTF_DIR = ft_printf

CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f
CC = cc

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

%.o: %.c libft.h
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	$(RM) $(OBJECTS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)
.PHONY: all clean fclean re