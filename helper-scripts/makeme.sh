# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makeme.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 13:52:58 by phakakos          #+#    #+#              #
#    Updated: 2020/02/14 18:32:31 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script to create a Makefile
# Auto solves .c, .a and folders into right categories
# Made by phakakos, Hive Helsink 2020

CNAME="SRCS"
ONAME="BIGO"
INCNAME="INC"
LIBNAME="LIB"
FLAGS="-Wall -Wextra -Werror"

NAME=""
CFILES=""
OFILES="\$($CNAME:.c=.o)"
LIB=""
INCLUDES=""
EMAKE=""

print_make(){
if [[ -f Makefile ]]
then mv Makefile Makefile1
fi

echo "NAME=$NAME" > Makefile
echo "$CNAME=$CFILES" >> Makefile
echo "$ONAME=$OFILES" >> Makefile
echo "$INCNAME=$INCLUDES" >> Makefile
echo "$LIBNAME=$LIB" >> Makefile
echo "\n\nall : \$(NAME)" >> Makefile
echo "" >> Makefile
echo "\$(NAME) :" >> Makefile
echo "$EMAKE"  >> Makefile
echo "\tgcc -c $FLAGS \$($CNAME) \$($INCNAME)" >> Makefile
echo "\tgcc $FLAGS -o \$(NAME) \$($ONAME) \$($LIBNAME)" >> Makefile
echo "" >> Makefile
echo "clean :" >> Makefile
echo "\trm -f \$($ONAME)" >> Makefile
echo "" >> Makefile
echo "fclean : clean" >> Makefile
echo "\trm -f \$(NAME)" >> Makefile
echo "" >> Makefile
echo "re: fclean all" >> Makefile
echo "Makefile created"; exit
}


if [[ $1 == "" ]]
then echo "usage 'makeme.sh' 'program name' source_file.c/a source_folder"
	echo "Support direct link to .a library or just the folder. Include folders will be included with just a folder"
	exit
fi

for arg in "$@"
do
	TEST=""
	if [[ $NAME == "" ]]
	then NAME="$arg"; continue;
	fi
	TEST=$(echo "$arg" | grep ".c")
	if [[ $TEST	!= "" ]] 						# Input is a .c file
		then 
			if [[ -f $arg ]] 					# It exists
			then CFILES+="$arg "; continue
			else echo "$arg is not an existing .c file"; continue
		fi
	fi
	if [[ -d $arg ]]										# Input is a folder
	then INCLUDES+="-I $arg "
		if [[ -f $arg/Makefile ]]							# If there is a Makefile inside the folder
		then TEST=$(cat $arg/Makefile | grep "NAME" | grep "\.a$")
			if [[ $TEST  != "" ]]							# The Makefile compiles an .a file, add it to EMAKE to make before compling
			then 
				TEST=$(echo "$arg" | grep "^[\.]\{1,2\}\/\|^~\/")
				if [[ $TEST != "" ]]						# if the arg has './' , '../'  or '~/' at the of the argument, otherwise at "./"
				then LIB+="-L $arg "; EMAKE+="\tmake -C $arg\n";
				else
					LIB+="-L ./$arg "; EMAKE+="\tmake -C ./$arg\n";
				fi
				TEST=$(cat $arg/Makefile | grep "\.a$" | sed -E "s/^.*=(.*)\.a/\1/g" | sed 's/ //g' | sed 's/^lib//g') # get the library name
				LIB+="-l$TEST "
				continue
			fi
		fi
	continue
	fi
	TEST=$(echo "$arg" | grep "\.a")
	if [[ $TEST != "" ]]						# Input is an a file
	then
		if [[ -f $arg ]]						# it exists
		then 
			TEST=$(echo "$arg" | grep "^[\.]\{1,2\}\/\|^~\/")		# starts with './', '../' or '~/'
			if [[ $TEST == "" ]]				# add the start ^
			then arg="./$arg"
			fi
			TEST=$(echo "$arg" | sed -E "s/(^.*)\/.*\.a$/\1/g")
			INCLUDES+="-I $TEST "
			LIB+="-L $TEST "
			TEST=$(echo "$arg" | sed -E "s/^.*\/(.*)\.a$/\1/g" | sed "s/^lib//g")
			LIB+="-l$TEST "
		else echo "$arg is not an existing .a file"
		fi
		continue
	fi
done

echo "\n ..VARIABLES..\n"

echo "Name = '$NAME'"
echo "CFILES = '$CFILES'"
echo "OFILES = '$OFILES'"
echo "LIB = '$LIB'"
echo "INCLUDES = '$INCLUDES'"
echo "EMAKE = '$EMAKE'"

print_make
