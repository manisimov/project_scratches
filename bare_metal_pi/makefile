TARGET := rasppi
OUTPUT_DIR := output
SOURCES_DIR := src

CC := arm-none-eabi-gcc
CFLAGS :=   -c\
            -mcpu=arm1176jzf-s\
            -nostdlib\
            -nostartfiles\
            -ffreestanding\
            -MMD -MP\
            -g3\
            -O0
INCLUDE := \
           -I$(SOURCES_DIR)
            
LINKER  := arm-none-eabi-gcc
LSCRIPT := $(SOURCES_DIR)/rasppi.ld
LFLAGS  :=  -T $(LSCRIPT)\
            -mcpu=arm1176jzf-s\
            -nostdlib\
            -nostartfiles\
            -e _start
OBJDUMP := arm-none-eabi-objdump
OBJCOPY := arm-none-eabi-objcopy


OBJECTS :=  main.o\
            start.o

vpath %.c $(SOURCES_DIR)
vpath %.S $(SOURCES_DIR)

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
	$(LINKER) $(_OBJ) $(LFLAGS) -o $@ -Wl,-Map,$(OUTPUT_DIR)/$(TARGET).map
	$(OBJCOPY) -O binary $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).bin

# compile, make listings and dependencies (.S)
$(OUTPUT_DIR)/objects/%.o : %.S makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst

# compile, make listings and dependencies (.c)
$(OUTPUT_DIR)/objects/%.o : %.c makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst
	
debug:
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel output/rasppi.elf -s -S &
	gdb-multiarch -x src/start.gdb


clean:
	$(S)rm $(OUTPUT_DIR)/objects/*.o -f
	$(S)rm $(OUTPUT_DIR)/listings/*.lst -f
	$(S)rm $(OUTPUT_DIR)/dependencies/*.d -f
	$(S)rm $(OUTPUT_DIR)/*.bin -f
	$(S)rm $(OUTPUT_DIR)/*.map -f
	$(S)rm $(OUTPUT_DIR)/*.elf -f

-include $(OUTPUT_DIR)/dependencies/*.d

