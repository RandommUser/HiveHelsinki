# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cnorm.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 15:40:35 by phakakos          #+#    #+#              #
#    Updated: 2020/11/03 14:51:21 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# A formatting wrapper for Norminette 2.0
# Inspired by -- on 42 Slack
# Recommended to be added to alias or root to be called easily
# Tested to work on zsh 5.3, bash 3.2.57 on iMac 10.14.6
# Made by phakakos, Hive Helsinki 2020

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

# Coloring for different outputs
ERRORC=$RED
WARNC=$YELLOW
INVAC=$CYAN
GOOD=$GREEN
NAMEC=$BLUE$BRIGHT

NORM=""
VERBOSE=""

main(){
# Parts of the norminette output to differenciate the different outputs
NORME="Norme: "
COMP_MSG="may not compile"
INVA_MSG="Not a valid file"
ERR_MSG="Error ("

# in case of "file may not compile" the norminette will not print out norm errors.
WARN_MESSAGE="THIS MAY RESULT IN NORM-ERRORS BEING IGNORED, CHECK MANUALLY"

OUTPUT=""
STATE=""
NEXT=""

# different states
NEWFILE="NEWFILE"
WARNING="WARNING"
ERROR="ERROR"
INVALID="INVALID"

while IFS= read -r line
do 
	# check norminette output
	# Reformat file name line to only print out the 'path/file'
	NORM_FILE=$(echo "$line" | grep "$NORME" | sed "s/$NORME//" | sed 's/.\/ //');
	WARNING=$(echo "$line"  | grep "$COMP_MSG");
	ERROR=$(echo "$line" | grep "$ERR_MSG");
	INVA=$(echo "$line" | grep "$INVA_MSG");
	if [[ $NORM_FILE != "" ]] # line is the name
	then 
	OUTPUT+=$NEXT; NEXT=""
		if [[ $STATE == $NEWFILE ]] # back to back names == no errors
		then printf -v append "\t%s\n" "${GOOD}All OK${NORMAL}";
		NEXT+=$append
		fi
	printf -v append "%s\n" "${NAMEC}>>  $NORM_FILE${NORMAL}";
	STATE=$NEWFILE; NEXT+=$append;
	elif [[ $ERROR != "" ]] # Error line
	then append=$(echo " $line" | sed "s/$ERR_MSG//" | sed -e 's/\(line [0-9]\{1,\}\)): /\1'$'\t\t''/' | sed $'s/, /\t/' | sed $'s/): /\t/')
	printf -v add "\t%s\t%s\n" "${BRIGHT}${ERRORC}Error${NORMAL}" "$append"
	NEXT+=$add
	STATE=$ERROR
	elif [[ $WARNING != "" ]] # Warning/May not compile line
	then append=$(echo " $line" | sed 's/Warning: //')
	printf -v add "\t%s\t\t%s\n\t%s\n" "${BRIGHT}${WARNC}Warning${NORMAL}" "$append" "${REVERSE}${WARNC}$WARN_MESSAGE${NORMAL}"
	NEXT+=$add
	STATE=$WARNING
	elif [[ $INVA != "" ]] # Invalid file
	then 
		if [[ $VERBOSE != "" ]]
		then append=$(echo " $line" | sed 's/Warning: //')
			printf -v add "\t%s\t\t%s\n" "${INVAC}Warning${NORMAL}" "$append"
			NEXT+=$add
			STATE=$INVALID
		else NEXT=""
		fi
	fi
done <<< "$NORM"

# If the last file does not have errors an extra check is needed
if [[ $STATE == $NEWFILE && $NEXT != "" ]]
	then printf -v append "\t%s\n" "${GOOD}All OK${NORMAL}";
	NEXT+=$append;
fi
OUTPUT+=$NEXT;
# Print out the formatted output
printf "%s" "$OUTPUT"
}

# if only script is called, print usage
# -v to not skip invalid files
if [[ ${@:1} == "" ]]
then printf "%s\n" "${NAMEC}usage:${NORMAL} $0 [${BRIGHT}-v ${NORMAL}'print full output']${BRIGHT} norminette input${NORMAL}"; exit;
elif [[ $1 == "-v" ]]
then NORM=$(norminette ${@:2}); VERBOSE="TRUE"
else NORM=$(norminette ${@:1})
fi
main
exit