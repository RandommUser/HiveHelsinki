# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    githandler.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/11 19:39:53 by phakakos          #+#    #+#              #
#    Updated: 2020/03/11 20:26:07 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Shell script to handle multiple git commands in a single line
# does not edit commit message for already committed files
# can handle multiple different different adds, commits and pushes
# Made by phakakos @ Hive Helsinki, 2020



gitcheck(){
# Check if in a git folder
GIT=$(git status 2> /dev/null);
if [[  $GIT == "" ]]
then echo "Not in a git folder"; exit;
fi
}

if [[ $1 == "" ]]
then echo "usage $0 (files to add) [-m ("'"'"commit message"'"'")] [-p (push)]"; exit
fi
gitcheck;
mess="no";

for arg in "$@"
do
	if [[ $mess == "yes" ]]
	then git commit -m "$arg"; mess="no"; continue
	elif [[ $arg == "-m" ]]
	then mess="yes"; continue
	elif [[ -f $arg ]]
	then git add $arg; continue
	elif [[ -d $arg ]]
	then git add $arg/*; continue
	elif [[ $arg == "-p" ]]
	then git push; continue
	else
	echo "input '$arg' was not valid file/folder/flag";
	fi
done
