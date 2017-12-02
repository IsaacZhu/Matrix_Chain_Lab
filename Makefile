MC.o: Matrix_Chain.c
	gcc -g -Wall Matrix_Chain.c -o $@
.Phony:clean
clean:
	rm *.o
