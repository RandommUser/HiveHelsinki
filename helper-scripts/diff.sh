# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    diff.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 13:27:32 by phakakos          #+#    #+#              #
#    Updated: 2020/02/14 13:47:24 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Single line diff comparer. Excepted test output are to be one line.
# Handles empty lines, and takes the file from the parameter
# Done by phakakos, Hive Helsinki 2020

# You should not have tests with expected output as "empty" or change this value
test_line()
{
	if [[ $1 == "" ]]
	then echo "empty"
	else echo "$line"
	fi
}

if [[ -z $1 ]]
then echo "usage: sh diff.sh 'file'"; exit
elif [[ ! -f $1 ]]
then echo "File does not exist"; exit
fi

COMP=""
FILE=$1

while IFS= read -r line
do
	line=$(test_line "$line")
	if [[ $COMP == "" ]]
	then COMP="$line"
	else
		if [[ $COMP == $line ]]
		then echo "test passed"
		else echo "Diff: $COMP | $line"
		fi
		COMP=""
	fi
done < $FILE
