include Makefile

linuxdbg/libmycutils.dll.a: $(addprefix linuxdbg/, ${OBJS})
	ar -rsv $@ $^

linuxdbg/%.o: %.c ${HEADS}
	gcc $< -c -g -O2 -o $@

clean:
	echo>linuxdbg/libmycutils.dll.a
	echo>linuxdbg/a.o
	rm linuxdbg/libmycutils.dll.a
	rm linuxdbg/*.o

.PHONY: clean
