include Makefile

linuxdbg/libmycutils.a: $(addprefix linuxdbg/, ${OBJS})
	ar -rsv $@ $^

linuxdbg/%.o: %.c ${HEADS}
	gcc $< -c -g -O2 -o $@

clean:
	touch linuxdbg/libmycutils.a linuxdbg/a.o
	rm linuxdbg/libmycutils.a linuxdbg/*.o

.PHONY: clean
