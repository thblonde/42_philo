CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(SRC_DIR)/1-main.c\
	$(SRC_DIR)/2-init.c\
	$(SRC_DIR)/3-threads.c\
	$(SRC_DIR)/4-actions.c\
	$(SRC_DIR)/5-safe_functions.c\
	$(SRC_DIR)/6-print.c\
	$(SRC_DIR)/7-time.c

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
