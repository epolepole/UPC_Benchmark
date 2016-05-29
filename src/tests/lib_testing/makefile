LIBS = 
UPCC = upcc
UPCFLAGS = 

.PHONY: default all clean

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
#OBJ_DEST = $(foreach obj, $(OBJECTS), $(join $(dir $(TESTLIBSPATH)), $(addprefix lib,$(obj))))
OBJ_DEST = $(join $(dir $(TESTLIBSPATH)), libT.o)
HEADERS = $(wildcard *.h)
#HEAD_DEST = $(foreach head, $(HEADERS), $(join $(dir $(TESTINCSPATH)),$(head)))
HEAD_DEST = $(join $(dir $(TESTINCSPATH)),T.h)

default: $(OBJECTS)
all: default

test:
	@echo $(OBJECTS)
	@echo $(OBJ_DEST)
	@echo $(HEADERS)
	@echo $(HEAD_DEST)

$(HEAD_DEST): $(HEADERS)
	cp $^ $(HEAD_DEST)


%.o: %.c $(HEAD_DEST)
	#$(UPCC) $(UPCFLAGS) -c $< -o $(join $(dir $(TESTLIBSPATH)), $(addprefix lib, $@))
	$(UPCC) $(UPCFLAGS) -c $< -o $@
	ld -r $(OBJECTS) -o $(OBJ_DEST)

.PRECIOUS: $(OBJECTS)

clean:
	-rm -f *.o
	-rm -f $(HEAD_DEST)
	-rm -f $(OBJ_DEST)