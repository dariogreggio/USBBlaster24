/********************************************************************
 FileName:      HardwareProfile.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, or PIC32 USB Microcontrollers
 Hardware:      The code is natively intended to be used on the 
                  following hardware platforms: 
                    PICDEM™ FS USB Demo Board
                    PIC18F46J50 FS USB Plug-In Module
                    PIC18F87J50 FS USB Plug-In Module
                    Explorer 16 + PIC24 or PIC32 USB PIMs
                    PIC24F Starter Kit
                    Low Pin Count USB Development Kit
                  The firmware may be modified for use on other USB 
                    platforms by editing this file (HardwareProfile.h)
 Compiler:  	Microchip C18 (for PIC18), C30 (for PIC24), 
                  or C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:


********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//#define DEMO_BOARD USER_DEFINED_BOARD

#if !defined(DEMO_BOARD)
    #if defined(__C32__)
        #if defined(__32MX460F512L__)
            #if defined(PIC32MX460F512L_PIM)
                #include "HardwareProfile - PIC32MX460F512L PIM.h"
            #elif defined(PIC32_USB_STARTER_KIT)
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #elif defined(__32MX795F512L__)
            #if defined(PIC32MX795F512L_PIM)
                #include "HardwareProfile - PIC32MX795F512L PIM.h"
            #elif defined(PIC32_USB_STARTER_KIT)
                //PIC32 USB Starter Kit II
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #endif
    #endif

    #if defined(__C30__)
        #if defined(__PIC24FJ256GB110__)
            #include "HardwareProfile - PIC24FJ256GB110 PIM.h"
        #elif defined(__PIC24FJ256GB210__)
            #include "HardwareProfile - PIC24FJ256GB210 PIM.h"
        #elif defined(__PIC24FJ256GB106__)
            #include "HardwareProfile - PIC24F Starter Kit.h"
        #elif defined(__PIC24FJ64GB004__) || defined(__PIC24FJ64GB002__) || defined(__PIC24FJ32GB002__)
            #include "HardwareProfile - PIC24FJ64GB004 PIM.h"
        #elif defined(__PIC24FJ256DA210__)
            #include "HardwareProfile - PIC24FJ256DA210 Development Board.h"
        #endif
	#define GetSystemClock()		(CLOCK_FREQ)      // Hz
	#define GetInstructionClock()	(GetSystemClock()/2)
	#define GetPeripheralClock()	GetInstructionClock()
    #endif

    #if defined(__18CXX)
        #if defined(__18F4550) | defined(__18F2550)		// igrometro, ott. 2010
            #include "HardwareProfile - PICDEM FSUSB.h"
        #elif defined(__18F87J50)
            #include "HardwareProfile - PIC18F87J50 PIM.h"
        #elif defined(__18F14K50)											// contaore, sett. 2010
            #include "HardwareProfile - Low Pin Count USB Development Kit.h"
        #elif defined(__18F46J50)
            #if defined(PIC18F_STARTER_KIT_1)
                #include "HardwareProfile - PIC18F Starter Kit 1.h"
            #else
                #include "HardwareProfile - PIC18F46J50 PIM.h"
            #endif
        #elif defined(__18F47J53)
            #include "HardwareProfile - PIC18F47J53 PIM.h"
        #endif
		#define GetSystemClock()		(48000000ul)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/4)
		#define GetPeripheralClock()	GetInstructionClock()
    #endif
#endif

#define FCY (GetSystemClock()/2)		// per LibPic30.h e delay

#if !defined(DEMO_BOARD)
    #error "Demo board not defined.  Either define DEMO_BOARD for a custom board or select the correct processor for the demo board."
#endif

#endif  //HARDWARE_PROFILE_H
