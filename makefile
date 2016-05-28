export FIRSTDIR := $(abspath $(lastword $(MAKEFILE_LIST)))
export TESTLIBSPATH = $(join $(dir $(FIRSTDIR)) ,libpath/)
export TESTINCSPATH = $(join $(dir $(FIRSTDIR)) ,include/)
T = mult_matrices

export FOLDER_TEST_NAME = $(T)
export UPCFLAGS = -T 4 -g

SUBDIRS = bench tests

.PHONY: subdirs $(SUBDIRS) test

default: subdirs
all: default

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@


bench: tests


clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
	rm -fr $(TESTLIBSPATH)*
	rm -fr $(TESTINCSPATH)*

test:
	@echo $(dir $(FIRSTDIR))
	@echo $(dir $(TESTLIBSPATH))
	@echo $(dir $(TESTINCSPATH))

	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) test ); done