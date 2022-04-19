# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/19 17:38:13 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name ==========================================

NAME := builtins.a

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
BIN_DIR := bin

# Exes ==========================================

EXE_ECHO := $(BIN_DIR)/echo
EXE_PWD := $(BIN_DIR)/pwd
EXE_ENV := $(BIN_DIR)/env

# Compilation ====================================

CC := cc
LDFLAGS ?= 
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) #-g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/builtins.h\

SRCS_ECHO	:= 	$(SRC_DIR)/echo.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/ft_strncmp.c\

SRCS_PWD	:= 	$(SRC_DIR)/pwd.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/utils_env.c\
				$(SRC_DIR)/ft_split.c\
				$(SRC_DIR)/ft_strdup.c\
				$(SRC_DIR)/ft_strncmp.c\
				$(SRC_DIR)/ft_strjoin.c\

SRCS_ENV	:= 	$(SRC_DIR)/env.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/utils_env.c\
				$(SRC_DIR)/ft_split.c\
				$(SRC_DIR)/ft_strdup.c\
				$(SRC_DIR)/ft_strncmp.c\
				$(SRC_DIR)/ft_strjoin.c\

# Make all ========================================

all : $(BIN_DIR) $(NAME)

$(NAME): echo pwd env

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS_ECHO := $(SRCS_ECHO:.c=.o)

OBJS_PWD := $(SRCS_PWD:.c=.o)

OBJS_ENV := $(SRCS_ENV:.c=.o)

# Libs ==========================================

# Recipes ========================================

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

echo : $(OBJS_ECHO)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_ECHO)

pwd : $(OBJS_PWD)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_PWD)

env : $(OBJS_ENV)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_ENV)

# Cleanup ========================================

clean:
	rm -f $(OBJS_ECHO) $(OBJS_PWD) $(OBJS_ENV)

fclean : clean
	rm -f $(EXE_ECHO) $(EXE_PWD) $(EXE_ENV)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
