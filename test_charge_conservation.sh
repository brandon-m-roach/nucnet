#!/bin/bash

i=1

while [ $i -le 62505 ]; do
    jina_to_webnucleo/reaction_converter rapp_rates_fixed/reac$i.dat test.xml | grep 'conserved' &> /dev/null;
    if [ $? == 0 ]; then
	echo "reac$i.dat";
    fi;
    let i=i+1;
done
