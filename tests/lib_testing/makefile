LIBS = 
UPCC = upcc
UPCFLAGS = -g
TESTLIBSPATH = ../../libpath/
TESTINCSPATH = ../../include/


.PHONY: default all clean

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJ_DEST = $(foreach obj, $(OBJECTS), $(join $(dir $(TESTLIBSPATH)), $(addprefix lib,$(obj))))
HEADERS = $(wildcard *.h)
HEAD_DEST = $(foreach head, $(HEADERS), $(join $(dir $(TESTINCSPATH)),$(head)))

default: $(OBJECTS)
all: default

test:
	@echo $(OBJECTS)
	@echo $(OBJ_DEST)
	@echo $(HEADERS)
	@echo $(HEAD_DEST)

$(HEAD_DEST): $(HEADERS)
	cp $^ $(dir $(TESTINCSPATH))


%.o: %.c $(HEAD_DEST)
	$(UPCC) $(UPCFLAGS) -c $< -o $(join $(dir $(TESTLIBSPATH)), $(addprefix lib, $@))

.PRECIOUS: $(OBJECTS)

clean:
	-rm -f *.o
	-rm -f $(HEAD_DEST)
	-rm -f $(OBJ_DEST)