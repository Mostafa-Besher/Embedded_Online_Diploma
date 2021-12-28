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
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/UART" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/RCC" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/HAL/inc" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/HAL/Kepad_Driver" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/HAL/LCD_Driver" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/inc" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/GPIO" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/inc" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL/Timer" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/MCAL" -I"D:/Embedded_Diploma/assignments/8-Smart_Parking/Smart_Parking/HAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Driver/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

