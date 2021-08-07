################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32_f103c6_Drivers/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include LCD_Driver/subdir.mk
-include Kepad_Driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lcd_keypad.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lcd_keypad.list \

OBJCOPY_BIN += \
lcd_keypad.bin \


# All Target
all: lcd_keypad.elf secondary-outputs

# Tool invocations
lcd_keypad.elf: $(OBJS) $(USER_OBJS) D:\Embedded_Diploma\assignments\5_Unit7_MCU_Essential\ Peripherals\Lesson3\section\lcd_keypad\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "lcd_keypad.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Embedded_Diploma\assignments\5_Unit7_MCU_Essential Peripherals\Lesson3\section\lcd_keypad\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lcd_keypad.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lcd_keypad.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lcd_keypad.list"
	@echo 'Finished building: $@'
	@echo ' '

lcd_keypad.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "lcd_keypad.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
