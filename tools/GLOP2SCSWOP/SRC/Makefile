#Make file to compile the program

#*************************************************************
# Variables to control the makefile operation
#*************************************************************
#Name of the program
EXECUTABLE = GLOp2SCSWOp

#Information on machine type
ARCH = $(shell uname -m)

#Information on current directory
CURDIR = $(shell pwd)

#Location of source files
SRCDIR = SRC

#Location of obj files
OBJDIR = ../OBJ

#Dir with all obj files
ODIR = ../64b

#Compiler to be used
CC = g++

#Flag for all warnings & add debug information
CFLAGS = -Wall -g

#Include the header files
INC = include -Iinclude/Eigen

#Create list of directories that need to be compiled
SRCDIRS = main geoclawUtils genUtils

#*************************************************************
# Targets needed to bring the executable up to date
#*************************************************************

# Get the cpp files in each directory
SRCc   = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
#SRCco   = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

# Get the list of obj files in each directory
OBJsrcc := $(addprefix $(OBJDIR)/, $(SRCc:.cpp=.o))
#OBJsrcco := $(addprefix $(OBJDIR)/, $(SRCc:.c=.o))

# Executable is compiled for each obj file from the
# .o files stored in 64b
$(EXECUTABLE): $(OBJsrcc) $(OBJsrcco)
	$(CC) $(CFLAGS) $(ODIR)/*.o -o $@

# dependencies
#.SUFFIXES: .cpp .c
	
# Each cpp file is linked to its .o file 
# stored in the OBJ folder and copied to 64b
$(OBJDIR)/%o: %cpp
	$(CC) $(CFLAGS) -c -I$(INC) $< -o $@
	(cp $@ $(ODIR))
#$(OBJDIR)/%o: %c
#	$(CC) $(CFLAGS) -c -I$(INC) $< -o $@
#	(cp $@ $(ODIR))