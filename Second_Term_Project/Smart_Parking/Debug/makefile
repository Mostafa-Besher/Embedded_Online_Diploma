################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/Timer/subdir.mk
-include MCAL/RCC/subdir.mk
-include MCAL/GPIO/subdir.mk
-include HAL/Servo_Motor/subdir.mk
-include HAL/LCD_Driver/subdir.mk
-include HAL/Kepad_Driver/subdir.mk
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
Smart_Parking.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Smart_Parking.list \

OBJCOPY_BIN += \
Smart_Parking.bin \


# All Target
all: Smart_Parking.elf secondary-outputs

# Tool invocations
Smart_Parking.elf: $(OBJS) $(USER_OBJS) D:\Embedded_Diploma\assignments\8-Smart_Parking\Smart_Parking\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Smart_Parking.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Embedded_Diploma\assignments\8-Smart_Parking\Smart_Parking\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Smart_Parking.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Smart_Parking.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Smart_Parking.list"
	@echo 'Finished building: $@'
	@echo ' '

Smart_Parking.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Smart_Parking.bin"
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
