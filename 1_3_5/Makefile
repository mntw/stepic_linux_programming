all: solution 
libf: function.c
	gcc function.c -o libFunction.so -shared -fPIC 
solution: solution.c
	gcc solution.c -o solution -fPIC  -ldl  -Wl,-rpath,.
clean:
	-rm libFunction.so
	-rm solution
