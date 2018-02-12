CFLAGS = -ggdb -Wall -Wextra $(shell pkg-config --cflags jansson libcurl)
LDLIBS = $(shell pkg-config --libs jansson libcurl)

SOURCES = ark.c aurpkg.c strfunc.c arkparse.c
HEADERS = ark.h arkparse.h aurpkg.h strfunc.h

all: ark

ark: $(SOURCES) $(HEADERS)

ark-dbg: $(SOURCES) $(HEADERS)
	cc $(SOURCES) $(CFLAGS) $(LDLIBS) -D ARK_DEBUG

clean:
	rm -f ark
	rm -f ark-dbg

.PHONY: all clean

