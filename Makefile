CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared
LDLIBS = -lcmdline 
LIBRARY = libcmdline.so
SRCDIR = src
INCDIR = include
OBJDIR = obj

LIBDIR = lib

SRCFILES = $(SRCDIR)/cmdline.c
OBJFILES = $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(LIBDIR) $(LIBRARY)

$(OBJDIR):
	mkdir obj

$(LIBDIR):
	mkdir lib

$(LIBRARY): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $(LIBDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(LIBDIR)/$(LIBRARY)

distclean:
	rm -rf $(OBJDIR) $(LIBDIR)
	rm -rf a.out
	rm -rf test.log

test:
	$(CC)  $(CFLAGS) -I$(INCDIR) test/main.c -L lib $(LDLIBS)
run:
	@./run

install: $(LIBRARY)
	cp $(LIB_DIR)/$(LIBRARY) /usr/local/lib/
	cp $(INC_DIR)/cmdline.h /usr/local/include/

uninstall:
	rm -f /usr/local/lib/$(LIBRARY)
	rm -f /usr/local/include/cmdline.h

.PHONY: all clean distclean test run install uninstall
