# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    githandler.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/11 19:39:53 by phakakos          #+#    #+#              #
#    Updated: 2020/03/11 20:12:44 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Shell script to handle multiple git commands in a single line
# Made by phakakos @ Hive Helsinki, 2020



gitcheck(){
# Check if in a git folder
GIT=$(git status 2> /dev/null);
if [[  $GIT == "" ]]
then echo "Not in a git folder"; exit;
fi
}

if [[ $1 == "" ]]
then echo "usage githandler.sh (files) [-m ("'"'"commit message"'"'")] [-p (push)]"; exit
fi

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
	fi
done
