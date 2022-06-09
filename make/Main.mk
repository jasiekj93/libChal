# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2022
# ------------------------------------------------

# This file is only a template and should be included 
# in other Makefile

# Append Configuration variables from file here
include $(make_dir)/Configuration.mk

# Measuring time feature
# start_time variable is expanded immiediate at the beggining of make process,
# the others are expanded (and executed) during every usage 
# (in this case at the end of build process).
start_time := $(shell date +%s)
end_time = $(shell date +%s)
build_time = $(shell expr $(end_time) - $(start_time) )

project_dir := .

library_dirs := $(addprefix lib$(target)-, $(library_names))
external_dirs := $(addprefix $(external_lib_dir)/, $(external_names))

library_includes := $(addprefix -I, $(library_dirs))
library_flags := $(addprefix -l$(target)-,$(notdir $(library_names)))

external_library_includes := $(addprefix -I$(external_lib_dir)/, $(external_names))
external_library_flags := $(addprefix -l, $(external_lib_names))
external_search_path := $(addprefix -L$(external_lib_dir)/, $(external_lib_dirs))

binary_extensions := elf hex bin
binaries := $(addprefix $(bin_dir)/$(target)., $(binary_extensions))

# Includes
cxx_includes += \
$(library_includes) \
$(external_library_includes) \

# Libraries
LDLIBS := -lc -lm -lnosys 
LDLIBS += $(library_flags) $(external_library_flags) 
LDLIBS += $(library_flags) $(external_library_flags) 

# Library path
LDFLAGS	+= $(external_search_path)

# Append GCC flags variables from file here
include $(make_dir)/Flags.mk

# Linker script to linker flags
LDFLAGS += -T$(ldscript)

# targets
.PHONY: all $(external_dirs) $(library_dirs) $(binaries) clean distclean rebuild

all: $(external_dirs) $(library_dirs) $(binaries)
	@echo "Building time: [$(build_time) seconds]"

$(binaries): $(external_dirs) $(library_dirs)

$(library_dirs): $(external_dirs)

$(library_dirs) $(external_dirs):
	@echo Making libraries:
	+@$(MAKE) --directory=$@

print-%: ; @echo "$* = $($*)"

# Append rules for building object files, libraries and executables
include $(make_dir)/BuildRules.mk

# rebuild
rebuild:
	@$(RMDIR) $(bin_dir)
	+@$(MAKE) -C .
 
# clean up
clean:
	@echo Cleaning
	@$(RMDIR) $(build_root_dir)

distclean:
	@echo Restoring project folder to default state
	@$(RMDIR) $(build_root_dir)
	@$(RMDIR) $(bin_dir)
	@$(RMDIR) $(lib_dir)
	@$(RMDIR) $(test_dir)
	+@for dir in $(external_dirs); do \
		$(MAKE) --directory=$$dir distclean; \
	done
