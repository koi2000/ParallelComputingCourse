export PATH=/opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin:$PATH

source device.sh 1
#source device.sh 8
make clean

timeout 1m time make serial
timeout 1m time make multicore
timeout 1m time make managed
#timeout 1m time make optimize
#timeout 1m time make multidevice

