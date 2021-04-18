/* linker_script cortexM3
Eng.Mostafa_Besher
*/


MEMORY
{
	FLASH(RX): ORIGIN = 0x08000000, LENGTH = 128k
	SRAM(RWX): ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		*(.rodata)
		. = ALIGN(4);
		_E_text = .;
	}>FLASH
	.data :
	{
		_S_data = .;
		*(.data)
		. = ALIGN(4);
		_E_data = .;
	}>SRAM AT> FLASH
	.bss :
	{
		_S_bss = .;
		*(.bss)
		_E_bss = .;
		
		. = ALIGN(4);
		. = . + 0x1000;
		_stack_top = .;
	}>SRAM
	
	
}