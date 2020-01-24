# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 16:09:54 by phakakos          #+#    #+#              #
#    Updated: 2020/01/24 17:49:49 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tester for ft_printf in the 42 cursur (old)
# Does various tests
# Creates and compiles two different mains to compare the outputs
# SHOULD BE PLACED IN THE ROOT
# Created by phakakos @ Hive Helsink, 2020

clear

NORM=""
PROG=libftprintf.a
OGTESTER=ogf
FTTESTER=userf
OGMAIN=printf.c
FTMAIN=printft.c






print_fancy(){                                                                           
	echo "\t                                                               ##### ##    "
	echo "\t                          #                                 ######  /### / "
	echo "\t                         ###                     #         /#   /  /  ##/  "
	echo "\t                          #                     ##        /    /  /    #   "
	echo "\t                                                ##            /  /         "
	echo "\t   /###    ###  /###    ###     ###  /###     ########       ## ##         "
	echo "\t  / ###  /  ###/ #### /  ###     ###/ #### / ########        ## ##         "
	echo "\t /   ###/    ##   ###/    ##      ##   ###/     ##           ## ######     "
	echo "\t##    ##     ##           ##      ##    ##      ##           ## #####      "
	echo "\t##    ##     ##           ##      ##    ##      ##           ## ##         "
	echo "\t##    ##     ##           ##      ##    ##      ##           #  ##         "
	echo "\t##    ##     ##           ##      ##    ##      ##              #          "
	echo "\t##    ##     ##           ##      ##    ##      ##          /####          "
	echo "\t#######      ###          ### /   ###   ###     ##         /  #####        "
	echo "\t######        ###          ##/     ###   ###     ##       /    ###         "
	echo "\t##                                                        #                "
	echo "\t##                                                         ##              "
	echo "\t##                                                                         "
	echo "\t ##                                                              "
}

print_intro(){
	echo "#############"
	echo "#############"
	echo "####"
	echo "####"
	echo "#########"
	echo "#########"
	echo "####"
	echo "####"
	echo "####"
	echo "####"
	echo "####"
}


norm_test(){
	NORM=$(norminette | grep "Error\|Warning")
	if [[ $NORM == "" ]]
	then echo "No norm errors";
	else
	norminette
	fi
}

auth_test(){
	# AUTHOR FILE CHECK
echo "~~~Checking author file~~~"
echo ''
if [ -f "author" ]
then
	file='author'
	while read line ; do
		if [[ $line == $USERN ]]
		then echo "user found"; echo ''
		else echo "$line $USERN"
		fi
	done < $file
else	echo "no author file"
fi
}

# MAKEFILE TEST
make_test(){
	if [ -f "Makefile" ]
then
PNAME=$(cat Makefile | grep "fillit")
	if [[ -z $"PNAME" ]]
	then echo "Library name wrong";
	fi
MNAME=$(cat Makefile | grep "NAME[ ]\{0,1\}=")
ALL=$(cat Makefile | grep "all[ ]\{0,1\}:")
NAME=$(cat Makefile | grep "(NAME)[ ]\{0,1\}:")
CLEAN=$(cat Makefile | grep "clean[ ]\{0,1\}:")
RE=$(cat Makefile | grep "re[ ]\{0,1\}:")
rules=0
	if [ -z "$MNAME" ]
	then echo "NAME is missing"
	else rules=$[rules + 1]
	fi
	if [ -z "$ALL" ]
	then echo "ALL rule is missing"
	else  rules=$[rules + 1]
	fi
	if [ -z "$NAME" ]
	then echo "NAME rule is missing"
	else rules=$[rules + 1]
	fi
	if [ -z "$CLEAN" ]
	then echo "CLEAN rule is missing"
	else rules=$[rules + 1]
	fi
	if [ -z "$RE" ]
	then echo "RE rule is missing"
	else rules=$[rules + 1]
	fi
	if [ $rules -eq 5 ]
	then echo "All rules found!";
	fi
else
	echo "Makefile missing"
fi
}

cont_press(){
	read -t 1 -s -r -n 10000 discard
	read -n 1 -s -r -p "Press anything to continue..."
	echo "\n"
}






run_test(){
	print_fancy
printf %s "ft_printf("
read TEST
echo "ft_printf($TEST); Run this? [yes/no]"
printf %s "$TEST" | read -p TEST
}

run_test
