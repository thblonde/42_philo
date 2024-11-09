CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(SRC_DIR)/main.c\
	$(SRC_DIR)/init.c\
	$(SRC_DIR)/actions.c\
	$(SRC_DIR)/actions2.c\
	$(SRC_DIR)/threads.c\
	$(SRC_DIR)/utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
