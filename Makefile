NAME = get_next_line.a
SRCS = get_next_line.c get_next_line_utils.c 
BONUS = get_next_line_bonus.c get_next_line_utils.c

OBJECTS = $(SRCS:.c=.o)
BOBJCTS = $(BONUS:.c=.o)

AR = ar rc
CC = cc
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -r $@ $?

bonus: $(OBJECTS) $(BOBJCTS)
	$(AR) -r $(NAME) $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) $(BOBJCTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re