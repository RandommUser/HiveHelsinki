# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 17:22:50 by phakakos          #+#    #+#              #
#    Updated: 2020/02/19 17:45:06 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

FILES=main.c reader.c points.c drawing.c keys.c anim.c anim_helpers.c actions.c \
add_actions.c projections.c map_misc.c resets.c map_resets.c

INCLUDES=-I ./libft -I ./minilibx

LIBRARY=-L ./minilibx -lmlx -L libft -lft

FRAMEWORK=-framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) :
	make -C ./libft mclean
	cc $(INCLUDES) $(FILES) $(LIBRARY) $(FRAMEWORK)
