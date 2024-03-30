CC = cc

CFLAGS = -g -Wall -Wextra -Werror 

SRC = 	src/mandatory/main.c src/mandatory/pipex.c src/mandatory/utils.c \
		src/mandatory/open_files.c 

SRC_BONUS = src/bonus/open_files_bonus.c src/bonus/utils_bonus2.c \
			src/bonus/multi_pipe_bonus.c src/bonus/pipex_bonus.c \
			src/bonus/utils_bonus.c
		
OBJ = $(SRC:%.c=%.o)

OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

INCLUDE = -Llib/libft -lft

LIBFTDIR = lib/libft

NAME = pipex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ) $(OBJ_BONUS) 
	@$(MAKE) -sC $(LIBFTDIR)
	@$(CC) $(OBJ) $(OBJ_BONUS) $(INCLUDE) -o $(NAME)
	@tput setaf 2
	@echo $(NAME) compiled

all : $(NAME)

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)
	@$(MAKE) -sC $(LIBFTDIR) clean
	@echo object files deleted

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIBFTDIR) fclean
	@echo executable files deleted

re: fclean all

.PHONY : all clean fclean re