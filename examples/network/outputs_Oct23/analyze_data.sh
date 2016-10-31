zonenum=158
tag='rapp_revised_Oct23'
while [ $zonenum -le 171 ]
do
mkdir results/zone$zonenum
echo "------------------------> Processing zone: $zonenum"
./extract_time_steps results/pp_zone$zonenum-$tag $zonenum
zonenum=$(($zonenum+1))
done
echo "find the last time step"
./find_last_time_step.sh
echo "sum all layers"
./sum_all_layers
echo "compare with solar"
./compare_with_solar
echo "get p-nuclei with beta-dacays"
./get_p_nuclei_with_beta_decays
echo "get p-nuclei from layers"
./get_pnuclei_from_layers
#mkdir /home/brandon/nucnet-tools-code/pprocess/results/$tag
#mv /home/asimon3/network_code/pprocess/results/zone* /home/asimon3/network_code/pprocess/results/$tag/
#mv /home/asimon3/network_code/pprocess/results/pp_X_Z_A.dat /home/asimon3/network_code/pprocess/results/$tag/
#mv /home/asimon3/network_code/pprocess/results/pp_X_A.dat /home/asimon3/network_code/pprocess/results/$tag/
#mv /home/asimon3/network_code/pprocess/results/pnuclei* /home/asimon3/network_code/pprocess/results/$tag/
#mv /home/asimon3/network_code/pprocess/results/ratio_to_solar.dat /home/asimon3/network_code/pprocess/results/$tag/
#mv /home/asimon3/network_code/pprocess/results/pnucl_in_layers.dat /home/asimon3/network_code/pprocess/results/$tag/
