CC=gcc
CCFLAGS=
LDFLAGS=-g0
SOURCES=passfail.c
HEADERS=../qunit.h

ifdef windir
	BIN_EXT=.exe
else
	BIN_EXT=.out
endif

BINARIES=$(foreach src,$(SOURCES),$(addsuffix $(BIN_EXT),$(basename $(SOURCES))))

.PHONY: clean

all: $(BINARIES)

$(BINARIES): %$(BIN_EXT): %.c
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $<

clean:
	$(RM) $(BINARIES)
