#!/bin/bash

limit=$1 ;
counter=0 ;
while [ "$counter" -lt "$limit" ]
do
    ./src/main ;
    let counter+=1
    echo "" ;
    echo "" ;
done
