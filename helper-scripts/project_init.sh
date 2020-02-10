# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    project_init.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 18:10:52 by phakakos          #+#    #+#              #
#    Updated: 2020/02/10 14:48:21 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script designed to be used when starting a project.
# Should be placed in the root and can be called with ~./project_init.shi
# or added as an alias
# Made by phakakos @ Hive Helsinki, 2019

PWD=$(pwd)
# change to your own libft folder 
LIBFT=~/42/HiveHelsinki/libft
LIBD=$(diff --brief libft $LIBFT)

clear
echo "current folder is '$PWD'"
# Do you want to create an author file? Default value is just your username. WILL OVERWRITE EXISTING FILES
echo "Do you want to make author file?"
read -p "(y/n) " aut
while true
do
	if [[ $aut == "n" ]]
	then echo "Skipping"; echo ''; break
	elif [[ $aut == "y" ]]
	then echo "$USER" > author; echo ">Created author file"; echo ''; break
	else read -p "(y/n) " aut
	fi
done

# Do you want to export your libft folder. Checks if you already have the folder and if it is up-to-date
# Copies library from '.libft' folder in the same folder as the script.
if ([[ $LIBD == "" ]] && [ -d "libft" ]); then
	echo "Libft up to date $LIBD"
elif [ -d "libft" ] ; then
	echo "Libft already exists. Do you want to refresh it?"
	read -p "(y/n) " lib
	while true
	do
		if [[ $lib == "y" ]]
		then make -C $LIBFT fclean; rm -r libft; cp -r $LIBFT .; echo ">Copied to current folder"; break
		elif [[ $lib == "n" ]]
		then echo "No re-copy"; break
		else read -p "(y/n) " lib
		fi
	done
else
	echo "Do you want to copy libft?"
	read -p "(y/n) " lib
	while true
	do
		if [[ $lib == "y" ]]
		then make -C $LIBFT fclean; cp -r $LIBFT .; echo ">Copied library to current folder"; break
		elif [[ $lib == "n" ]]
		then echo "Skipping"; echo ''; break
		else read -p "(y/n) " lib
		fi
	done
fi
echo "Exiting"
