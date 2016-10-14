#!/bin/bash

for flag in bec bet+ bet- bkmo btyk bqa+ ec bec bhi+ bex+ mo92 mo03; do
    touch $flag.txt;
    egrep -l "$flag" rapp_rates_unedited/reac*.dat > $flag.txt;
    #while read file; do 
#	sed -i -e "${flag} /${flag}w/g"; 
 #   done<${flag}.txt
done
	
