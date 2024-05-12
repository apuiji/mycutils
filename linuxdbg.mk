include Makefile

DEST = linuxdbg

${DEST}/libmycutils.a: $(addprefix ${DEST}/, ${OBJS})
	ar -rsv $@ $^

${DEST}/%.o: %.c ${HEADS}
	gcc $< -c -g -O2 -o $@

clean:
	touch ${DEST}/libmycutils.a ${DEST}/a.o
	rm ${DEST}/libmycutils.a ${DEST}/*.o

.PHONY: clean
