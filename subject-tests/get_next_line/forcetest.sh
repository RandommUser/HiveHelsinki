# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    forcetest.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/26 18:51:35 by phakakos          #+#    #+#              #
#    Updated: 2019/11/26 21:04:51 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Test to go through different BUFF_SIZEs from x to y
# Made by phakakos @ Hive Helsinki, 2019


START=1  # Configure the starting buff size
END=1025 # Configure the last buff size + 1
TESTER=test_gnl
TESTFILE=force.ph
ORIGINAL=input.ph
DIFFERENCE=diff.ph

LIBFT="-L libft "
LIBFTI="-I libft/includes "
LFT="-lft "

make_libft(){
if [[ -f "libft/libft.a" ]]
	then echo "Library already compiled, skipping"; echo ''
	else make -C libft/ fclean && make -C libft/
fi
}

compile_main(){
	clang -Wall -Wextra -Werror $LIBFTI -o get_next_line.o -c get_next_line.c
	clang -Wall -Wextra -Werror $LIBFTI -o main.o -c main.c
	clang -o $TESTER -Wall -Wextra -Werror get_next_line.o main.o $LIBFTI $LIBFT $LFT
}

make_main(){
	echo "#include \"get_next_line.h\"\n#include <sys/types.h>\n#include <sys/types.h>\n#include <fcntl.h>\n#include <stdio.h>\n#include <unistd.h>\n" > main.c
	echo "static int	opensesame(char *name)\n{\n\treturn (open(name, O_RDONLY));\n}\n" >> main.c
	echo "static void	read_all(int fd)\n{\n\tchar *output;\n\tint rtn;\n\toutput = NULL;\n\twhile ((rtn = get_next_line(fd, &output)) > 0)\n\t{\n\t\tprintf(\"%s\\\n\",output);\n\tfree(output);\n\t}\n\n}\n" >> main.c
	echo "int	main(int argc, char **argv)\n{\n\tint fd;\n
\tif (argc == 1)\n\t\tread_all(0);\n\tif (argc == 2)\n\t{\n\t\tfd = opensesame(argv[1]);\n\t\tread_all(fd);\n\t\tclose(fd);\n\t}\n\tfd=0;\n\treturn (0);\n}" >> main.c
}

# Configure the original file to compare to

make_original(){
	echo "0123456789\n55555\n4444\n333\n22\n1\n\n0" > $ORIGINAL
}

change_buffer(){
	sed -i '' "s/#.define BUFF_SIZE.*/# define BUFF_SIZE $BUFF_S/" get_next_line.h
	compile_main
}

run_test(){
./$TESTER $ORIGINAL > $TESTFILE
CHECK=$(diff $ORIGINAL $TESTFILE)
echo "Buff size $BUFF_S diff: $CHECK" >> $DIFFERENCE
}

force_test(){
clear
# FIND REQUIRED FILES
if [[ ! -f get_next_line.c ]]
then echo "No get_next_line.c found. Place me in the subject folder. Exiting..."; exit
elif [[ ! -f get_next_line.h ]]
then echo "No get_next_line.h found. Place me in the subject folder. Exiting..."; exit
	else echo "Initializing...";
fi

if [[ -f "$DIFFERENCE" ]]
then rm $DIFFERENCE
fi
BUFF_S=$START
make_main
make_original
make_libft

while [[ $BUFF_S -lt $END ]]
do
	clear 
	echo "Testing with buffer $BUFF_S"
	change_buffer
	run_test
	BUFF_S=$[$BUFF_S + 1]
	clear
done

# Prints out the buffer sizes with differences. see the diff.ph for the full diff output

echo "Completed.\n Differences:"
cat "$DIFFERENCE" | grep ","
}

force_test
