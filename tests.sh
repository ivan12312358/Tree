#!/bin/bash

for ((i=1;i<=10;i++))
do
res=$(./tree < ./Tests/test$i/test)
answ=$(cat ./Tests/test$i/answ)
if [ "$answ" = "$res" ]
then
echo "Test $i: Done"
else
echo "Test $i: Failed"
echo "$res" > res$i
#echo "------------------------"
#echo  "Answer:$(\n) $answ"
fi
done