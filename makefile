export FIRSTDIR := $(abspath $(lastword $(MAKEFILE_LIST)))
export TESTLIBSPATH = $(join $(dir $(FIRSTDIR)) ,libpath/)
export TESTINCSPATH = $(join $(dir $(FIRSTDIR)) ,include/)


SUBDIRS = bench tests

.PHONY: subdirs $(SUBDIRS)

default: subdirs
all: default

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@


bench: tests


clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

test:
	@echo $(dir $(FIRSTDIR))
	@echo $(dir $(TESTLIBSPATH))
	@echo $(dir $(TESTINCSPATH))