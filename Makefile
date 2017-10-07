
#https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html#C
#This is an easier to use and modify makefile, but it is slightly more difficult to read than the simple one:
#
# 'make depend' uses makedepend to automatically generate dependencies 
#		(dependencies are added to end of Makefile)
# 'make'	build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# yes this is full of SPACES not tabs but seems to work?

# define the C compiler to use
#CC = gcc
CXX = g++

# define any compile-time flags
#CFLAGS = -Wall -g
CXXFLAGS = -std=c++11 -Wall

# define any directories containing header files other than /usr/include
#
#INCLUDES = -I/home/newhall/include  -I../include
#INCLUDES = -I/home/newhall/include  -I../include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LDFLAGS = -L/home/justin/MakeTest/test/amazing_libs -lamazing_library

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
#LDLIBS = -lmylib -lm

# define the C source files
#SRCS = emitter.c error.c init.c lexer.c main.c symbol.c parser.c
#SRCS = qs.cpp
SRCS = amazing_main.cpp

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#	 For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
#OBJS = $(SRCS:.c=.o)
#OBJS = $(SRCS:.cpp=.o)
# see below

# define the executable file 
MAIN = amazing

OBJDIR = obj

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

# Remember the second lines here MUST be tab indented

all:	$(MAIN)
	@echo Done!

# replace each bla.cpp with object_directory/bla.o
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# it means that the prerequisites that follow (in this case obj) are order-only prerequisites. This means that if any $(objects) must be built then obj must be built first, but if obj is out of date (or doesn't exist), that does not force $(objects) to be built
# https://stackoverflow.com/questions/4102469/makefile-to-put-object-files-from-source-files-different-directories-into-a-sing
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#.cpp.o:
	#$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJDIR)/*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
