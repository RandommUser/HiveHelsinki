# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    testfill.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 13:26:41 by phakakos          #+#    #+#              #
#    Updated: 2019/12/11 19:50:21 by phakakos         ###   ########.fr        #
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
TESTER=fillit
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
	if [ -f "Makefile" ]
then
PNAME=$(cat Makefile | grep "fillit")
	if [[ -z $"PNAME" ]]
	then echo "Program name wrong";
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

check_output(){
reset_alpha
if [[ -z "$TESTOUT" ]]
then echo "Could not find output file, check for errors. Exiting"; exit
fi
while READ= read -r -n1 c
do
	[ "$c" == "Z" ] && (( Z=$[$Z + 1] ))
	[ "$c" == "X" ] && (( Y=$[$Y + 1] ))
	[ "$c" == "Y" ] && (( X=$[$X + 1] ))
	[ "$c" == "W" ] && (( W=$[$W + 1] ))
	[ "$c" == "V" ] && (( V=$[$V + 1] ))
	[ "$c" == "U" ] && (( U=$[$U + 1] ))
	[ "$c" == "T" ] && (( T=$[$T + 1] ))
	[ "$c" == "S" ] && (( S=$[$S + 1] ))
	[ "$c" == "R" ] && (( R=$[$R + 1] ))
	[ "$c" == "Q" ] && (( Q=$[$Q + 1] ))
	[ "$c" == "P" ] && (( P=$[$P + 1] ))
	[ "$c" == "O" ] && (( O=$[$O + 1] ))
	[ "$c" == "N" ] && (( N=$[$N + 1] ))
	[ "$c" == "M" ] && (( M=$[$M + 1] ))
	[ "$c" == "L" ] && (( L=$[$L + 1] ))
	[ "$c" == "K" ] && (( K=$[$K + 1] ))
	[ "$c" == "J" ] && (( J=$[$J + 1] ))
	[ "$c" == "I" ] && (( I=$[$I + 1] ))
	[ "$c" == "H" ] && (( H=$[$H + 1] ))
	[ "$c" == "G" ] && (( G=$[$G + 1] ))
	[ "$c" == "F" ] && (( F=$[$F + 1] ))
	[ "$c" == "E" ] && (( E=$[$E + 1] ))
	[ "$c" == "D" ] && (( D=$[$D + 1] ))
	[ "$c" == "C" ] && (( C=$[$C + 1] ))
	[ "$c" == "B" ] && (( B=$[$B + 1] ))
	[ "$c" == "A" ] && (( A=$[$A + 1] ))
	[ "$c" == "." ] && (( DOT=$[$DOT + 1] ))
done < "$TESTOUT"

cat -e $TESTOUT
echo ''
[ $DOT -ge 0 ] && { echo "Dots $DOT"; } 
[ $A -gt 0 ] && { echo "A $A"; }
[ $B -gt 0 ] && { echo "B $B"; }
[ $C -gt 0 ] && { echo "C $C"; }
[ $D -gt 0 ] && { echo "D $D"; }
[ $E -gt 0 ] && { echo "E $E"; }
[ $F -gt 0 ] && { echo "F $F"; }
[ $G -gt 0 ] && { echo "G $G"; }
[ $H -gt 0 ] && { echo "H $H"; }
[ $I -gt 0 ] && { echo "I $I"; }
[ $J -gt 0 ] && { echo "J $J"; }
[ $K -gt 0 ] && { echo "K $K"; }
[ $L -gt 0 ] && { echo "L $L"; }
[ $M -gt 0 ] && { echo "M $M"; }
[ $N -gt 0 ] && { echo "N $N"; }
[ $O -gt 0 ] && { echo "O $O"; }
[ $P -gt 0 ] && { echo "P $P"; }
[ $Q -gt 0 ] && { echo "Q $Q"; }
[ $R -gt 0 ] && { echo "R $R"; }
[ $S -gt 0 ] && { echo "S $S"; }
[ $T -gt 0 ] && { echo "T $T"; }
[ $U -gt 0 ] && { echo "U $U"; }
[ $V -gt 0 ] && { echo "V $V"; }
[ $W -gt 0 ] && { echo "W $W"; }
[ $X -gt 0 ] && { echo "X $X"; }
[ $Y -gt 0 ] && { echo "Y $Y"; }
[ $Z -gt 0 ] && { echo "Z $Z"; }
}

cont_press(){
	read -t 1 -s -r -n 10000 discard
	read -n 1 -s -r -p "Press anything to continue..."
	echo "\n"
}

print_intro(){
clear
echo "   ____ ____        ____                                ____             ____\n /___ /___ /|     /___ /|                              |\ ___\          |\ ___\\\\\n|    |    | |    |    | |        ___       ___         | |    |     ___ | |    |___\n|____|____|/     |____|/       /___ /|    |\ ___\       \|____|    |\ ___\|____| ___\ \n|    | |____        ____      |    | |    | |    |       ____      | |    |    |    |\n|____|/___ /|     /___ /|     |____|/|    |\|____|     |\ ___\      \|____|____|____|\n|    |    | |    |    | |     |    | |    | |    |     | |    |         | |    |\n|____|____|/     |____|/|     |____|/|    |\|____|     |\|____|         |\|____|\n|    | |         |    | |     |    | |    | |    |     | |    |         | |    |\n|____|/|         |____|/|     |____|/|    |\|____|     |\|____|         |\|____|\n|    | |         |    | |     |    | |    | |    |     | |    |         | |    |\n|____|/          |____|/      |____|/      \|____|      \|____|          \|____|\n"
}


test_error(){
cat -e $TESTFILE
echo ''
printf %s "output: "
./$TESTER $TESTFILE
cont_press
print_intro
}

test_input(){
cat -e $TESTFILE
echo "output:";
./$TESTER $TESTFILE > $TESTOUT
check_output
cont_press
print_intro
}

test_speed(){
time ./$TESTER $TESTFILE > $TESTOUT
check_output
cont_press
print_intro
}

run_test(){
print_intro
echo "Welcome to the Fillit tester."; echo ''
if [[ ! -f "author" ]]
then echo "No author file found, exiting."; exit
else
	cat -e author
fi
makefile=$(make_test)
#echo "$makefile"
if [[ makefile ==  "All rules found!" ]]
	then echo "Makefile is wrong, exiting"; exit
	else
		echo "All makefile rules found"; cont_press
		make re; make clean; print_intro
fi
if [[ ! -f "$PROG" ]]
then echo "could not find compiled program, exiting"; exit
else
	echo "Initializing done. Next tests"; cont_press; print_intro
fi

# ERROR TESTING
# usage prompt
echo "Usage test"; echo ''
./$TESTER 
cont_press
./$TESTER hello world
cont_press
print_intro

# no block
echo "....\n....\n....\n...." > $TESTFILE
echo "Starting with bad inputs." ; echo ''; test_error

echo "####\n####\n####\n####" > $TESTFILE
test_error

# extra line
echo "...#\n...#\n...#\n...#\n." > $TESTFILE
test_error

# input too small
echo "#...\n#..\n#...\n#..." > $TESTFILE
test_error

# too big block
echo "...#\n..##\n...#\n...#" > $TESTFILE
test_error
# valid block and then more hashes
echo "...#\n...#\n..##\n...#" > $TESTFILE
test_error

# no linebreak finish
echo "This can work (no linebreak at the end)"
echo "...#\n...#\n...#" > $TESTFILE
printf %s "...#" >> $TESTFILE
test_error

# empty file
echo "(Empty file)"
printf %s "" > $TESTFILE
test_error

# invalid characters
echo "---#\n---#\n---#\n---#" > $TESTFILE
test_error

echo "...i\n...i\n...i\n...i" > $TESTFILE

# invalid block
echo "##..\n..##\n....\n...." > $TESTFILE
test_error

# invalid block, blocks "connected" in string
echo "..##\n##..\n....\n...." > $TESTFILE
test_error

echo "Multiblock error testing"; echo ''

# one block too small
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n..#" > $TESTFILE
test_error

# one line too small
echo "...#\n...#\n...#\n...#\n\n....\n####\n...." > $TESTFILE
test_error

# one block too big
echo "...#\n...#\n...#\n...#\n\n...#\n....#\n...#\n...#" > $TESTFILE
test_error

echo "...#\n...#\n...#\n...#\n\n...#\n...#\n..##\n...#" > $TESTFILE
test_error

# extra line break between blocks
echo "...#\n...#\n...#\n...#\n\n\n...#\n...#\n...#\n...#" > $TESTFILE
test_error

# invalid character
echo "...#\n...#\n...#\n...#\n\n...a\n...#\n...#\n...#" > $TESTFILE
test_error

# too many blocks
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n" > $TESTFILE
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n" >> $TESTFILE
echo "...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#\n\n...#\n...#\n...#\n...#" >> $TESTFILE
test_error


# SOLVABLE INPUT TEST
# singles
echo "Testing with valid input, single block"
echo "...#\n...#\n...#\n...#" > $TESTFILE # I block
test_input

echo "....\n....\n####\n...." > $TESTFILE # I block flat
test_input

echo "....\n....\n..##\n..##" > $TESTFILE # square
test_input

echo "#...\n#...\n##..\n...." > $TESTFILE # L
test_input

echo "....\n..#.\n..#.\n.##." > $TESTFILE # L reverse
test_input

echo "...#\n.###\n....\n...." > $TESTFILE # L down
test_input

echo "....\n....\n.#..\n.###" > $TESTFILE # L down reverse
test_input

echo ".##.\n..#.\n..#.\n...." > $TESTFILE # L upsidedown
test_input

echo "....\n..##\n..#.\n..#." > $TESTFILE # L upsidedown reverse
test_input

echo "....\n....\n..#.\n###." > $TESTFILE # L r-down
test_input

echo "....\n.###\n...#\n...." > $TESTFILE # L r-down reverse
test_input

echo "....\n.#..\n##..\n#..." > $TESTFILE # S down
test_input

echo ".#..\n.##.\n..#.\n...." > $TESTFILE # S down reverse
test_input

echo "....\n....\n.##.\n..##" > $TESTFILE # S flat reverse
test_input

echo ".##.\n##..\n....\n...." > $TESTFILE # S flat
test_input

echo "###.\n.#..\n....\n...." > $TESTFILE # T 1
test_input

echo "....\n..#.\n.###\n...." > $TESTFILE # T 2
test_input

echo "....\n...#\n..##\n...#" > $TESTFILE # T 3
test_input

echo "....\n....\n###.\n.#.." > $TESTFILE # T 4
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

echo "....\n##..\n.#..\n.#..\n\n....\n####\n....\n....\n\n#...\n###.\n....\n....\n\n....\n##..\n.##.\n...." > $TESTFILE
test_input

echo "Speed test, evaluation test"
echo "...#\n...#\n...#\n...#\n\n....\n....\n....\n####\n\n.###\n...#\n....\n....\n\n....\n..##\n.##.\n....\n\n....\n.##.\n.##.\n....\n\n....\n....\n##..\n.##.\n\n##..\n.#..\n.#..\n...." > $TESTFILE
test_speed



echo "Why are you here? Just to suffer?"
}
run_test
