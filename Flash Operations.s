;*************************************************************************
;*
;*   Emulating Data EEPROM for PIC24 Microcontrollers and
;*           dsPIC Digital Signal Controllers
;*
;*************************************************************************
;* FileName:     Flash Operations.s
;* Compiler:     MPLAB C30, v2.01 or higher
;* Company:      Microchip Technology, Inc.
;*
;* Software License Agreement
;*
;* Copyright © 2007 Microchip Technology Inc. All rights reserved.
;*
;* Microchip licenses to you the right to use, modify, copy and distribute
;* Software only when embedded on a Microchip microcontroller or digital
;* signal controller, which is integrated into your product or third party
;* product (pursuant to the sublicense terms in the accompanying license
;* agreement).
;*
;* You should refer to the license agreement accompanying this Software for
;* additional information regarding your rights and obligations.
;*
;* Author        Date        Comment
;*************************************************************************
;* D. Otten      2007/05/01  Version 1.0.0 - Initial Release
;* D. Otten      2007/05/15  Version 1.0.1 - First publication release
;************************************************************************/
.global _ReadPMHigh
.global _ReadPMLow
.global _UnlockPM
.global _WritePMHigh
.global _WritePMHighB
.global _WritePMLow
.global _WritePMLowB

.section .text
_ReadPMHigh:
	tblrdh [W0],W0
	return

_ReadPMLow:
	tblrdl [W0],W0
	return		
	
_UnlockPM:
	push	W0
	disi	#5
	mov		#0x55,W0
	mov		W0, NVMKEY
	mov		#0xAA, W0
	mov		W0, NVMKEY
	bset	NVMCON, #15
	nop
	nop
	btsc	NVMCON, #15
	bra		$-2
	pop		W0
	return	
	
_WritePMHigh:
	tblwth	W0,[W1]
	return

_WritePMHighB:
	tblwth.b	W0,[W1]
	return

_WritePMLow:
	tblwtl	W0,[W1]
	return

_WritePMLowB:
	tblwtl.b	W0,[W1]
	return
	
.end
