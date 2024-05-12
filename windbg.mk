include Makefile

windbg/libmycutils.dll.a: $(addprefix windbg/, ${OBJS})
	ar -rsv $@ $^

windbg/%.o: %.c ${HEADS}
	gcc $< -c -g -O2 -o $@

clean:
	echo>windbg/libmycutils.dll.a
	echo>windbg/a.o
	del windbg\libmycutils.dll.a
	del windbg\*.o

.PHONY: clean
