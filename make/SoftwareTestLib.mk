# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2023
# ------------------------------------------------

# This file is only a template and should be included 
# in other Makefile

project_dir ?= ../..
PLATFORM := Pc32

# Append Configuration variables from file here
include $(make_dir)/Configuration.mk


# libraries
LDFLAGS := \
-L$(external_lib_dir)/CppUTest/lib/Pc32 \
$(external_library_paths)

# Includes
cxx_includes += \
$(library_includes) \
-I$(external_lib_dir)/CppUTest/include \

# libraries
LDLIBS := \
-lCppUTest \
$(library_flags) \
$(external_library_flags) \

# Append GCC flags variables from file here
include $(make_dir)/Flags.mk

# Targets
.PHONY: all clean

all: $(test_dir)/$(target).elf
	@$(test_dir)/$(target).elf

print-%  : ; @echo "$* = $($*)"

# Append rules for building object files, libraries and executables
include $(make_dir)/BuildRules.mk

# clean up
clean:
	@echo Cleaning	
	@$(RMDIR) $(build_dir)

