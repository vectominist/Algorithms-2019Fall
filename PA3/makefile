# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: cb
	@echo "Jizz"

# optimized version
cb			: cb_opt.o main_opt.o tmu_opt.o
			$(CC) $(OPTFLAGS) main_opt.o cb_opt.o tmu_opt.o -o cb
main_opt.o	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
tmu_opt.o	: src/tm_usage.cpp src/tm_usage.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
cb_opt.o	: src/CBSolver.cpp src/CBSolver.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : cb_dbg
	@echo -n ""

cb_dbg		: cb_dbg.o main_dbg.o tmu_dbg.o
			$(CC) $(DBGFLAGS) cb_dbg.o main_dbg.o tmu_dbg.o -o cb_dbg
main_dbg.o	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
tmu_dbg.o	: src/tm_usage.cpp src/tm_usage.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@
cb_dbg.o	: src/CBSolver.cpp src/CBSolver.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

lib: lib/libtm_usage.a

# lib/libtm_usage.a: tm_usage.o
# 	$(AR) $(ARFLAGS) $@ $<
# tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	# $(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o cb cb_dbg

