M4=m4
HEADERS=qunit.h
DISTFILES=$(HEADERS)

.PHONY: clean dist samples install run-samples

all: $(HEADERS)

$(HEADERS): %.h: %.h.in
	$$(sed 's/\([0-9]*\)\.\([0-9]*\).\([0-9]*\)/declare VERSION_MAJOR=\1 VERSION_MINOR=\2 VERSION_PATCH=\3/' < VERSION) && \
		sed -e "s/@@VERSION_MAJOR@@/$$VERSION_MAJOR/g" \
				-e "s/@@VERSION_MINOR@@/$$VERSION_MINOR/g" \
				-e "s/@@VERSION_PATCH@@/$$VERSION_PATCH/g" <$< >$@

clean:
	$(RM) $(HEADERS) qunit-*.tar.xz
	$(MAKE) -C samples/ clean

dist: $(DISTFILES)
	declare QUNIT_VERSION=$$(<VERSION); \
		install -m 755 -d qunit-$$QUNIT_VERSION && \
		install -m 644 -t qunit-$$QUNIT_VERSION $(DISTFILES) && \
		tar -cJvf qunit-$$QUNIT_VERSION.tar.xz qunit-$$QUNIT_VERSION && \
		$(RM) -r qunit-$$QUNIT_VERSION
	
samples:
	$(MAKE) -C samples/

run-samples: $(HEADERS)
	$(MAKE) -C samples/ run

install:
	$(error Nothing to install. Just copy $(HEADERS) to your project and good luck.)
