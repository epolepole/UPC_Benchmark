

SUBDIRS = bench tests

.PHONY: subdirs $(SUBDIRS)

default: subdirs
all: default

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@


bench: tests


clean:
	$(MAKE) clean -C $(SUBDIRS)