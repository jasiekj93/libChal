# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2023
# ------------------------------------------------

# Target
target := 

# Directories
project_dir ?= ../..
make_dir := $(project_dir)/make
external_dir := $(project_dir)/external

# Sources 
cxx_sources :=  \

# Includes
cxx_includes := \

# Defines
cxx_defs := \

# Libraries
library_includes = \

library_flags = \

external_library_flags = \

external_library_paths = \

# Append rest of Makefile from template
include $(make_dir)/SoftwareTestLib.mk