# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    project_init.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 18:10:52 by phakakos          #+#    #+#              #
#    Updated: 2019/11/15 17:43:23 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script designed to be used when starting a project.
# Should be placed in the root and can be called with ~./project_init.sh
# Made by phakakos @ Hive Helsinki, 2019

PWD=$(pwd)
LIBD=$(diff --brief libft ~/.libft)

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
	echo "Libft already in the folder. Do you want to refresh it?"
	read -p "(y/n) " lib
	while true
	do
		if [[ $lib == "y" ]]
		then rm -r libft; cp -r ~/.libft .; mv .libft libft; echo ">Copied to current folder"; break
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
		then cp -r ~/.libft .; mv .libft libft; echo ">Copied library to current folder"; break
		elif [[ $lib == "n" ]]
		then echo "Skipping"; echo ''; break
		else read -p "(y/n) " lib
		fi
	done
fi
echo "Exiting"
