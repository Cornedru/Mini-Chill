# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/08/16 04:11:41 by ndehmej          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name **************************************************************** #
NAME = minishell

# Directories ***************************************************************** #
SRCS_DIR     = ./src
OBJS_DIR     = ./obj
LIBFT_DIR    = ./libft
GC_DIR       = ./gc
INCLUDES_DIR = ./includes

# Subdirectories of src/ ***************************************************** #
EXEC_DIR     = exec
BUILTINS_DIR = built-ins
UTILS_DIR    = utils
PRS_DIR      = parser

# Source Files *************************************************************** #
SRCS_FILES =	./main.c \
				./signals_utils.c \
				./signals.c \
				$(EXEC_DIR)/env_array.c \
				$(EXEC_DIR)/pipe_utils.c \
				$(EXEC_DIR)/env_lst.c \
                $(EXEC_DIR)/env_utils.c \
                $(EXEC_DIR)/exec.c \
                $(EXEC_DIR)/exec_cmd.c \
				$(EXEC_DIR)/init.c \
                $(EXEC_DIR)/path.c \
                $(EXEC_DIR)/pipe.c \
                $(EXEC_DIR)/redir.c \
				$(BUILTINS_DIR)/bi_utils.c \
                $(BUILTINS_DIR)/cd.c \
				$(BUILTINS_DIR)/cd_path.c \
				$(BUILTINS_DIR)/cd_path_utils.c \
                $(BUILTINS_DIR)/echo.c \
				$(BUILTINS_DIR)/env.c \
				$(BUILTINS_DIR)/exit.c \
				$(BUILTINS_DIR)/export.c \
				$(BUILTINS_DIR)/export_utils.c \
                $(BUILTINS_DIR)/pwd.c \
				$(BUILTINS_DIR)/unset.c \
				$(PRS_DIR)/heredoc_handler.c \
				$(PRS_DIR)/heredoc.c \
				$(PRS_DIR)/heredoc_utils.c \
                $(PRS_DIR)/lexer.c \
				$(PRS_DIR)/args.c \
				$(PRS_DIR)/args_utils.c \
				$(PRS_DIR)/ast.c \
                $(PRS_DIR)/parser.c \
                $(PRS_DIR)/redir.c \
                $(PRS_DIR)/redir2.c \
				$(PRS_DIR)/lexer_utils.c \
				$(PRS_DIR)/parser_utils.c \
				$(PRS_DIR)/parser_utils2.c \
                $(PRS_DIR)/quotes.c \
                $(PRS_DIR)/utils.c \
                $(PRS_DIR)/quotes_utils.c \
                $(PRS_DIR)/quotes_expand.c \
                $(PRS_DIR)/operator.c \
                $(PRS_DIR)/vars_utils.c \
                $(PRS_DIR)/tokens.c \
				$(PRS_DIR)/tokens_utils.c \
                $(PRS_DIR)/tokens2.c \
                $(PRS_DIR)/pipeline.c \

# Full paths to source and object files ************************************** #
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# External libraries ********************************************************* #
LIBFT = $(LIBFT_DIR)/libft.a
GC    = $(GC_DIR)/gc.a

# Compiler and flags ********************************************************* #
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g3 \
		 -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(GC_DIR)/includes

# Default rule *************************************************************** #
all: $(NAME)

# Build executable *********************************************************** #
$(NAME): $(OBJS) $(LIBFT) $(GC)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(GC) $(LIBFT) -o $(NAME) -lreadline 
	@echo "Build complete."

# Build libft.a ************************************************************** #
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "libft built."

# Build gc.a ***************************************************************** #
$(GC): $(LIBFT)
	@echo "Building gc..."
	@$(MAKE) -s -C $(GC_DIR) LIBFT_PATH="../libft"
	@echo "gc built."

# Compile .c to .o with directory creation *********************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and libraries ******************************************* #
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(GC_DIR) clean
	@echo "Clean done."

# Clean everything *********************************************************** #
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(GC_DIR) fclean

# Rebuild ******************************************************************** #
re: fclean all

# Phony targets ************************************************************** #
.PHONY: all clean fclean re
