# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    testfill.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 13:26:41 by phakakos          #+#    #+#              #
#    Updated: 2019/11/27 12:36:05 by phakakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Simple test script for the Fillit project in 42 cursus (old)
# Does similar test to set in the evaluation.
# Creates it's own files, only this file is needed to run the test
# SHOULD BE PLACED IN THE FOLDER WITH THE MAKE FILE
# Created by phakakos @ Hive Helsinki, 2019

clear

# VARIABLE DECLATIONS

NORM=""
PROG=fillit
TESTFILE=input.ph
TESTOUT=output.ph

A=0
B=0
C=0
D=0
E=0
F=0
G=0
H=0
I=0
J=0
K=0
L=0
M=0
N=0
O=0
P=0
Q=0
R=0
S=0
T=0
U=0
V=0
W=0
X=0
Y=0
Z=0
DOT=0

# RESET BLOCK COUNTING
reset_alpha(){
A=0
B=0
C=0
D=0
E=0
F=0
G=0
H=0
I=0
J=0
K=0
L=0
M=0
N=0
O=0
P=0
Q=0
R=0
S=0
T=0
U=0
V=0
W=0
X=0
Y=0
Z=0
DOT=0
}

# DO NORM TEST
norm_test(){
	NORM=$(norminette | grep "Error\|Warning")
	if [[ $NORM == "" ]]
	then echo "No norm errors";
	else
	norminette
	fi
}

# MAKEFILE TEST
make_test(){
rtn=0
	if [ -f "Makefile" ]
then
PNAME=$(cat Makefile | grep "fillit")
	if [[ -z $"PNAME" ]]
	then echo "Program name wrong"; rtn--
	fi
MNAME=$(cat Makefile | grep "NAME[ ]\{0,1\}=")
ALL=$(cat Makefile | grep "all[ ]\{0,1\}:")
NAME=$(cat Makefile | grep "(NAME)[ ]\{0,1\}:")
CLEAN=$(cat Makefile | grep "clean[ ]\{0,1\}:")
RE=$(cat Makefile | grep "re[ ]\{0,1\}:")
rules=0
	if [ -z "$MNAME" ]
	then echo "NAME is missing"; rtn--
	else echo $MNAME; (( rules+=1 ))
	fi
	if [ -z "$ALL" ]
	then echo "ALL rule is missing"; rtn--
	else (( rules+=1 ))
	fi
	if [ -z "$NAME" ]
	then echo "NAME rule is missing"; rtn--
	else (( rules+=1 ))
	fi
	if [ -z "$CLEAN" ]
	then echo "CLEAN rule is missing"; rtn--
	else (( rules+=1 ))
	fi
	if [ -z "$RE" ]
	then echo "RE rule is missing"; rtn--
	else (( rules+=1 ))
	fi
	if [ $rules -eq 5 ]
	then echo "All rules found"; rtn=1
	fi
else
	echo "Makefile missing"; rtn--
fi
return rtn
}

check_output(){
reset_alpha
if [[ -z "$TESTOUT" ]]
then echo "Could not find output file, check for errors. Exiting"; exit
fi
while READ= read -r -n1 c
do
	[ "$c" == "Z" ] && (( Z++ ))
	[ "$c" == "X" ] && (( Y++ ))
	[ "$c" == "Y" ] && (( X++ ))
	[ "$c" == "W" ] && (( W++ ))
	[ "$c" == "V" ] && (( V++ ))
	[ "$c" == "U" ] && (( U++ ))
	[ "$c" == "T" ] && (( T++ ))
	[ "$c" == "S" ] && (( S++ ))
	[ "$c" == "R" ] && (( R++ ))
	[ "$c" == "Q" ] && (( Q++ ))
	[ "$c" == "P" ] && (( P++ ))
	[ "$c" == "O" ] && (( O++ ))
	[ "$c" == "N" ] && (( N++ ))
	[ "$c" == "M" ] && (( M++ ))
	[ "$c" == "L" ] && (( L++ ))
	[ "$c" == "K" ] && (( K++ ))
	[ "$c" == "J" ] && (( J++ ))
	[ "$c" == "I" ] && (( I++ ))
	[ "$c" == "H" ] && (( H++ ))
	[ "$c" == "G" ] && (( G++ ))
	[ "$c" == "F" ] && (( F++ ))
	[ "$c" == "E" ] && (( E++ ))
	[ "$c" == "D" ] && (( D++ ))
	[ "$c" == "C" ] && (( C++ ))
	[ "$c" == "B" ] && (( B++ ))
	[ "$c" == "A" ] && (( A++ ))
	[ "$c" == "." ] && (( DOT++ ))
done < "$TESTOUT"

cat -e $TESTOUT
echo ''
[ $DOT -ge 0] && { echo "Dots $DOT"; } 
[ $A -ge 0 ] && { echo "A $A"; }
[ $B -ge 0 ] && { echo "B $B"; }
[ $C -ge 0 ] && { echo "C $C"; }
[ $D -ge 0 ] && { echo "D $D"; }
[ $E -ge 0 ] && { echo "E $E"; }
[ $F -ge 0 ] && { echo "F $F"; }
[ $G -ge 0 ] && { echo "G $G"; }
[ $H -ge 0 ] && { echo "H $H"; }
[ $I -ge 0 ] && { echo "I $I"; }
[ $J -ge 0 ] && { echo "J $J"; }
[ $K -ge 0 ] && { echo "K $K"; }
[ $L -ge 0 ] && { echo "L $L"; }
[ $M -ge 0 ] && { echo "M $M"; }
[ $N -ge 0 ] && { echo "N $N"; }
[ $O -ge 0 ] && { echo "O $A"; }
[ $P -ge 0 ] && { echo "P $P"; }
[ $Q -ge 0 ] && { echo "Q $Q"; }
[ $R -ge 0 ] && { echo "R $R"; }
[ $S -ge 0 ] && { echo "S $S"; }
[ $T -ge 0 ] && { echo "T $T"; }
[ $U -ge 0 ] && { echo "U $U"; }
[ $V -ge 0 ] && { echo "V $V"; }
[ $W -ge 0 ] && { echo "W $W"; }
[ $X -ge 0 ] && { echo "X $X"; }
[ $Y -ge 0 ] && { echo "Y $Y"; }
[ $Z -ge 0 ] && { echo "Z $Z"; }
}

cont_press(){
	read -t 1 -s -r -n 10000 discard
	read -n 1 -s -r -p "Press anything to continue..."
	echo "\n"
}

test_error(){
cat -e $TESTFILE
echo ''
./$TESTER $TESTFILE
cont_press
clear
}

test_input(){
./$TESTER $TESTFILE > $TESTOUT
check_output
cont_press
clear
}

run_test(){
echo "Welcome to the Fillit tester."; echo ''
if [[ -z "author" ]]
then echo "No author file found, exiting."; exit
else
	cat -e author
fi
makefile=make_test
if [[ makefile -lt 1 ]]
	then echo "Makefile is wrong, exiting"; exit
	else
		make re; make clean; clean
fi
if [[ -z "$PROG" ]]
then echo "could not find compiled program, exiting"; exit
else
	echo "Initializing done. Next tests"; cont_press; clear
fi

# ERROR TESTING

# usage prompt
echo "Usage test"; echo ''
./$TESTER
cont_press
clear

# no block
echo "....\n....\n....\n....\n...." > $TESTFILE
echo "Starting with bad inputs." ; echo ''; test_error

# usage prompt
./$TESTER
cont_press
clear

# extra line
echo "...#\n...#\n...#\n...#\n." > $TESTFILE
test_err

# input too small
echo "#...\n#..\n#...\n#..." > $TESTFILE
test_err

# too big block
echo "...#\n..##\n...#\n...#\n" > $TESTFILE
test_err

clear

# empty file
printf %s "" > $TESTFILE
test_err

# invalid characters
echo "---#\n---#\n---#\n---#" > $TESTFILE
test_err

echo "...i\n...i\n...i\n...i" > $TESTFILE

# invalid block
echo "##..\n..##\n....\n...." > $TESTFILE
test_err

echo "Multiblock error testing"; echo ''

# one block too small

echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n..#" > $TESTFILE
test_err

# one block too big

echo "...#\n...#\n...#\n...#\n\n...#\n....#\n...#\n...#" > $TESTFILE
test_err

# extra line break between blocks
echo "...#\n...#\n...#\n...#\n\n\n...#\n...#\n...#\n...#" > $TESTFILE
test_err

# invalid character
echo "...#\n...#\n...#\n...#\n\n...a\n...#\n...#\n...#" > $TESTFILE
test_err

# too many blocks
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n" > $TESTFILE
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n" >> $TESTFILE
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#" >> $TESTFILE
test_err


# SOLVABLE INPUT TEST
# singles
echo "Testing with valid input, single block"
echo "...#\n...#\n...#\n...#" > $TESTFILE
test_input

echo "....\n....\n..##\n..##" > $TESTFILE
test_input

echo "#...\n#...\n##..\n...." > $TESTFILE
test_input

echo "....\n.#..\n##..\n#..." > $TESTFILE
test_input

# doubles
echo "Testing with valid input, two blocks"
echo "##..\n##..\n....\n....\n\n##..\n##..\n....\n...." > $TESTFILE
test_input

echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#" > $TESTFILE
test_input

echo "####\n....\n....\n....\n\n...#\n...#\n...#\n...#" > $TESTFILE
test_input

echo "....\n....\n...#\n.###\n\n####\n....\n....\n...." > $TESTFILE
test_input


echo "Why are you here? Just to suffer?"
}
run_test
