# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/16 16:46:29 by phakakos          #+#    #+#              #
#    Updated: 2020/09/16 16:46:32 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
SRCS=main.c draw.c mlx.c helpers.c image.c fractal.c formula.c formula_bonus.c\
	color_picker.c loops.c input.c mouse.c actions.c mouse_live.c
BIGO=$(SRCS:.c=.o)
INC=-I ./minilibx -I libft 
LIB=-L ./minilibx -lmlx -L ./libft -lft 
FLAGS=-Wall -Wextra -Werror
FRAMEWORK=-framework OpenGL -framework AppKit 


all : $(NAME)

$(NAME) :
	make -C ./libft
	gcc -c $(FLAGS) $(SRCS) $(INC)
	gcc $(FLAGS) -lpthread -pthread -o $(NAME) $(BIGO) $(LIB) $(FRAMEWORK)

clean :
	make -C ./libft clean
	rm -f $(BIGO)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
