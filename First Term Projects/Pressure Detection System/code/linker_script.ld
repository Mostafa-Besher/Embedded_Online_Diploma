/* linker_script cortex-M3
Eng.Mostafa_Besher
*/


MEMORY
{
	ROM(RX) : ORIGIN =  0x08000000,  LENGTH = 128k
	RAM(RXW): ORIGIN =  0x20000000,	LENGTH = 20k
}

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_text = .;
	}> ROM
	.data :
	{
		_S_data = .;
		*(.data)
		_E_data = .;
	}> RAM AT> ROM
	.bss :
	{
		_S_bss = .;
		*(.bss)
		_E_bss = .;
		. = ALIGN(4);
	}> RAM
	. = . + 0x1000;
	_stack_top = .;
}