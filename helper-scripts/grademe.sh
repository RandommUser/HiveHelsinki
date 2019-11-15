# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    grademe.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 17:01:25 by phakakos          #+#    #+#              #
#    Updated: 2019/11/15 17:43:17 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script made to test the folder's status before turning in the project.
# Should be placed in root and called with ~./grademe.sh
# Made by phakakos @ Hive Helsinki, 2019

clear
# Wait for norm test
echo "Initializing"


U="$USER"
GIT=".git"
NORM=$(norminette *.c *.h | grep "Error\|Warning")

clear
# Print out current folder
echo "Current location"
pwd
echo ''
# Print out git status if in a git root
echo "---git status---"
echo ''
if [ -d $GIT ]
then git status -s -u
else
   	echo "Not in a  git folder"
fi
echo ''
# Print out Norm errors
echo "...Checking norm..."
echo ''
	if [[ $NORM == "" ]]
	then echo "No norm errors";
	else 
	NORME=$(norminette *.c *.h)
		echo "$NORME"
	fi
echo ''
# Find rules set by the Norm and the file name
echo ">>>Checking the Makefile<<<"
echo ''
if [ -f "Makefile" ]
then
MNAME=$(cat Makefile | grep "NAME[ ]=")
ALL=$(cat Makefile | grep "all[ ]\{0,1\}:")
NAME=$(cat Makefile | grep "(NAME)[ ]\{0,1\}:")
CLEAN=$(cat Makefile | grep "clean[ ]\{0,1\}:")
RE=$(cat Makefile | grep "re[ ]\{0,1\}:")
rules=0
	if [ -z "$MNAME" ]
	then echo "NAME is missing"
	else echo $MNAME; (( rules+=1 ))
	fi
	if [ -z "$ALL" ]
	then echo "ALL rule is missing"
	else (( rules+=1 ))
	fi
	if [ -z "$NAME" ]
	then echo "NAME rule is missing"
	else (( rules+=1 ))
	fi
	if [ -z "$CLEAN" ]
	then echo "CLEAN rule is missing"
	else (( rules+=1 ))
	fi
	if [ -z "$RE" ]
	then echo "RE rule is missing"
	else (( rules+=1 ))
	fi
	if [ $rules -eq 5 ]
	then echo "All rules found"
	fi
else
	echo "Makefile missing"
fi
echo ''
# Check author file, prints out the file if there is more than your username
echo "~~~Checking author file~~~"
echo ''
if [ -f "author" ]
then
	file='author'
	while read line ; do
		if [[ $U == $line ]]
		then echo "user found"; echo ''
		else echo $line
		fi
	done < $file
else	echo "no author file"
fi
