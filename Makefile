make: system_call.o	context_switch.o

system_call.o: system_call.c
	gcc -Wall -c system_call.c -lrt
	gcc -Wall -o system_call system_call.o -lrt

context_switch.o: context_switch.c
	gcc -Wall -std=c99 -c context_switch.c -lrt
	gcc -Wall -std=c99 -o context_switch context_switch.o -lrt

runsc: system_call.o
	./system_call

runcs: context_switch.o
	./context_switch

clean:
	rm system_call
	rm context_switch
	rm *.o
