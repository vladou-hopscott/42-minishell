# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/11 12:20:46 by vnafissi         ###   ########.fr        #
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
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR)
#-g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/minishell.h\
			$(INC_DIR)/parsing.h\

SRCS	:= 	$(SRC_DIR)/main.c\
			$(SRC_DIR)/prompt.c\
			$(SRC_DIR)/lexer.c\
			$(SRC_DIR)/parser.c\
			$(SRC_DIR)/expander.c\
			$(SRC_DIR)/executor.c\
			$(SRC_DIR)/tok_linked_list.c\
			$(SRC_DIR)/libft.c\


# Make all ========================================

all : $(NAME)

$(NAME): minishell

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

# Recipes ========================================

minishell : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE)

# Cleanup ========================================

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXE)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
