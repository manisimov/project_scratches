TARGET := template
OUTPUT_DIR := output
SOURCES_DIR := src

TOOLCHAIN_DIR := d:/Projects/toolchains/GNU_Tools_Arm_Embedded/8_2018-q4-major

CC := $(TOOLCHAIN_DIR)/bin/arm-none-eabi-gcc
CFLAGS :=   -c\
            -mthumb\
            -mcpu=cortex-m4\
            -mlittle-endian\
            -MMD -MP\
            -D__SAM4SD32C__\
            -D __STACK_SIZE=0x400\
            -g3\
            -O1
INCLUDE := -I$(TOOLCHAIN_DIR)/arm-none-eabi/include\
           -I$(SOURCES_DIR)/CMSIS/core/include\
           -I$(SOURCES_DIR)/CMSIS/device/include\
           -I$(SOURCES_DIR)/CMSIS\
           -I$(SOURCES_DIR)
            
LINKER := $(TOOLCHAIN_DIR)/bin/arm-none-eabi-gcc
LSCRIPT := $(SOURCES_DIR)/template.ld
LFLAGS :=   -T $(LSCRIPT)\
            -mthumb\
            -mcpu=cortex-m4\
            --specs=nosys.specs\
            --specs=nano.specs

OBJDUMP := $(TOOLCHAIN_DIR)/bin/arm-none-eabi-objdump
OBJCOPY := $(TOOLCHAIN_DIR)/bin/arm-none-eabi-objcopy


OBJECTS :=  main.o\
            startup_SAM4S.o\
            system_SAM4S.o

vpath %.c $(SOURCES_DIR)
vpath %.c $(SOURCES_DIR)/CMSIS
vpath %.S $(SOURCES_DIR)
vpath %.S $(SOURCES_DIR)/CMSIS/device

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
#	$(OBJCOPY) -O ihex $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex

# compile, make listings and dependencies (.S)
$(OUTPUT_DIR)/objects/%.o : %.S makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst

# compile, make listings and dependencies (.c)
$(OUTPUT_DIR)/objects/%.o : %.c makefile
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -MF $(OUTPUT_DIR)/dependencies/$*.d
	$(S)$(OBJDUMP) -d -S $@ > $(OUTPUT_DIR)/listings/$*.lst


clean:
	del $(OUTPUT_DIR)\objects\*.o /F /Q
	del $(OUTPUT_DIR)\listings\*.lst /F /Q
	del $(OUTPUT_DIR)\dependencies\*.d /F /Q
	del $(OUTPUT_DIR)\*.hex /F /Q
	del $(OUTPUT_DIR)\*.map /F /Q
	del $(OUTPUT_DIR)\*.elf /F /Q

-include $(OUTPUT_DIR)/dependencies/*.d