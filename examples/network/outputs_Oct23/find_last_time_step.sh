#
# this script searches for the last time step file in zone folder
# (last file created by extract_time_steps) and copies it to 
# ../results directory
#
zone_num=158
while [ $zone_num -le 171 ]
do 
echo $zone_num
cd results/zone$zone_num
filename=$(ls -rt | tail -1)
echo ${filename}
cp $filename ../pp_$zone_num-last.dat
echo "results/zone$zone_num/$filename copied to results/pp_$zone_num-last.dat"
let zone_num=zone_num+1
cd /home/brandon/nucnet/nucnet/examples/network/outputs_Oct23
done
