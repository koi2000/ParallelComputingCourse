devreq=$1
if [ "$devreq" == "" ] ; then
  devreq=2
fi

unset CUDA_VISIBLE_DEVICES
numdev=`nvaccelinfo | grep -e "^Device Number:" | wc -l`
if [ $devreq -ge $numdev ] ; then
  echo -e "unset CUDA_VISIBLE_DEVICES"
else
  let devnum=$$%$numdev
  devlst=$devnum
  let devreq=$devreq-1
  while [ $devreq -gt 0 ] ; do
    let devnum=($devnum+1)%$numdev
    devlst=$devlst,$devnum
    let devreq=$devreq-1
  done
  export CUDA_VISIBLE_DEVICES=5,6,7
  echo -e "set CUDA_VISIBLE_DEVICES=$CUDA_VISIBLE_DEVICES"
fi

