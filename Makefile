CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3#-fsanitize=address
NAME  = philo
SRC = src
OBJ = obj
TEST = test
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	@mkdir $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

clean_all: fclean
	@rm -rf $(NAME_LIB) $(NAME_PRI)

re: clean_all all