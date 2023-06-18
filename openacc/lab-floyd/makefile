device:
	nvaccelinfo

serial:
	nvc++ -o floyd.exe0 -DSIZE=1200 -Minfo=all -Mneginfo=all floyd_serial.cpp >floyd.log0 2>&1
	#nsys profile -o floyd.prof0.nsys-rep -t openmp,openacc,cuda ./floyd.exe0 >>floyd.log0 2>&1
	timeout 1m time ./floyd.exe0 >>floyd.log0 2>&1

multicore:
	nvc++ -o floyd.exe1 -DSIZE=2400 -mp=multicore -acc=multicore -Minfo=all -Mneginfo=all floyd_multicore.cpp >floyd.log1 2>&1
	#nsys profile -o floyd.prof1.nsys-rep -t openmp,openacc,cuda ./floyd.exe1 >>floyd.log1 2>&1
	timeout 1m time ./floyd.exe1 >>floyd.log1 2>&1

managed:
	nvc++ -o floyd.exe2 -DSIZE=3600 -mp=multicore -acc=gpu -gpu=managed -Minfo=all -Mneginfo=all floyd_managed.cpp >floyd.log2 2>&1
	#nsys profile -o floyd.prof2.nsys-rep -t openmp,openacc,cuda ./floyd.exe2 >>floyd.log2 2>&1
	timeout 1m time ./floyd.exe2 >>floyd.log2 2>&1

optimize:
	nvc++ -o floyd.exe3 -DSIZE=4800 -mp=multicore -acc=gpu -Minfo=all -Mneginfo=all floyd_optimize.cpp >floyd.log3 2>&1
	#nsys profile -o floyd.prof3.nsys-rep -t openmp,openacc,cuda ./floyd.exe3 >>floyd.log3 2>&1
	timeout 1m time ./floyd.exe3 >>floyd.log3 2>&1

multidevice:
	nvc++ -o floyd.exe4 -DSIZE=6000 -mp=multicore -acc=gpu -Minfo=all -Mneginfo=all floyd_multidevice.cpp >floyd.log4 2>&1
	#nsys profile -o floyd.prof4.nsys-rep -t openmp,openacc,cuda ./floyd.exe4 >>floyd.log4 2>&1
	timeout 1m time ./floyd.exe4 >>floyd.log4 2>&1

all: clean serial multicore managed optimize multidevice

clean:
	rm -f floyd.exe* floyd.prof* floyd.log*

