CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = src/pipex.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = 

LIBFTDIR = lib/libft

NAME = pipex

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ)
	@$(MAKE) -sC $(LIBFTDIR)
	@$(CC) $(OBJ) $(INCLUDE) -o $(NAME)
	@tput setaf 2
	@echo $(NAME) compiled

all : $(NAME)

clean :
	@rm -f $(OBJ)
	@$(MAKE) -sC $(LIBFTDIR) clean
	@echo object files deleted

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIBFTDIR) fclean
	@echo executable files deleted

re: fclean all

.PHONY : all clean fclean re