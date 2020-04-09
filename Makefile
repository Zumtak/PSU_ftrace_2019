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
			lib/free_d_array.c \

INCLUDE =	include/

OBJ = 	$(SRC:.c=.o)

override CFLAGS +=	-W 				\
					-Wall			\
					-Wextra			\
					-I $(INCLUDE)	\

NAME = ftrace

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(OBJ)

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
