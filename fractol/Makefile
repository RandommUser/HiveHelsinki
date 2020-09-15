NAME=fractol
SRCS=main.c draw.c mlx.c
BIGO=$(SRCS:.c=.o)
INC=-I ./minilibx -I libft 
LIB=-L ./minilibx -lmlx -L ./libft -lft 
FLAGS=-Wall -Wextra -Werror
FRAMEWORK=-framework OpenGL -framework AppKit 


all : $(NAME)

$(NAME) :
	make -C ./libft
	gcc -c $(FLAGS) $(SRCS) $(INC)
	gcc $(FLAGS) -o $(NAME) $(BIGO) $(LIB) $(FRAMEWORK)

clean :
	make -C ./libft clean
	rm -f $(BIGO)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
