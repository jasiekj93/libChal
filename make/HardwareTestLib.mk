# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2023
# ------------------------------------------------

# This file is only a template and should be included 
# in other Makefile

project_dir := ../..
PLATFORM := ARM

# Append Configuration variables from file here
include $(make_dir)/Configuration.mk

# libraries
LDFLAGS := \
$(external_library_paths)

# Includes
cxx_includes += \
$(library_includes) \

# libraries
LDLIBS := -lc -lm -lnosys \
$(library_flags) \
$(external_library_flags) \

binary_extensions := elf hex bin
binaries := $(addprefix $(test_dir)/$(target)., $(binary_extensions))

# Append GCC flags variables from file here
include $(make_dir)/Flags.mk

# Linker script to linker flags
LDFLAGS += -T$(ldscript)

# Targets
.PHONY: all clean

all: $(binaries) 

print-%  : ; @echo "$* = $($*)"

# Append rules for building object files, libraries and executables
include $(make_dir)/BuildRules.mk

# clean up
clean:
	@echo Cleaning	
	@$(RMDIR) $(build_dir)

