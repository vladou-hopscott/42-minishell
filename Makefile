
# Name ==========================================

NAME := minishell.a

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
LIB_DIR := lib

# Exes ==========================================

EXE := minishell

# Compilation ====================================

CC := cc
LDFLAGS ?= -lreadline -L/usr/local/opt/readline/lib/
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/local/opt/readline/include #-g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/minishell.h\
			$(INC_DIR)/parsing.h\
			$(INC_DIR)/pipex.h\
			$(INC_DIR)/libft.h\
			$(INC_DIR)/ft_printf.h\

SRCS	:= 	$(SRC_DIR)/main.c\
			$(SRC_DIR)/prompt.c\
			$(SRC_DIR)/lexer.c\
			$(SRC_DIR)/syntax_validation.c\
			$(SRC_DIR)/syntax_validation2.c\
			$(SRC_DIR)/parser.c\
			$(SRC_DIR)/update_token_type.c\
			$(SRC_DIR)/executor.c\
			$(SRC_DIR)/executor_errors.c\
			$(SRC_DIR)/executor_binary.c\
			$(SRC_DIR)/builtins.c\
			$(SRC_DIR)/builtins2.c\
			$(SRC_DIR)/builtins3.c\
			$(SRC_DIR)/tokens_linked_list.c\
			$(SRC_DIR)/cmds_linked_list.c\
			$(SRC_DIR)/cmd_line_struct.c\
			$(SRC_DIR)/init_values.c\
			$(SRC_DIR)/free_values.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/utils2.c\
			$(SRC_DIR)/env_manager.c\
			$(SRC_DIR)/env_manager_utils.c\
			$(SRC_DIR)/env_expand.c\
			$(SRC_DIR)/env_expand2.c\
			$(SRC_DIR)/quotes.c\
			$(SRC_DIR)/quotes_utils.c\
			$(SRC_DIR)/signals.c\
			$(SRC_DIR)/heredoc.c\
			$(SRC_DIR)/heredoc2.c\
			$(SRC_DIR)/heredoc3.c\
			$(SRC_DIR)/redirections.c\
			$(SRC_DIR)/multipipe.c\
			$(SRC_DIR)/int_check.c\

# Make all ========================================

all : $(NAME)

$(NAME): minishell

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

LIBFT := $(LIB_DIR)/libft/libft.a

PRINTF := $(LIB_DIR)/libftprintf/libftprintf.a

$(LIBFT) :
	make -C lib/libft -f Makefile

$(PRINTF) :
	make -C lib/libftprintf -f Makefile

# Recipes ========================================

minishell : $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE) -lreadline

# Cleanup ========================================

clean:
	make -C lib/libft -f Makefile clean
	make -C lib/libftprintf -f Makefile clean
	rm -f $(OBJS)

fclean : clean
	make -C lib/libft -f Makefile fclean
	make -C lib/libftprintf -f Makefile fclean
	rm -f $(EXE)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
