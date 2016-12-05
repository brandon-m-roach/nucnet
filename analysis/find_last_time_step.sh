#
# this script searches for the last time step file in zone folder
# (last file created by extract_time_steps) and copies it to 
# ../results directory
#
zone_num=158
while [ $zone_num -le 171 ]
do 
echo $zone_num
cd ../pprocess/outputs_Nov9/zone$zone_num
pwd
filename=$(ls -rt | tail -1)
echo ${filename}
cp $filename ../../outputs_Nov9/pp_$zone_num-last.dat
echo "../../pprocess/outputs_Nov9/zone$zone_num/$filename copied to ../pprocess/outputs_Nov9/pp_$zone_num-last.dat"
let zone_num=zone_num+1
cd /home/brandon/nucnet/nucnet/analysis
#cd /afs/crc.nd.edu/user/b/broach1/nucnet-tools-code/analysis
done
