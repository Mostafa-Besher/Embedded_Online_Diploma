#@copyright : Mostafa_Besher
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS= -I .
LIBS=
SRC= $(wildcard *.c) 
OBJ= $(SRC:.c=.o)
As= $(wildcard *.s) 
AsOBJ= $(As:.s=.o)
Project_name=Pressure_Detection


all: $(Project_name).bin
	@echo "=======Build is complete======="
	
%.o: %.c	
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $(Project_name).elf -Map=map_file.map
	
$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
	rm *.o *.elf *.bin
clean:
	rm *.elf *.bin
	
