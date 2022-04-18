
# Name ==========================================

NAME := minishell.a

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
LIB_DIR := lib
BIN_DIR := bin

# Exes ==========================================

EXE := minishell

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
			$(SRC_DIR)/quotes.c\


# Make all ========================================

all : $(NAME)

$(NAME): minishell pipex builtins

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

LIBFT := $(LIB_DIR)/libft/libft.a

PRINTF := $(LIB_DIR)/libftprintf/libftprintf.a

PIPEX := $(LIB_DIR)/pipex/pipex

LIB_BIN := $(LIB_DIR)/builtins/bin

BINS := 	$(LIB_BIN)/echo \
			$(LIB_BIN)/env \
			$(LIB_BIN)/export \
			$(LIB_BIN)/pwd \
			$(LIB_BIN)/unset \

BUILTINS := $(BIN_DIR)/echo \
			$(BIN_DIR)/env \
			$(BIN_DIR)/export \
			$(BIN_DIR)/pwd \
			$(BIN_DIR)/unset \

$(LIBFT) :
	make -C lib/libft -f Makefile

$(PRINTF) :
	make -C lib/libftprintf -f Makefile

$(PIPEX) :
	make -C lib/pipex -f Makefile

$(BUILTINS) :
	make -C lib/builtins -f Makefile
	cp $(BINS) $(BIN_DIR)

# Recipes ========================================

minishell : $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE)

pipex : $(PIPEX)

builtins : $(BUILTINS)

# Cleanup ========================================

clean:
	make -C lib/pipex -f Makefile clean
	make -C lib/builtins -f Makefile clean
	make -C lib/libft -f Makefile clean
	make -C lib/libftprintf -f Makefile clean
	rm -f $(OBJS)

fclean : clean
	make -C lib/pipex -f Makefile fclean
	make -C lib/builtins -f Makefile fclean
	make -C lib/libft -f Makefile fclean
	make -C lib/libftprintf -f Makefile fclean
	rm -f $(EXE) $(BUILTINS)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
