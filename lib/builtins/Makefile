# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/18 21:25:35 by swillis          ###   ########.fr        #
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
EXE_EXP := $(BIN_DIR)/export
EXE_UNS := $(BIN_DIR)/unset
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

SRCS_EXP	:= 	$(SRC_DIR)/exp.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/utils_env.c\
				$(SRC_DIR)/ft_split.c\
				$(SRC_DIR)/ft_strdup.c\
				$(SRC_DIR)/ft_strncmp.c\
				$(SRC_DIR)/ft_strjoin.c\

SRCS_UNS	:= 	$(SRC_DIR)/uns.c\
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

all : $(NAME)

$(NAME): echo pwd exp uns env

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS_ECHO := $(SRCS_ECHO:.c=.o)

OBJS_PWD := $(SRCS_PWD:.c=.o)

OBJS_EXP := $(SRCS_EXP:.c=.o)

OBJS_UNS := $(SRCS_UNS:.c=.o)

OBJS_ENV := $(SRCS_ENV:.c=.o)

# Libs ==========================================

# Recipes ========================================

echo : $(OBJS_ECHO)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_ECHO)

pwd : $(OBJS_PWD)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_PWD)

exp : $(OBJS_EXP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_EXP)

uns : $(OBJS_UNS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_UNS)

env : $(OBJS_ENV)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_ENV)

# Cleanup ========================================

clean:
	rm -f $(OBJS_ECHO) $(OBJS_PWD) $(OBJS_EXP) $(OBJS_UNS) $(OBJS_ENV)

fclean : clean
	rm -f $(EXE_ECHO) $(EXE_PWD) $(EXE_EXP) $(EXE_UNS) $(EXE_ENV)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
