include Makefile

DEST = windbg

${DEST}/libmycutils.dll.a: $(addprefix ${DEST}/, ${OBJS})
	ar -rsv $@ $^

${DEST}/%.o: %.c ${HEADS}
	gcc $< -c -g -O2 -o $@

clean:
	echo>${DEST}/libmycutils.dll.a
	echo>${DEST}/a.o
	del ${DEST}\libmycutils.dll.a
	del ${DEST}\*.o

.PHONY: clean
