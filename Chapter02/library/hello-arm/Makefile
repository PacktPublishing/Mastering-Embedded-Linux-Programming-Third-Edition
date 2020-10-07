CFLAGS := -c -Wall -I../inc
PROGS := hello-arm-static hello-arm-shared

all: $(PROGS)

hello-arm.o: hello-arm.c
	$(CC) $(CFLAGS) -o $@ $^

hello-arm-static: hello-arm.o
#	$(CC) $(LDFLAGS) -o $@ $^ ../static/libtest.a
	$(CC) -o $@ $^ -L../static -ltest

hello-arm-shared: hello-arm.o
	$(CC) -o $@ $^ -L../shared -ltest

clean:
	rm -f *.o
	rm -f $(PROGS)

install:
	cp $(PROGS) $(TARGET_DIR)/usr/local/bin

