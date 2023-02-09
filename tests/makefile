CPPUTEST_HOME := cpputest/
build_folder := build/
program_dir := ../src/


#COMPILER AND LINKER FLAGS
CC = g++
CXXFLAGS += -Wall
CPPFLAGS += -D IS_RUNNING_TESTS
CPPFLAGS += -I$(CPPUTEST_HOME)include/ -I$(program_dir) -I./
LDLIBS += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

#OPTIONS
quiet := @

#RULES
all: make_dir tests
	$(quiet)echo "RGB led tests"
	$(quiet)./tests 

cpp_files  = $(wildcard *.cpp)
cpp_files += $(notdir $(wildcard $(program_dir)*.cpp))
cpp_files += $(notdir $(wildcard mocks/*.cpp))
objects_to_link  = $(addprefix $(build_folder), $(patsubst %.cpp, %.o, $(cpp_files)))

tests: $(objects_to_link)
	$(quiet)$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@


vpath %.cpp mocks/
vpath %.cpp $(program_dir)

$(build_folder)%.o: %.cpp
	$(quiet)$(COMPILE.cpp) $(OUTPUT_OPTION) $<

make_dir:
	$(quiet)mkdir -p $(build_folder)

clean:
	$(quiet)echo "Removing old data"
	$(quiet)rm -f tests
	$(quiet)rm -rf build/

print:
	echo $(objects_to_link)
 