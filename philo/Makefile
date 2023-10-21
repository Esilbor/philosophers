# project
NAME = philo

# compiler
CC = cc
CFLAGS = -g3 -Werror -Wextra -Werror -pthread

# libft
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

# include
INC = -I./include/

# sources and objects
SRC_DIR = ./src/
OBJ_DIR = ./obj/

C_FILES = main.c \
philo.c \
time.c \
philo_utils.c \
philo_utils_2.c \
init.c \
actions.c \
death.c \
forks.c \

SRC = $(addprefix $(SRC_DIR), $(C_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean all
