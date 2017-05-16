OBJDIR = .
SRCDIR = .
INCLDIR = .
OUTDIR = .

## General Flags
PROGRAM = rt
CC = gcc
LD = gcc
CFLAGS = -Wall -O0 -I $(INCLDIR)
LDFLAGS = -lncurses -lpthread

## Objects that must be built in order to link
OBJECTS = $(OBJDIR)/rt_main.o                   \
          $(OBJDIR)/rt_hist.o                   \
          $(OBJDIR)/rt_disp_thrd.o              \
          $(OBJDIR)/rt_rx_thrd.o                \
          $(OBJDIR)/rt_queue.o


## Build both compiler and program
all: $(PROGRAM)

## Compile source files
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$*.o $< 

## Link object files to build the compiler
$(PROGRAM): $(SUBDIRS) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUTDIR)/$(PROGRAM)


clean:
	-rm -rf $(OBJECTS) $(PROGRAM)

