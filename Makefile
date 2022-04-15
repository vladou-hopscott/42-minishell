# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/15 12:30:05 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name ==========================================

NAME := minishell.a

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
LIB_DIR := lib
BIN_DIR := .

# Exes ==========================================

EXE := $(BIN_DIR)/minishell

# Compilation ====================================

CC := cc
LDFLAGS ?= -lreadline
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/minishell.h\
			$(INC_DIR)/parsing.h\
			$(INC_DIR)/pipex.h\
			$(INC_DIR)/libft.h\
			$(INC_DIR)/ft_printf.h\

SRCS	:= 	$(SRC_DIR)/main.c\
			$(SRC_DIR)/prompt.c\
			$(SRC_DIR)/lexer.c\
			$(SRC_DIR)/parser.c\
			$(SRC_DIR)/expander.c\
			$(SRC_DIR)/executor.c\
			$(SRC_DIR)/tokens_linked_list.c\
			$(SRC_DIR)/init_values.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/env_manager.c\
			$(SRC_DIR)/env_manager_utils.c\

# Make all ========================================

all : $(NAME)

$(NAME): minishell pipex

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

PIPEX := $(LIB_DIR)/pipex/pipex

LIBFT := $(LIB_DIR)/libft/libft.a

PRINTF := $(LIB_DIR)/libftprintf/libftprintf.a

$(LIBFT) :
	make -C lib/libft -f Makefile

$(PRINTF) :
	make -C lib/libftprintf -f Makefile

$(PIPEX) :
	make -C lib/pipex -f Makefile

# Recipes ========================================

minishell : $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE)

pipex : $(PIPEX)

# Cleanup ========================================

clean:
	make -C lib/pipex -f Makefile clean
	make -C lib/libft -f Makefile clean
	make -C lib/libftprintf -f Makefile clean
	rm -rf $(OBJS)

fclean : clean
	make -C lib/pipex -f Makefile fclean
	make -C lib/libft -f Makefile fclean
	make -C lib/libftprintf -f Makefile fclean
	rm -rf $(EXE)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
