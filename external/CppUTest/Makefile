# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
target = libCppUTest
#PLATFORM = CortexM7
PLATFORM = Pc32

ifeq (PLATFORM, Pc32)
target += Pc32
endif

# debug
DEBUG = 1
GEN_LST = 0
OPT = -Og

# directories
build_dir = build/$(target)
lib_dir = lib/$(PLATFORM)

# toolchain
ifeq ($(PLATFORM), Pc32)
PREFIX = 
else
PREFIX = arm-none-eabi-
endif

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# mcu definition
ifeq ($(PLATFORM), Pc32)
MCU = -m32
else
CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
endif 

# sources 
cxx_sources =  \
$(wildcard CppUTest/*.cpp) \

# includes
cxx_includes =  \
-Iinclude \

#defines
ifeq ($(PLATFORM), Pc32)
use_std_lib = 1
else
use_std_lib = 0
endif

cxx_defs = \
-DCPPUTEST_USE_STD_CPP_LIB=$(use_std_lib)

# gcc flags
CXXFLAGS = $(MCU) $(cxx_defs) $(cxx_includes) $(OPT) -std=c++17 -Wall 

ifneq ($(PLATFORM), Pc32)
CXXFLAGS += -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions -nostdlib
endif

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information as 'make' rules
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Generate assembly output into build directory
ifeq ($(GEN_LST), 1)
CXXFLAGS += -Wa,-a,-ad,-alms=$(build_dir)/$(notdir $(<:.cpp=.lst))
endif

# Targets
.PHONY: all print clean distclean

all: $(lib_dir)/$(target).a

print-%: ; @echo $* = $($*)

# list of objects
objects = $(addprefix $(build_dir)/,$(notdir $(cxx_sources:.cpp=.o)))
vpath %.cpp $(sort $(dir $(cxx_sources)))

# list of C++ objects
objects = $(addprefix $(build_dir)/,$(notdir $(cxx_sources:.cpp=.o)))
vpath %.cpp $(sort $(dir $(cxx_sources)))

# build C++ objects
$(build_dir)/%.o: %.cpp Makefile | $(build_dir)
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) $< -o $@

# build library
$(lib_dir)/$(target).a: $(objects) Makefile | $(lib_dir)
	@echo Creating library $@
	@$(AR) rcs $@ $(objects) 

# create directories
$(build_dir):
	@echo Create directory $@
	@mkdir -p $@		

$(lib_dir):
	@echo Creating directory $@
	@mkdir -p $@

# clean up
clean:
	@echo Cleaning
	@rm -rf $(build_dir)

distclean:
	@echo Restoring project folder to default state
	@rm -rf $(build_dir)
	@rm -rf $(lib_dir)
  
# dependencies
-include $(wildcard $(build_dir)/*.d)
