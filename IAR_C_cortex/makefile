TARGET := first
OUTPUT_DIR := output
SOURCES_DIR := src

AS := iasmarm
AS_FLAGS := -L$(OUTPUT_DIR)/listings\
            -D__SAM4SD32C__\
            -r\
            --cpu Cortex-M4

LINKER := ilinkarm
LFLAGS := --config src/linker_script.icf\
          --no_library_search\
          --no_entry\
          --map $(OUTPUT_DIR)
          
ELF_TOOL := ielftool

OBJECTS :=  first.o

vpath %.s $(SOURCES_DIR)

#--------------------------------------------------------
# add path to object names
_OBJ := $(addprefix $(OUTPUT_DIR)/objects/, $(OBJECTS))

all : build
build : $(OUTPUT_DIR)/$(TARGET).elf

# link
$(OUTPUT_DIR)/$(TARGET).elf : $(_OBJ) makefile
	$(LINKER) $(LFLAGS) $< -o $@
	$(ELF_TOOL) --ihex $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex

# assemble
$(OUTPUT_DIR)/objects/%.o : %.s makefile
	$(AS) $(AS_FLAGS) $< -o $@
    
clean:
	del $(OUTPUT_DIR)\objects\*.o /F /Q
	del $(OUTPUT_DIR)\listings\*.lst /F /Q
	del $(OUTPUT_DIR)\*.hex /F /Q
	del $(OUTPUT_DIR)\*.map /F /Q
	del $(OUTPUT_DIR)\*.elf /F /Q