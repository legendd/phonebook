CC ?= gcc
#debugging information specifically intended for gdb
CFLAGS_common ?= -O3 -Wall -ggdb -std=gnu99
# show specific messages
perf = stat -r 5 -e cache-misses,cache-references,cs,cpu-clock,L1-dcache-loads,L1-icache-loads

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c
perf_orig: 
	perf $(perf) ./phonebook_orig
perf_opt:
	perf $(perf) ./phonebook_opt
clear: 
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh

run: $(EXEC)
	watch -d -t ./phonebook_orig

clean:
	$(RM) $(EXEC) *.o perf.*
