TARGET = Test
LIBS = 
UPCC = upcc
UPCFLAGS = -g

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

test: $(OBJECTS)
	echo $(OBJECTS)


%.o: %.c $(HEADERS)
	$(UPCC) $(UPCFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(UPCC) $(UPCFLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)