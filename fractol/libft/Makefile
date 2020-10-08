# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 19:32:09 by phakakos          #+#    #+#              #
#    Updated: 2020/02/28 19:42:10 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = 
FLAGS = -Wall -Wextra -Werror
SRCS = ft_abs.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c \
	   ft_iswspace.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
	   ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
	   ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
	   ft_nbrlen.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
	   ft_puterr.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
	   ft_sizeofchar.c ft_sizeofint.c ft_skipempty.c ft_strcat.c ft_strchr.c \
	   ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strcreate.c ft_strdel.c ft_strdup.c \
	   ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	   ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
	   ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
	   ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_strclen.c \
	   ft_strrclen.c ft_putpointer.c get_next_line.c ft_strarrdel.c ft_rgb.c \
	   ft_chrcount.c ft_itoa_base.c ft_atoi_base.c ft_power_to.c ft_keys.c \
	   ft_keys2.c ft_strnchr.c ft_strrep.c ft_vecn.c ft_mat4_pro.c ft_matn.c ft_mat4.c \
	   ft_vec4.c ft_mat4_trans.c ft_matn_ini.c ft_strcont.c
BIGO := $(SRCS:.c=.o)

all : $(NAME)

$(NAME) :
		gcc $(FLAGS) $(INC) $(SRCS) -c
		ar rc $(NAME) $(BIGO)
		ranlib $(NAME)

mclean: fclean all clean
		make clean
clean :
		rm -f $(BIGO)

fclean : clean
		rm -f $(NAME)

re : fclean all
