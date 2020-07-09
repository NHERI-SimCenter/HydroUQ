# set some stuff
ARCH   = $(shell uname -m)
CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/SRC
EXECUTABLE = GLOp2SCSWOp

# set machine specific stuff
ifeq ($(ARCH),i686)    # host is i686 (PCs)
   MAKE = /usr/bin/make
endif
ifeq ($(ARCH),x86_64)   # host is 64 bit Opteron RRZN (lclog)
   MAKE = /usr/bin/make
endif

is:
	@echo '============= compiling ishi ======================='
	(cd $(SRCDIR);$(MAKE) -f Makefile $(EXECUTABLE))
	(mv $(SRCDIR)/$(EXECUTABLE) $(CURDIR)/$(EXECUTABLE))
	@echo '============== compiling successful ================'
