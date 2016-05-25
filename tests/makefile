#SUBDIRS = $(wildcard */.)
SUBDIRS = $(addsuffix /, $(FOLDER_TEST_NAME))
#T = test folder name

.PHONY: default subdirs $(SUBDIRS) test

default: subdirs
all: default

subdirs: $(SUBDIRS)

$(SUBDIRS): clean
	$(MAKE) -C $@

test:	
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) test ); done

clean:
	echo $(SUBDIRS)
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
	#$(foreach dir, $(SUBDIRS), $(MAKE) clean -C $(dir))