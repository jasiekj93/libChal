# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
target = libChal

# debug
DEBUG = 1
OPT = -O0

# directories
build_dir = build/$(target)
lib_dir = lib

# toolchain
prefix = arm-none-eabi-

CXX = $(prefix)g++
AS = $(prefix)gcc -x assembler-with-cpp
CP = $(prefix)objcopy
SZ = $(prefix)size
AR = $(prefix)ar
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# mcu definition
cpu = -mcpu=cortex-m4
fpu = -mfpu=fpv4-sp-d16
float-abi = -mfloat-abi=hard
mcu = $(cpu) -mthumb $(fpu) $(float-ABI)

# sources 
cxx_sources =  \
$(wildcard $(target)/*.cpp) \

# includes
cxx_includes = \
-I. \

# gcc flags
CXXFLAGS = $(mcu) $(cxx_defs) $(cxx_includes) $(OPT) -std=c++17  
CXXFLAGS += -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions -fno-rtti

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# select recipes
.PHONY: all library tests clean distclean

# build all
all:  library tests

library: $(lib_dir)/$(target).a

tests: library
	$(MAKE) -C tests

print-%  : ; @echo $* = $($*)

# list of C++ objects
objects = $(addprefix $(build_dir)/,$(notdir $(cxx_sources:.cpp=.o)))
vpath %.cpp $(sort $(dir $(cxx_sources)))

# build C++ objects
$(build_dir)/%.o: %.cpp Makefile | $(build_dir)
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(build_dir)/$(notdir $(<:.cpp=.lst)) $< -o $@

# build library
$(lib_dir)/$(target).a: $(objects) Makefile | $(lib_dir)
	@echo Creating library $@
	@$(AR) rcs $@ $(objects) 

# create directories
$(build_dir):
	@echo Creating directory $@
	@mkdir -p $@		

$(lib_dir):
	@echo Creating directory $@
	@mkdir -p $@

# clean up
clean:
	@echo Cleaning
	@rm -rf $(build_dir)

distclean:
	@echo Dist Cleaning
	@rm -rf $(build_dir) $(lib_dir)

  
# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)
