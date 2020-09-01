# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/01 15:41:27 by phakakos          #+#    #+#              #
#    Updated: 2020/09/01 15:41:30 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRCS=actions.c add_actions.c anim.c anim_helpers.c draw_helpers.c draw_line.c\
drawing.c keys.c main.c map_misc.c map_resets.c points.c pos_test.c \
projections.c reader.c resets.c 
BIGO=$(SRCS:.c=.o)
INC=-I ./minilibx -I libft/ 
LIB=-L ./minilibx -lmlx -L ./libft/ -lft 
FRAMEWORK=-framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) :
	make -C ./libft/
	gcc -c -Wall -Wextra -Werror $(SRCS) $(INC)
	gcc -Wall -Wextra -Werror -o $(NAME) $(BIGO) $(LIB) $(FRAMEWORK)

clean :
	rm -f $(BIGO)
	make -C ./libft clean

fclean : clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
