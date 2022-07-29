NAME = get_next_line.a

SRC = get_next_line.c get_next_line_utils.c \

SRC_BONUS = get_next_line_bonus_utils.c get_next_line_bonus.c \ 

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(SRC_BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE -g

$(NAME): $(OBJ) 
	ar rcs $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re