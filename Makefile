## EPITECH PROJECT, 2019
## PROJECT_NAME
## File description:
## Description here

SRC 	= 	src/main.c \
			src/arguments_utils.c \
			src/manage_arguments.c \
			src/path_commande.c \
			src/display_syscall.c \
			src/ftrace.c \
			src/check_opcode.c \
			src/symbols_finder_static.c \
			src/symbols_finder_dynamic.c \
			src/function_list.c \
			src/check_exit_loop.c		\
			src/process_call.c			\
			lib/free_d_array.c \

INCLUDE =	include/

OBJ = 	$(SRC:.c=.o)

override CFLAGS +=	-W 				\
					-Wall			\
					-Wextra			\
					-I $(INCLUDE)	\
					-lelf 			\

NAME = ftrace

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) -lelf

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

debug: CFLAGS += -ggdb3
debug: re

re: fclean all

tests_run:
	$(MAKE) -C criterion && ./criterion/test


.PHONY: re $(NAME) all clean fclean tests_run debug
