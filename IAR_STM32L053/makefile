TARGET := stm32l053xx
OUTPUT_DIR := output
SOURCES_DIR := src

TOOLCHAIN_DIR := d:/Programs/EmbeddedWorkbench_8.2

CC := $(TOOLCHAIN_DIR)/arm/bin/iccarm
CFLAGS :=   --thumb\
            --cpu Cortex-M0+\
            -e\
            --debug\
            --dependencies=m $(OUTPUT_DIR)/dependencies
INCLUDE := -I$(SOURCES_DIR)/CMSIS/core/include\
           -I$(SOURCES_DIR)/CMSIS/device/include\
           -I$(SOURCES_DIR)/CMSIS\
           -I$(SOURCES_DIR)

AS := $(TOOLCHAIN_DIR)/arm/bin/iasmarm
AFLAGS :=   --thumb\
            --cpu Cortex-M0+\
            -r

LINKER  := $(TOOLCHAIN_DIR)/arm/bin/ilinkarm
LSCRIPT := $(SOURCES_DIR)/stm32l053xx_flash.icf
LFLAGS  :=  --config $(LSCRIPT)\
            --map $(OUTPUT_DIR)\
            --cpu Cortex-M0+

ELFTOOL := $(TOOLCHAIN_DIR)/arm/bin/ielftool

OBJECTS :=  main.o\
            startup_stm32l053xx.o\
            system_stm32l0xx.o

vpath %.c $(SOURCES_DIR)
vpath %.c $(SOURCES_DIR)/CMSIS
vpath %.s $(SOURCES_DIR)
vpath %.s $(SOURCES_DIR)/CMSIS/device

#--------------------------------------------------------
# add path to object names
_OBJ := $(addprefix $(OUTPUT_DIR)/objects/, $(OBJECTS))
#silent
S := @

.PHONY : build all
all: build
build : $(OUTPUT_DIR)/$(TARGET).elf

# link
$(OUTPUT_DIR)/$(TARGET).elf : $(_OBJ) makefile $(LSCRIPT)
	$(LINKER) $(_OBJ) $(LFLAGS) -o $@
	$(ELFTOOL) --ihex --verbose $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex

# assemble (.s)
$(OUTPUT_DIR)/objects/%.o : %.s makefile
	$(AS) $(AFLAGS) $(INCLUDE) $< -o $@

# compile, make listings and dependencies (.c)
$(OUTPUT_DIR)/objects/%.o : %.c makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -l $(OUTPUT_DIR)/listings/$*


clean:
	$(S)if exist $(OUTPUT_DIR)\objects\*.o del $(OUTPUT_DIR)\objects\*.o /F /Q
	$(S)if exist $(OUTPUT_DIR)\listings\*.lst del $(OUTPUT_DIR)\listings\*.lst /F /Q
	$(S)if exist $(OUTPUT_DIR)\dependencies\*.d del $(OUTPUT_DIR)\dependencies\*.d /F /Q
	$(S)if exist $(OUTPUT_DIR)\*.hex del $(OUTPUT_DIR)\*.hex /F /Q
	$(S)if exist $(OUTPUT_DIR)\*.map del $(OUTPUT_DIR)\*.map /F /Q
	$(S)if exist $(OUTPUT_DIR)\*.elf del $(OUTPUT_DIR)\*.elf /F /Q

-include $(OUTPUT_DIR)/dependencies/*.d