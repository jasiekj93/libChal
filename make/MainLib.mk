# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2022
# ------------------------------------------------

# This file is only a template and should be included 
# in other Makefile
ifeq ($(PLATFORM), Pc32)
target := $(target)Pc32
endif

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

external_dirs := $(addprefix $(external_lib_dir)/, $(external_names))
external_library_includes := $(addprefix -I$(external_lib_dir)/, $(external_names))

# Includes
cxx_includes += \
$(external_library_includes) \

# Append GCC flags variables from file here
include $(make_dir)/Flags.mk

# targets
.PHONY: all $(external_dirs) library pcLibrary tests clean distclean rebuild

all: $(external_dirs) library pcLibrary tests
	@echo "Building time: [$(build_time) seconds]"

library: $(external_dirs) $(lib_dir)/$(target).a

pcLibrary: 
	+@$(MAKE) -C . library PLATFORM=Pc32 

tests:
	+@$(MAKE) -C tests PLATFORM=Pc32

$(external_dirs):
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
