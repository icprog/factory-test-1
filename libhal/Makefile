SHELL = /bin/sh
top_srcdir = ..
top_builddir = ..
top_vsos = ../../..
PLATTYPE = powerpc
#########################################################
include ../../../build/pub.mk
include ../../../build/$(PLATTYPE)/board.mk

DIR = $(shell pwd)
BIN_DIR = 
LIB_DIR =
SRC_DIR = .
INCLUDE_DIR =
OBJ_DIR = .$(PLATTYPE)-obj
DEPS_DIR = .$(PLATTYPE)-deps
PROGRAM=$(OBJ_DIR)/libhal

ifneq ($(OBJ_DIR), $(wildcard $(OBJ_DIR)))
$(shell mkdir -p $(OBJ_DIR))
endif
ifneq ($(DEPS_DIR), $(wildcard $(DEPS_DIR)))
$(shell mkdir -p $(DEPS_DIR))
endif

############################################################################
EXTENSION=c
obj-all += $(patsubst $(SRC_DIR)/%.$(EXTENSION), $(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.$(EXTENSION)))
obj-n += $(OBJ_DIR)/cpld-upgrade.o

obj-y += $(filter-out $(obj-n), $(obj-all))

DEPS = $(patsubst $(OBJ_DIR)/%.o, $(DEPS_DIR)/%.d, $(obj-y))

############################################################################
KERNEL_INCLUDE_DIR = $(top_srcdir)/../../kernel/$(KERNELVERSION)/include
ifeq ($(board) , cavium_octeon)
INCLUDES +=-I$(top_builddir) -I$(top_builddir)/lib -I$(top_builddir)/../../kernel/include -I./include -I../openssl/include
endif
ifeq ($(board) , marvell_arm)
INCLUDES +=-I$(top_builddir) -I$(top_builddir)/lib -I$(top_builddir)/../../kernel/$(KERNELVERSION)/include \
		-I$(top_builddir)/../../kernel/$(KERNELVERSION)/rcios/include -I./include -I../openssl/include
endif
ifeq ($(board) , power_pc)
INCLUDES +=-I$(top_builddir) -I$(top_builddir)/lib \
		-I$(top_builddir)/../../kernel/$(KERNELVERSION)/rcios/include -I./include -I../openssl/include \
		-I$(KERNEL_INCLUDE_DIR)/../usr/include
endif

           
CONFIG_HEADER = $(top_builddir)/config.h

LIBS_INCLUDE = -L../../rootfs/$(PLATTYPE)/lib  -Wl,-rpath,../../rootfs/$(PLATTYPE)/lib
ifeq ($(board) , cavium_octeon)
LIBS = -lm -lcrypt  -lreadline -lncurses -lzebra -lssl -lldap
endif
ifeq ($(board) , marvell_arm)
LIBS = -lm -lcrypt  -lreadline -lncurses -lzebra -lssl -lldap -llber -lcrypto 
endif

ifeq ($(board) , power_pc)
LIBS = -lm -lcrypt  -lreadline -lncurses -lzebra -lssl -lcrypto -ldb-4.5 -liconv -lldap -llber $(LIBS_COMMON)
#LIBS = -lm -lzebra -lvtss_api -liconv $(LIBS_COMMON)
endif

############################################################
.PHONY: all clean rebuild

all:$(PROGRAM)

$(PROGRAM):$(obj-y) 
	-rm -f $(PROGRAM)
	$(CC) -o $(PROGRAM).so -fpic -shared $(obj-y) $(LIBS_INCLUDE) $(LIBS) 
	$(AR) cqs $(PROGRAM).a $(obj-y)
	@cp -f $(OBJ_DIR)/libhal.* ../../rootfs/$(PLATTYPE)/lib
	$(CC) -o cpld-upgrade cpld-upgrade.c $(LIBS_INCLUDE) $(LIBS) -lhal
	@cp -f cpld-upgrade ../../rootfs/$(PLATTYPE)/bin

sinclude $(DEPS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.$(EXTENSION) 
	$(CC) -MM $(INCLUDES) $(CFLAGS) $< | sed -e 1's,^,$(OBJ_DIR)/,' > $(patsubst $(OBJ_DIR)/%.o,$(DEPS_DIR)/%.d,$@)
	$(CC) $< -o $@ -c -fpic -shared $(CFLAGS) $(DEFS) $(INCLUDES) 
#	$(CC) $< -o $@ -c $(CFLAGS) $(DEFS) $(INCLUDES)
rebuild: clean all

clean:
	rm -rf $(OBJ_DIR)  $(DEPS_DIR) 


