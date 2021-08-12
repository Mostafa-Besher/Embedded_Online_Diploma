################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD_Driver/lcd.c 

OBJS += \
./HAL/LCD_Driver/lcd.o 

C_DEPS += \
./HAL/LCD_Driver/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LCD_Driver/lcd.o: ../HAL/LCD_Driver/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/Embedded_Diploma/assignments/5_Unit7_MCU_Essential Peripherals/Lesson4/Lab/Drivers/HAL/LCD_Driver" -I../Inc -I"D:/Embedded_Diploma/assignments/5_Unit7_MCU_Essential Peripherals/Lesson4/Lab/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Driver/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

