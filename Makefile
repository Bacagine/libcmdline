# 
# Makefile
# 
# Makefile for the project logger
# 
# This is the a Makefile to my personal logger C library
#
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Date: 2024-02-19
#

TARGET       = libcmdline.so

# Directories
SRCDIR       = src
INCDIR       = include/cmdline
OBJDIR       = obj
LIBDIR       = lib
BINDIR       = bin
TESTDIR      = tests
LIB          = $(LIBDIR)/$(TARGET)

# .c files
SRC        = $(wildcard $(SRCDIR)/*.c)

# .o files
OBJ        = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# .so or .a files
#LIB        = $(LIBDIR)

# Compilation flags
LDFLAGS      = -L $(LIBDIR)
LDLIBS       = -lcmdline
CFLAGS       = -I $(INCDIR) -Wall -Wextra 
DEBUGFLAGS   = -g -O0 -DDEBUG
CC           = gcc

ifdef DEBUG
	CFLAGS += $(DEBUGFLAGS) 
	LDFLAGS += $(DEBUGFLAGS)
else
	CFLAGS += -O3
endif

all: distclean $(OBJDIR) $(LIBDIR) $(LIB)

$(LIB): $(OBJ)
	$(CC) -shared -o $@ $(OBJ) $(CFLAGS)

$(BINDIR):
	mkdir $@
$(LIBDIR):
	mkdir $@
$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -fPIC -c $< -o $@ $(CFLAGS)

clean:
	rm -rvf $(OBJDIR)

install: all
	./install.sh

uninstall:
	./uninstall.sh

test: all $(BINDIR)
	$(CC) -o $(BINDIR)/cmdline $(TESTDIR)/test.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

distclean: clean
	rm -rvf $(BINDIR)
	rm -rvf $(LIBDIR)
	
.PHONY: all clean install uninstall distclean

