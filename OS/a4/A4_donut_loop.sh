#! /bin/bash

# usage: A4_linux_donut_loop.sh  number_of_runs_integer
# so from the shell prompt:  $ A4_linux_donut_loop.sh 10 
# will run the single threaded process named   pc_threads
# 10 times and report how many of the runs ended in deadlock

if [ -z $1 ]
then
echo "USAGE: A4_linux_donut_loop.sh  number_of_runs_integer"
echo "Try the command again"
echo " "
fi

echo " "
echo "The configuration is for $1 LOOPS"
echo " "

local1=$1
lpcnt=1
count=0
while test $local1 -ne 0
do
echo " "
echo "Working on LOOP $lpcnt"
echo " "
./pc_threads &
pid=`ps | grep pc\_threads | cut -c1-6`
echo JOB AND PID IS $pid
sleep 10
pid=`ps | grep 'pc\_threads' | cut -c1-6`
# if  ps | grep 'pc\_threads' > /dev/null
if [ -n "$pid" ]
then
echo PID REMAINING IS $pid
echo " "
echo "DEADLOCK DETECTED ON LOOP $lpcnt"
sleep 5
echo " "
count=`expr $count + 1`
echo "#### KILLING ALL THREADS"
# /bin/kill pc_threads 2> /dev/null
kill $pid
fi
local1=`expr $local1 - 1`
lpcnt=`expr $lpcnt + 1`
sleep 1
done
echo $1 loops and $count deadlocks
