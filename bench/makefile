TARGET = Benchmark
INCSPATH = $(join -I,$(dir $(TESTINCSPATH)))

LIBS =
#TEST_TO_INCLUDE = $(wildcard $(addprefix $(dir $(TESTLIBSPATH)), *.o))
TEST_TO_INCLUDE = $(addprefix $(TESTLIBSPATH), libT.o)
UPCC = upcc
UPCFLAGS = 

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean test

.PRECIOUS: $(TARGET) $(OBJECTS)

default: $(TARGET)
all: default

test:
	echo $(LIBS)
	echo $(TEST_TO_INCLUDE)


%.o: %.c $(HEADERS)
	$(UPCC) $(UPCFLAGS) -c $< -o $@ $(INCSPATH)


$(TARGET): $(OBJECTS)
	$(UPCC) $(UPCFLAGS) $(OBJECTS) $(LIBS) $(TEST_TO_INCLUDE) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)