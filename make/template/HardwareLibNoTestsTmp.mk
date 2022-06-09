# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2022
# ------------------------------------------------

# Target
target := 

# Directories
project_dir := ..
make_dir := $(project_dir)/make
external_dir := $(project_dir)/external

# Sources 
cxx_sources =  \

c_sources := \

asm_sources := \

# Includes
cxx_includes :=  \

# Defines
cxx_defs := \

# Append rest of Makefile from template
include $(make_dir)/HardwareLibNoTests.mk
