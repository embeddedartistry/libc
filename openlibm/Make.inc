# -*- mode: makefile-gmake -*-

# Default build rule for any Makefile in this project: all
default: all

OS := $(shell uname)
# Do not forget to bump SOMINOR when changing VERSION,
# and SOMAJOR when breaking ABI in a backward-incompatible way
VERSION = 0.7.0
SOMAJOR = 3
SOMINOR = 0
DESTDIR =
prefix = /usr/local
bindir = $(prefix)/bin
libdir = $(prefix)/lib
includedir = $(prefix)/include

ifeq ($(OS), FreeBSD)
pkgconfigdir = $(prefix)/libdata/pkgconfig
else
pkgconfigdir = $(libdir)/pkgconfig
endif

USEGCC = 1
USECLANG = 0

ifneq (,$(findstring $(OS),Darwin FreeBSD OpenBSD))
USEGCC = 0
USECLANG = 1
endif

AR = $(TOOLPREFIX)ar

ifeq ($(ARCH),wasm32)
CC = clang-8
USEGCC = 0
CFLAGS_add += -fno-builtin -fno-strict-aliasing
endif

ifeq ($(USECLANG),1)
USEGCC = 0
CC = clang
CFLAGS_add += -fno-builtin -fno-strict-aliasing
endif

ifeq ($(USEGCC),1)
CC = $(TOOLPREFIX)gcc
CFLAGS_add += -fno-gnu89-inline -fno-builtin
endif

ARCH ?= $(shell $(CC) -dumpmachine | sed "s/\([^-]*\).*$$/\1/")

ifeq ($(ARCH),mingw32)
$(error "the mingw32 compiler you are using fails the openblas testsuite. please see the Julia README.windows.md document for a replacement")
endif

# OS-specific stuff
ifeq ($(findstring arm,$(ARCH)),arm)
override ARCH := arm
MARCH ?= armv7-a
CFLAGS_add += -mhard-float
endif
ifeq ($(findstring powerpc,$(ARCH)),powerpc)
override ARCH := powerpc
endif
ifeq ($(findstring ppc,$(ARCH)),ppc)
override ARCH := powerpc
endif
ifeq ($(findstring s390,$(ARCH)),s390)
override ARCH := s390
endif
ifneq ($(filter $(ARCH),i386 i486 i586 i686 i387 i487 i587 i687),)
override ARCH := i387
MARCH ?= i686
endif
ifeq ($(ARCH),x86_64)
override ARCH := amd64
endif
ifeq ($(findstring mips,$(ARCH)),mips)
override ARCH := mips
endif

# If CFLAGS does not contain a -O optimization flag, default to -O3
ifeq ($(findstring -O,$(CFLAGS)),)
CFLAGS_add += -O3
endif

ifneq (,$(findstring MINGW,$(OS)))
override OS=WINNT
endif

#keep these if statements separate
ifeq ($(OS), WINNT)
SHLIB_EXT = dll
SONAME_FLAG = -soname
CFLAGS_add += -nodefaultlibs
shlibdir = $(bindir)
else
ifeq ($(OS), Darwin)
SHLIB_EXT = dylib
SONAME_FLAG = -install_name
else
SHLIB_EXT = so
SONAME_FLAG = -soname
endif
CFLAGS_add += -fPIC
shlibdir = $(libdir)
endif

# Add `-march` to our CFLAGS if it's defined
ifneq ($(MARCH),)
CFLAGS_arch += -march=$(MARCH)
endif

ifeq ($(ARCH),i387)
CFLAGS_arch  += -m32
SFLAGS_arch  += -m32
LDFLAGS_arch += -m32
endif

ifeq ($(ARCH),amd64)
CFLAGS_arch  += -m64
SFLAGS_arch  += -m64
LDFLAGS_arch += -m64
endif

ifeq ($(ARCH),wasm32)
CFLAGS_arch += -ffreestanding -nostdlib -nostdinc --target=wasm32-unknown-unknown
endif

# Add our "arch"-related FLAGS in.  We separate arch-related flags out so that
# we can conveniently get at them for targets that don't want the rest of
# *FLAGS_add, such as the testing Makefile targets
CFLAGS_add  += $(CFLAGS_arch)
SFLAGS_add  += $(SFLAGS_arch)
LDFLAGS_add += $(LDFLAGS_arch)

CFLAGS_add += -std=c99 -Wall -I$(OPENLIBM_HOME) -I$(OPENLIBM_HOME)/include -I$(OPENLIBM_HOME)/$(ARCH) -I$(OPENLIBM_HOME)/src -DASSEMBLER -D__BSD_VISIBLE -Wno-implicit-function-declaration
ifneq ($(filter $(ARCH),i387 amd64 powerpc),)
CFLAGS_add += -I$(OPENLIBM_HOME)/ld80
else
ifneq ($(filter $(ARCH),aarch64),)
CFLAGS_add += -I$(OPENLIBM_HOME)/ld128
endif
endif


%.c.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CFLAGS_add) -c $< -o $@

%.S.o: %.S
	$(CC) $(CPPFLAGS) $(SFLAGS) $(SFLAGS_add) $(filter -m% -B% -I% -D%,$(CFLAGS_add)) -c $< -o $@


# Makefile debugging trick:
# call print-VARIABLE to see the runtime value of any variable
print-%:
	@echo '$*=$($*)'
