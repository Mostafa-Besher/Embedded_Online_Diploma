################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.c 

OBJS += \
./HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.o 

C_DEPS += \
./HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.o: ../HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded_Diploma/assignments/6-Unit8_MCU_Interfacing/Lesson7/Lab/Drivers/HAL/Includes" -I"D:/Embedded_Diploma/assignments/6-Unit8_MCU_Interfacing/Lesson7/Lab/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

