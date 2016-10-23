#/bin/bash
#removes files from excited_states.txt from the reaction xml list file

while read line; do
    sed "/$line/d" rapp_rates_fixed_xml/rapp_rates_fixed_list.xml > rapp_rates_fixed_xml/rapp_rates_fixed_no_excited.xml;
    done<excited_states.txt
