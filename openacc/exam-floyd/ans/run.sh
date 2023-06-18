export PATH=/opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin:$PATH

make clean

#source device.sh 1
#timeout 1m time make serial
#timeout 1m time make multicore
#timeout 1m time make managed
#timeout 1m time make optimize

source device.sh 8
timeout 1m time make multidevice

