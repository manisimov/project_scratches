TARGET := rx62n
OUTPUT_DIR := output
SOURCES_DIR := src

TOOLCHAIN_DIR := ~/toolchains/gcc_8.3.0.201904_gnurx-elf

CC := $(TOOLCHAIN_DIR)/bin/rx-elf-gcc
CFLAGS :=   -c\
            -mcpu=rx600\
            -mlittle-endian-data\
            -MMD -MP\
            -g3\
            -Os
INCLUDE := \
           -I$(SOURCES_DIR)/device\
           -I$(SOURCES_DIR)
            
LINKER  := $(TOOLCHAIN_DIR)/bin/rx-elf-gcc
LSCRIPT := $(SOURCES_DIR)/device/RX62N.ld
LFLAGS  :=  -T $(LSCRIPT)\
            -nostartfiles\
            -mcpu=rx600\
            -mlittle-endian-data\
            -e _PowerON_Reset\
            --specs=nosys.specs\
            --specs=nano.specs

OBJDUMP := $(TOOLCHAIN_DIR)/bin/rx-elf-objdump
OBJCOPY := $(TOOLCHAIN_DIR)/bin/rx-elf-objcopy


OBJECTS :=  main.o\
            startup.o\
            vector_table.o\
            interrupt_handlers.o\
            hardware_setup.o


vpath %.c $(SOURCES_DIR)
vpath %.c $(SOURCES_DIR)/device
vpath %.S $(SOURCES_DIR)
vpath %.S $(SOURCES_DIR)/device

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
	$(LINKER) $(_OBJ) $(LFLAGS) -o $@ -Wl,-Map,$(OUTPUT_DIR)/$(TARGET).map -Wl,--start-group -l "nosys" -l "gcc" -l "optc" -l "optm" -Wl,--end-group
	$(OBJCOPY) -O ihex $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex

# compile, make listings and dependencies (.S)
$(OUTPUT_DIR)/objects/%.o : %.S makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst

# compile, make listings and dependencies (.c)
$(OUTPUT_DIR)/objects/%.o : %.c makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst


clean:
	$(S)rm $(OUTPUT_DIR)/objects/*.o -f
	$(S)rm $(OUTPUT_DIR)/listings/*.lst -f
	$(S)rm $(OUTPUT_DIR)/dependencies/*.d -f
	$(S)rm $(OUTPUT_DIR)/*.hex -f
	$(S)rm $(OUTPUT_DIR)/*.map -f
	$(S)rm $(OUTPUT_DIR)/*.elf -f

-include $(OUTPUT_DIR)/dependencies/*.d
