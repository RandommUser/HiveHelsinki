# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cnorm.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 15:40:35 by phakakos          #+#    #+#              #
#    Updated: 2020/11/02 16:01:15 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
LIME_YELLOW=$(tput setaf 190)
POWDER_BLUE=$(tput setaf 153)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
BLINK=$(tput blink)
REVERSE=$(tput smso)
UNDERLINE=$(tput smul)

ERRORC=$RED
WARNC=$YELLOW
GOOD=$GREEN

NORM=$(norminette $1)
NORME="Norme: "
COMP_MSG="may not compile"
INVA_MSG="Not a valid file"
ERR_MSG="Error ("

OUTPUT=""

printf "%s\n" "${ERRORC}error${NORMAL} on this ${BRIGHT}line${NORMAL}"
printf "%s\n" "${WARNC}warning${NORMAL} on this ${REVERSE}line${NORMAL}"
printf "%s\n" "${GOOD}okay${NORMAL} on this ${UNDERLINE}line"

for line in $NORM
do 
NORM_FILE=$(echo "$line" | grep "$NORME");
WARNING=$(echo "$line"  | grep "$COMP_MSG");
ERROR=$(echo "$line" | grep "$ERR_MSG");
INVA=$(echo "$line" | grep "$INVA_MSG");

	if [[ $NORM_FILE != "" ]]
	then # insert output.append()
	fi
done


