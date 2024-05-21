TARGET = gdb_demo
OBJS += gdb_demo.o
LIBS += -lm

CC = gcc
CFLAGS += -MMD -MP # dependency tracking flags
CFLAGS += -I./
CFLAGS += -std=gnu99 -Wall -Werror -Wconversion
LDFLAGS += $(LIBS)

all: CFLAGS += -g -O2 # release flags
all: $(TARGET)

release: clean all

debug: CFLAGS += -g -O0 # debug flags
debug: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

DEPS = $(OBJS:%.o=%.d)
-include $(DEPS)

clean:
	-@rm $(TARGET) $(OBJS) $(DEPS) 2> /dev/null || true
