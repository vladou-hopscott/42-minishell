# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/04/15 21:24:42 by swillis          ###   ########.fr        #
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

# Compilation ====================================

CC := cc
LDFLAGS ?= 
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR)
#-g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/builtins.h\

SRCS_ECHO	:= 	$(SRC_DIR)/echo.c\
				$(SRC_DIR)/utils.c\

SRCS_PWD	:= 	$(SRC_DIR)/pwd.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/utils_env.c\
				$(SRC_DIR)/ft_split.c\
				$(SRC_DIR)/ft_strdup.c\
				$(SRC_DIR)/ft_strncmp.c\
				$(SRC_DIR)/ft_strjoin.c\

# Make all ========================================

all : $(NAME)

$(NAME): echo pwd

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS_ECHO := $(SRCS_ECHO:.c=.o)

OBJS_PWD := $(SRCS_PWD:.c=.o)

# Libs ==========================================

# Recipes ========================================

echo : $(OBJS_ECHO)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_ECHO)

pwd : $(OBJS_PWD)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE_PWD)

# Cleanup ========================================

clean:
	rm -f $(OBJS_ECHO) $(OBJS_PWD)

fclean : clean
	rm -f $(EXE_ECHO) $(EXE_PWD)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
