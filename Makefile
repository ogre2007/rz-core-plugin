NAME=core-plugin
RZ_PLUGIN_PATH=$(shell rizin -H RZ_USER_PLUGINS)
LIBEXT=$(shell rizin -H LIBEXT)
ASAN_FLAG=-fsanitize=address
CFLAGS=-g -fPIC $(shell pkg-config --cflags rz_core) 
LDFLAGS=-shared $(shell pkg-config --libs rz_core)
SRC = core_plugin.c
OBJS=$(NAME).o
LIB=$(NAME).$(LIBEXT)

all: $(LIB)

clean:
	rm -f $(LIB) $(OBJS)

$(LIB): $(SRC) #$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(LIB)

check:
	$(CC) $(CFLAGS) $(ASAN_FLAG) $(LDFLAGS) $(ASAN_FLAG) $(SRC) -o $(LIB) 

install:
	cp -f $(NAME).$(LIBEXT) $(RZ_PLUGIN_PATH)

uninstall:
	rm -f $(RZ_PLUGIN_PATH)/$(NAME).$(LIBEXT)