/*startup_cortex-m3.s
Eng.Mostafa_Besher
*/

.section .vectors

.word 0x20001000		/*stack_top address*/
.word _reset			/* reset section*/
.word vector_handler	/*NMI */
.word vector_handler	/*HARD FAULT*/
.word vector_handler	/*MM FAULT*/
.word vector_handler	/*BUS FAULT*/
.word vector_handler	/*USAGE FAULT*/
.word vector_handler	/*RESERVED*/
.word vector_handler	/*RESERVED*/
.word vector_handler	/*RESERVED*/
.word vector_handler	/*RESERVED*/
.word vector_handler	/*sv call*/
.word vector_handler	/*debug reserved*/
.word vector_handler	/*RESERVED*/
.word vector_handler	/*Pend sv*/
.word vector_handler	/*systick*/
.word vector_handler	/*IRQ 0*/
.word vector_handler	/*IRQ 1*/
.word vector_handler	/*IRQ 2*/


.section .text

_reset:
		bl main
		b .
		
.thumb_func
vector_handler:
		b _reset