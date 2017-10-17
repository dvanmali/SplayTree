#!/bin/bash

clear
make

#TESTDIR="./testcases/"
TESTDIR="./prog1-testcases/"   # change it to your directory

start=`date +%s`
./prog1 < $TESTDIR/delete.in
end=`date +%s`
echo "Runtime delete.in: $(($end - $start))"
echo "------------------------"

start=`date +%s`
./prog1 < $TESTDIR/deleteMax.in
end=`date +%s`
echo "Runtime deleteMax.in: $(($end - $start))"
echo "------------------------"

start=`date +%s`
./prog1 < $TESTDIR/insert.in
end=`date +%s`
echo "Runtime insert.in: $(($end - $start))"
echo "------------------------"

start=`date +%s`
./prog1 < $TESTDIR/lookup.in
end=`date +%s`
echo "Runtime lookup.in: $(($end - $start))"
echo "------------------------"

start=`date +%s`
./prog1 < $TESTDIR/random.in
end=`date +%s`
echo "Runtime random.in: $(($end - $start))"
echo "------------------------"
