CFLAGS=-O3
LDFLAGS=-lcrypt

pls: pls.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o pls pls.c

.PHONY: install
install: pls
	cp -f pls      /usr/bin
	chown root:pls /usr/bin/pls
	chmod 4750     /usr/bin/pls

