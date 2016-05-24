SUBDIRS = $(wildcard */.)
#SUBDIRS=vector_testing/.
.PHONY: default subdirs $(SUBDIRS)

default: subdirs
all: default

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	echo $(SUBDIRS)
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
	#$(foreach dir, $(SUBDIRS), $(MAKE) clean -C $(dir))