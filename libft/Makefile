# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 01:44:57 by oligrien          #+#    #+#              #
#    Updated: 2025/06/29 23:58:34 by oligrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories **************************************************************** #
SRCS_DIR = ./src
OBJS_DIR = ./obj

# Source Files *************************************************************** #
SRCS_FILES =	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strcmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strjoin_free_s1.c \
				ft_strjoin_free_s2.c \
				ft_strjoin_free_s1_s2.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar.c \
				ft_putstr.c \
				ft_putendl.c \
				ft_putulnbr.c \
				ft_putnbr.c \
				ft_putnbr_base.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstfirst.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_printf.c \
				get_next_line.c \
				ft_free.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

NAME = libft.a

# Compilation **************************************************************** #
CC = cc
CFLAGS =  -Wall -Wextra -Werror -g3

# Rules ********************************************************************** #
all: $(NAME)

# Compile .c files to .o files *********************************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@


# Build Library ************************************************************** #
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# Clean ********************************************************************** #
clean:
	@rm -rf $(OBJS_DIR)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

# **************************************************************************** #
.PHONY: all clean fclean  re