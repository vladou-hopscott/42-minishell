# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/11 22:08:53 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name ==========================================

NAME := pipex.a

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
BIN_DIR := .

# Exes ==========================================

EXE := $(BIN_DIR)/pipex

# Compilation ====================================

CC := cc
LDFLAGS ?= 
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR)
#-g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/pipex.h\

SRCS	:= 	$(SRC_DIR)/main.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/ft_split.c\
			$(SRC_DIR)/ft_strdup.c\
			$(SRC_DIR)/ft_strjoin.c\
			$(SRC_DIR)/ft_strlen.c\
			$(SRC_DIR)/ft_strncmp.c\
			$(SRC_DIR)/ft_strnstr.c\
			$(SRC_DIR)/ft_substr.c\

# Make all ========================================

all : $(NAME)

$(NAME): pipex

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

# Recipes ========================================

pipex : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE)

# Cleanup ========================================

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXE)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
