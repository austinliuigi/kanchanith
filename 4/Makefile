# CPP Makefile
BINARY=4
BUILDDIR=./bin
SRCDIRS=.

INCDIRS=$(shell find $(SRCDIRS) -type d)

# Specify compiler
CXX=g++
# Options that tell compiiler to generate Makefiles that have .d
DEPFLAGS=-MMD -MP
# Prefix -I onto each include directory
INCFLAGS=$(addprefix -I,$(INCDIRS))
# Compiler options
CXXFLAGS=-Wall -Wextra $(DEPFLAGS) $(INCFLAGS) 

# Get list of source files we have
SRCFILES=$(shell find $(SRCDIRS) -name '*.cpp')
# Get list of object files we want to create
OBJFILES=$(patsubst %.cpp,$(BUILDDIR)/buildfiles/%.o,$(SRCFILES))
# Get list of dependency files we want to create
DEPFILES=$(patsubst %.o,%.d,$(OBJFILES))

all: $(BUILDDIR)/$(BINARY)
	cp $(BUILDDIR)/$(BINARY) .

$(BUILDDIR)/$(BINARY): $(OBJFILES)
	mkdir -p $(dir $@)
	$(CXX) -o $@ $^

$(BUILDDIR)/buildfiles/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -r $(BUILDDIR)
	rm $(BINARY)
	rm map.txt

# Include the dependencies
-include $(DEPFILES)
