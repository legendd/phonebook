CC ?= gcc
#debugging information specifically intended for gdb
CFLAGS_common ?= -O3 -Wall -ggdb -std=gnu99
# show specific messages
perf = stat -r 5 -e L1-dcache-prefetch-misses,cache-misses,cache-references,cs,cpu-clock,L1-dcache-loads,L1-icache-loads

EXEC = phonebook_orig phonebook_opt phonebook_opt_hash
all: $(EXEC)

SRCS_common_orig = main.c
SRCS_common_hash = main_hash.c

phonebook_orig: $(SRCS_common_orig) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_orig) $@.c

phonebook_opt: $(SRCS_common_orig) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_orig) $@.c

phonebook_opt_hash: $(SRCS_common_hash) phonebook_opt_hash.c phonebook_opt_hash.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_hash) $@.c

perf_orig: 
	perf $(perf) ./phonebook_orig
perf_opt:
	perf $(perf) ./phonebook_opt
perf_opt_hash:
	perf $(perf) ./phonebook_opt_hash
clear: 
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh

run: $(EXEC)
	watch -d -t ./phonebook_orig

clean:
	$(RM) $(EXEC) *.o perf.*
