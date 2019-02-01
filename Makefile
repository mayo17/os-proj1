make: system_call.c	context_switch.c
	gcc -Wall -o system_call system_call.c
	gcc -Wall -o context_switch context_switch.c

runsc: system_call
	./system_call

runcs: context_switch
	./context_switch

clean:
	rm system_call
	rm context_switch
