NAME = minishell
HEADER = minishell.h
GFLAGS = -Werror -Wall -Wextra -g3 
CC = gcc

MAIN_FILE = main.c

READ_INPUT_FILES = read_input_and_history/read_command.c\
					read_input_and_history/history.c


GARBAGE_COLLECTORE = custom_malloc/malloc.c


HELPER_FUNCTIONS = helper_functions/func_list_1.c



SRC_FILE =	$(MAIN_FILE) $(READ_INPUT_FILES)\
			$(GARBAGE_COLLECTORE) $(HELPER_FUNCTIONS)
OBJS = $(SRC_FILE:.c=.o)

%.o: %.c $(HEADER)
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

