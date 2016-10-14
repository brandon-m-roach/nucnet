#!/bin/bash

for flag in bec bet+ bet- bkmo btyk bqa+ ec bhi+ bex+ mo92 mo03; do
    touch $flag.txt;
    egrep -l "$flag" rapp_rates_weak_flags/reac*.dat > $flag.txt;
    while read file; do 
	sed -i -e "s/${flag} /${flag}w/g" $file; 
    done<${flag}.txt
done
	
