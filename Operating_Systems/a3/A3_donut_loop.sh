#! /bin/sh

# Jason Downing
# Assignment 3
# Operating Systems - COMP.3080
# 10/24/2016

# This file is from Professor Moloney's cs308 directory.
# http://www.cs.uml.edu/~bill/cs308/A3_donut_loop.sh

# usage: A1_linux_donut_loop.sh  number_of_runs_integer
# so from the shell prompt:  $ A1_linux_donut_loop.sh 10
# will run the proddonuts program and the consdonuts
# programs (5 of them) 10 times and report how many
# of the 10 runs ended in deadlock

if [ -z $1 ]
then
echo "USAGE: A1_linux_donut_loop.sh  number_of_runs_integer"
echo "Try the command again"
echo " "
fi

echo " "
echo " "
echo " "
echo "The configuration is for $1 LOOPS"
echo " "

local1=$1
lpcnt=1
count=0
while test $local1 -ne 0
do
echo "___________________________________________________________"
echo " "
echo "Working on LOOP $lpcnt"
echo " "

# Off you go Producer
./proddonuts >  prod_out.txt &
sleep 1

# Different number of Consumers for the graph

# 1 Consumer
#./consdonuts 1 > c1 &

# Two Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 &

# Three Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 &

# Four Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 &

# Five Consumers
./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 &

# Six Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 & ./consdonuts 6 > c6 &

# Seven Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 & ./consdonuts 6 > c6 & ./consdonuts 7 > c7 &

# Eight Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 & ./consdonuts 6 > c6 & ./consdonuts 7 > c7 & ./consdonuts 8 > c8 &

# Nine Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 & ./consdonuts 6 > c6 & ./consdonuts 7 > c7 & ./consdonuts 8 > c8 & ./consdonuts 9 > c9 &

# Ten Consumers
#./consdonuts 1 > c1 & ./consdonuts 2 > c2 & ./consdonuts 3 > c3 & ./consdonuts 4 > c4 & ./consdonuts 5 > c5 & ./consdonuts 6 > c6 & ./consdonuts 7 > c7 & ./consdonuts 8 > c8 & ./consdonuts 9 > c9 & ./consdonuts 10 > c10 &

sleep 15
pid=`ps | grep -v 'grep' | grep 'proddonuts' | cut -c1-6`
if ps | grep -v 'grep' | grep -q 'consdonuts'
then
echo " "
echo "DEADLOCK DETECTED ON LOOP $lpcnt"
echo " "
count=`expr $count + 1`
else
echo "LOOP $lpcnt COMPLETED SUCCESSFULLY"
echo " "
fi
echo ">>>>>>>> NOW KILLING THE PRODUCER PROCESS PID: $pid"
kill $pid
local1=`expr $local1 - 1`
lpcnt=`expr $lpcnt + 1`
sleep 1
done
echo "___________________________________________________________"
echo " "
echo $1 loops and $count deadlocks
echo " "
echo " "
