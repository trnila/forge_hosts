TARGETS=change_hosts.so test

all: $(TARGETS)

%.so: %.c
	$(CC) -shared -fPIC $^ -o $@ -ldl

clean:
	rm -f $(TARGETS)
