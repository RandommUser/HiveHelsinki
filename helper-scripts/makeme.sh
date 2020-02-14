# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makeme.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 13:52:58 by phakakos          #+#    #+#              #
#    Updated: 2020/02/14 20:14:55 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script to create a Makefile
# Auto solves .c, .a and folders into right categories
# Made by phakakos, Hive Helsink 2020


# Set the names of the different variables in the Makefile
CNAME="SRCS"		# all the .c files
ONAME="BIGO"		# all the .o files
INCNAME="INC"		# include folders
LIBNAME="LIB"		# library folders

# Parse parameters
FLAGS="-Wall -Wextra -Werror"	# flags
NAME=""							# output name
CFILES=""						# .c files
OFILES="\$($CNAME:.c=.o)"		# set the .c files into .o files
LIB=""							# libraries
INCLUDES=""						# included folders
EMAKE=""						# make commands to compile libraries


# Create the makefile
print_make(){
# move old makefile to Makefile1
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
TEST=$(echo "$NAME" | grep "\.a$")
if [[ $TEST == "" ]]						# if the desired output file is an .a file, change the final compilation
then echo "\tgcc $FLAGS -o \$(NAME) \$($ONAME) \$($LIBNAME)" >> Makefile
else 
	echo "\tar rc \$(NAME) \$($ONAME)" >> Makefile; echo "\tranlib \$(NAME)" >> Makefile
fi
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

# usage
if [[ $1 == "" ]]
then echo "usage 'makeme.sh' 'program name' source_file.c/a source_folder"
	echo "Support direct link to .a library or just the folder. Include folders will be included with just a folder"
	exit
fi

# Loop thru all the parameters
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
				if [[ $TEST != "" ]]						# if the arg has './' , '../'  or '~/' at the of the argument, otherwise add "./"
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
			TEST=$(echo "$arg" | grep "^[\.]\{1,2\}\/\|^~\/")						# starts with './', '../' or '~/'
			if [[ $TEST == "" ]]													# add the start ^ if needed
			then arg="./$arg"
			fi
			TEST=$(echo "$arg" | sed -E "s/(^.*)\/.*\.a$/\1/g") 					# get the folder for the library
			INCLUDES+="-I $TEST "
			LIB+="-L $TEST "
			TEST=$(echo "$arg" | sed -E "s/^.*\/(.*)\.a$/\1/g" | sed "s/^lib//g")	# get the library name
			LIB+="-l$TEST "
		else echo "$arg is not an existing .a file"
		fi
		continue
	fi
done
print_make
