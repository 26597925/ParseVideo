CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -Os
LDFLAGS =

OUTPUT = bin

SRC = src

SOURCES = $(wildcard $(SRC)/*.c)
#OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
#http://bbs.chinaunix.net/thread-1692258-1-1.html
#OBJS_NAME = $(notdir $(patsubst %.c,%.o,$(SOURCES)))
OBJS = $(addprefix $(OUTPUT)/,$(notdir $(patsubst %.c,%.o,$(SOURCES))))

TARGET = bin/parsevideo

CFLAGS += `pkg-config --cflags glib-2.0`
LDFLAGS += `pkg-config --libs glib-2.0` -lpcre

#libcurl
LIBCURL_STATICLIB :=  lib/libcurl.a
LIBCURL_INC :=  lib/libcurl/include

all : libcurl

.PHONY : libcurl

CURL_STATICLIB := $(LIBCURL_STATICLIB)

$(LIBCURL_STATICLIB):lib/libcurl/Makefile
	cd lib/libcurl && $(MAKE) CC=$(CC)
	cp lib/libcurl/lib/.libs/libcurl.a lib

lib/libcurl/buildconf:
	cd lib/libcurl && ./configure
	
lib/libcurl/Makefile: | lib/libcurl/buildconf
	cd lib/libcurl && ./buildconf

libcurl : $(CURL_STATICLIB)

#libcurl

LDFLAGS += $(CURL_STATICLIB) -lssl -lcrypto -lz -lrt

#libjson

LIBJSON_STATICLIB := lib/libjson.a
LIBJSON_INC := lib/libjson

all : libjson
	
.PHONY : libjson

JSON_STATICLIB := $(LIBJSON_STATICLIB)

$(LIBJSON_STATICLIB) : lib/libjson/Makefile
	cd lib/libjson && $(MAKE) CC=$(CC)
	cp lib/libjson/.libs/libjson.a lib

lib/libjson/autogen.sh :
	cd lib/libjson && ./configure

lib/libjson/Makefile : | lib/libjson/autogen.sh
	cd lib/libjson && ./autogen.sh
	

libjson : $(JSON_STATICLIB)

#libjson

LDFLAGS += $(JSON_STATICLIB)

all: $(TARGET)

$(TARGET):$(OUTPUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
$(OBJS):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(*F).c,$(SOURCES)) -I$(LIBCURL_INC)  -I$(LIBJSON_INC) 
#$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
install:
	cp $(TARGET) /usr/bin 
uninstall:  
	rm -rf /usr/bin/$(TARGET)