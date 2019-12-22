TARGET := atmega328p
OUTPUT_DIR := output
SOURCES_DIR := src

TOOLCHAIN_DIR := d:/Projects/toolchains/GNU_Tools_Avr/avr8-gnu-toolchain-win32_x86

CC := $(TOOLCHAIN_DIR)/bin/avr-gcc
CFLAGS :=   -c\
            -mmcu=atmega328p\
            -MMD -MP\
            -g3\
            -Os
INCLUDE := 
            
LINKER  := $(TOOLCHAIN_DIR)/bin/avr-gcc
#LSCRIPT := 
LFLAGS  :=  -mmcu=atmega328p

OBJDUMP := $(TOOLCHAIN_DIR)/bin/avr-objdump
OBJCOPY := $(TOOLCHAIN_DIR)/bin/avr-objcopy


OBJECTS :=  main.o

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
	@if exist $(OUTPUT_DIR)\objects\*.o del $(OUTPUT_DIR)\objects\*.o /F /Q
	@if exist $(OUTPUT_DIR)\listings\*.lst del $(OUTPUT_DIR)\listings\*.lst /F /Q
	@if exist $(OUTPUT_DIR)\dependencies\*.d del $(OUTPUT_DIR)\dependencies\*.d /F /Q
	@if exist $(OUTPUT_DIR)\*.hex del $(OUTPUT_DIR)\*.hex /F /Q
	@if exist $(OUTPUT_DIR)\*.map del $(OUTPUT_DIR)\*.map /F /Q
	@if exist $(OUTPUT_DIR)\*.elf del $(OUTPUT_DIR)\*.elf /F /Q

-include $(OUTPUT_DIR)/dependencies/*.d