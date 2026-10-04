TARGET        := 67os
BUILD_DIR     := build
CROSS_COMPILE ?= arm-none-eabi-
CC            := $(CROSS_COMPILE)gcc
OBJCOPY       := $(CROSS_COMPILE)objcopy
SIZE          := $(CROSS_COMPILE)size

LDSCRIPT      := startup/link.ld
C_SOURCES     := $(wildcard core/*.c) $(wildcard kernel/*.c) $(wildcard drivers/*.c) $(wildcard utils/*.c) $(wildcard app/*.c)
ASM_SOURCES   := $(wildcard startup/*.s)
INCLUDES      := -Icore -Iconfig -Ikernel -Idrivers -Iutils -Iapp

CPU           := -mcpu=cortex-m4
FPU           := -mfpu=fpv4-sp-d16
FLOAT_ABI     := -mfloat-abi=hard
MCU           := $(CPU) -mthumb $(FPU) $(FLOAT_ABI)

OPT           := -O2
DEBUG         := -g3 -gdwarf-2

CFLAGS        := $(MCU) $(INCLUDES) $(OPT) $(DEBUG) -Wall -Wextra -ffunction-sections -fdata-sections -MMD -MP
ASFLAGS       := $(MCU) $(OPT) $(DEBUG) -Wall
LDFLAGS       := $(MCU) -T$(LDSCRIPT) -nostartfiles -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

OPENOCD       ?= openocd
OCD_ARGS      ?= -f interface/stlink.cfg -f target/stm32f4x.cfg
RM            := rm -f

OBJECTS       := $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS       += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(CC) -c -x assembler-with-cpp $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(LDSCRIPT) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR):
	-@mkdir $(BUILD_DIR)

size: $(BUILD_DIR)/$(TARGET).elf
	$(SIZE) $<

flash: $(BUILD_DIR)/$(TARGET).elf
	$(OPENOCD) $(OCD_ARGS) -c "program $< verify reset exit"

rebuild: clean all

clean:
	$(RM) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d
	$(RM) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).map

.PHONY: all size flash rebuild clean

-include $(wildcard $(BUILD_DIR)/*.d)
