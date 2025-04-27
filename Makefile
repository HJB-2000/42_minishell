NAME = minishell
HEADER = minishell.h
BRANCH_HEADERS = custom_malloc/malloc.h\
					helper_functions/helper_functions.h\
					read_input_and_history/read_input.h\
					scanning/scanner.h

GFLAGS = -Werror -Wall -Wextra -g3 -fsanitize=address
CC = gcc

MAIN_FILE = main.c

READ_INPUT_FILES = read_input_and_history/read_command.c\
					read_input_and_history/history.c\
					scanning/scanner.c\
					scanning/token.c\
					scanning/recognize.c



GARBAGE_COLLECTORE = custom_malloc/malloc.c


HELPER_FUNCTIONS = helper_functions/func_list_1.c



SRC_FILE =	$(MAIN_FILE) $(READ_INPUT_FILES)\
			$(GARBAGE_COLLECTORE) $(HELPER_FUNCTIONS)
OBJS = $(SRC_FILE:.c=.o)

%.o: %.c $(HEADER) $(BRANCH_HEADERS)
	$(CC) $(GFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) -lreadline -o $(NAME) 
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

