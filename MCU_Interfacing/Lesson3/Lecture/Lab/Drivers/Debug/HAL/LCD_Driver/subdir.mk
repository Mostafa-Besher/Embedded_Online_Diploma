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
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded_Diploma/assignments/6-Unit8_MCU_Interfacing/Lesson3/Lecture/Lab/Drivers/stm32_f103c6_Drivers/inc" -I"D:/Embedded_Diploma/assignments/6-Unit8_MCU_Interfacing/Lesson3/Lecture/Lab/Drivers/HAL/LCD_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Driver/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

