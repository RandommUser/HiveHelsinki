# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makeme.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 13:52:58 by phakakos          #+#    #+#              #
#    Updated: 2020/02/14 20:19:03 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script to create a Makefile
# Should be added as alias or placed to the root for easy use
# Auto solves .c, .a and folders into right categories
# Made by phakakos, Hive Helsinki 2020


# Set the names of the different variables in the Makefile
CNAME="SRCS"				# all the .c files
ONAME="BIGO"				# all the .o files
INCNAME="INC"				# include folders
LIBNAME="LIB"				# library folders
FRAMEWORKNAM="FRAMEWORK"	# framework name
FLAGSNAME="FLAGS"			# compile flags

# Parse parameters
FLAGS="-Wall -Wextra -Werror"		# flags
NAME=""								# output name
CFILES=""							# .c files
OFILES="\$($CNAME:.c=.o)"			# set the .c files into .o files
LIB=""								# libraries
INCLUDES=""							# included folders
EMAKE=()							# list of libraries folders to run 'make' in
FRAMEWORK=""						# mlx framework flags


# Create the makefile
print_make(){
# move old makefile to Makefile1
if [[ -f Makefile ]]
then mv Makefile Makefile-$(date +%s); echo "Renamed old Makefile"
fi

echo "NAME=$NAME" > Makefile					# Write variables to Makefile
echo "$CNAME=$CFILES" >> Makefile
echo "$ONAME=$OFILES" >> Makefile
echo "$INCNAME=$INCLUDES" >> Makefile
echo "$LIBNAME=$LIB" >> Makefile
echo "$FLAGSNAME=$FLAGS" >> Makefile
echo "$FRAMEWORKNAM=$FRAMEWORK" >> Makefile
echo "\n\nall : \$(NAME)" >> Makefile
echo "" >> Makefile
echo "\$(NAME) :" >> Makefile
if [[ $EMAKE != "" ]]							# library make
then 
	for folder in ${EMAKE[@]}
	do
		echo "\tmake -C $folder" >> Makefile	
	done
fi
echo "\tgcc -c \$($FLAGSNAME) \$($CNAME) \$($INCNAME)" >> Makefile
TEST=$(echo "$NAME" | grep "\.a$")
if [[ $TEST == "" ]]							# if the desired output file is an .a file, change the final compilation
then echo "\tgcc \$($FLAGSNAME) -o \$(NAME) \$($ONAME) \$($LIBNAME) \$($FRAMEWORKNAM)" >> Makefile
else 
	echo "\tar rc \$(NAME) \$($ONAME)" >> Makefile; echo "\tranlib \$(NAME)" >> Makefile
fi
echo "" >> Makefile
echo "clean :" >> Makefile
if [[ $EMAKE != "" ]]							# library clean
then 
	for folder in ${EMAKE[@]}
	do
		echo "\tmake -C $folder clean" >> Makefile	
	done		
fi
echo "\trm -f \$($ONAME)" >> Makefile
echo "" >> Makefile
echo "fclean : clean" >> Makefile
if [[ $EMAKE != "" ]]							# library fclean
then 
	for folder in ${EMAKE[@]}
	do
		echo "\tmake -C $folder fclean" >> Makefile	
	done
fi
echo "\trm -f \$(NAME)" >> Makefile
echo "" >> Makefile
echo "re: fclean all" >> Makefile
echo "Makefile created"; exit
}

# usage
if [[ ${@:1} == "" ]]
then echo "usage $0 'program name' source_file.c/a source_folder"
	echo "Support direct link to .a library or just the folder. Include folders will be included with just a folder"
	exit
fi

# Loop thru all the parameters
for arg in "${@:1}"
do
	TEST=""
	if [[ $NAME == "" ]]
	then NAME="$arg"; continue;
	fi
	if [[ $arg == "-mlx" ]]						# mlx framework tag
	then FRAMEWORK+="-framework OpenGL -framework AppKit "; continue;
	fi
	TEST=$(echo "$arg" | grep ".c")
	if [[ $TEST	!= "" ]] 						# Input is a .c file
		then 
			if [[ -f $arg ]] 					# It exists
			then 
				if [[ $CFILES != "" ]]
				then printf -v add "%s\n\t" "\\"
				CFILES+=$add;
				fi
			#printf -v add "%s" "$arg"
			CFILES+=$arg; continue
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
				then LIB+="-L $arg "; EMAKE+=( "$arg" );
				else
					LIB+="-L ./$arg "; EMAKE+=( "./$arg" );
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
