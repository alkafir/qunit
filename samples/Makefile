CC=gcc
CCFLAGS=-Wall
LDFLAGS=-g0
SOURCES=passfail.c vectors.c textfile.c
HEADERS=../qunit.h

ifdef windir
	BIN_EXT=.exe
else
	BIN_EXT=.out
endif

BINARIES=$(foreach src,$(SOURCES),$(addsuffix $(BIN_EXT),$(basename $(src))))

.PHONY: clean test

all: $(BINARIES)

$(BINARIES): %$(BIN_EXT): %.c $(HEADERS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $<

clean:
	$(RM) $(BINARIES) *.log

$(HEADERS):
	$(MAKE) -C ../

run: $(BINARIES) $(HEADERS)
	@for bin in $(BINARIES); do ./$$bin; echo -e "\n *******************************************************************************\n";done
