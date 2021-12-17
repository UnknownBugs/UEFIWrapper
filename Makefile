include UefiWrapperInclude.mk

# project dir
TOP_DIR := $(shell pwd)

CXX := x86_64-w64-mingw32-g++
CXX_FLAGS := -Wall -Wextra -e efi_main -nostdinc -nostdlib \
        -fno-builtin -Wl,--subsystem,10

SRC := test/debug.cpp

EFI := bin/debug.efi
EFI := $(addprefix $(TOP_DIR)/,$(EFI))

UEFIWRAPPER_LIB_INC := $(addprefix -I$(TOP_DIR)/,$(UEFIWRAPPER_LIB_INC))

$(EFI): $(SRC)
	@echo + $@
	mkdir -p bin
	$(CXX) -o $@ $(CXX_FLAGS) $(SRC) $(UEFIWRAPPER_LIB_INC)

.PHONY : clean

clean :
	rm -rf bin