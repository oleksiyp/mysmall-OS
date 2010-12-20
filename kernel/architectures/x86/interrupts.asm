section _TEXT PUBLIC CLASS=CODE

use32
extern _c_x86_int_timerHandler
global _x86_int_timerHandler

_x86_int_timerHandler:
	int 3
	call _c_x86_int_timerHandler
	iret