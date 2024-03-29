make: system_call.o	context_switch.o

system_call: system_call.o
	gcc -Wall -o system_call system_call.o -lrt

system_call.o: system_call.c
	gcc -Wall -c system_call.c -lrt

context_switch: context_switch.o
	gcc -Wall -std=c99 -o context_switch context_switch.o -lrt

context_switch.o: context_switch.c
	gcc -Wall -std=c99 -c context_switch.c -lrt

runsc: system_call
	./system_call

runcs: context_switch
	./context_switch

clean:
	rm -f system_call
	rm -f context_switch
	rm -f *.o
