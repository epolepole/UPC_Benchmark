TARGET = Benchmark
INCSPATH = $(join -I,$(dir $(TESTINCSPATH)))

LIBS = $(wildcard $(addprefix $(dir $(TESTLIBSPATH)), *.o))
UPCC = upcc
UPCFLAGS = -g

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

.PRECIOUS: $(TARGET) $(OBJECTS)

default: $(TARGET)
all: default

test:
	@echo $(LIBS)


%.o: %.c $(HEADERS)
	$(UPCC) $(UPCFLAGS) -c $< -o $@ $(INCSPATH)


$(TARGET): $(OBJECTS)
	$(UPCC) $(UPCFLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)