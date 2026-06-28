/********************************************************************
 FileName:      HardwareProfile - PIC24F Starter Kit.h
 Dependencies:  See INCLUDES section
 Processor:     PIC24FJ256GB106
 Hardware:      PIC24F Starter Kit
 Compiler:      Microchip C30
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.


********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
	2.4   28/6/2026		 riallineamento; bootloader; morte a TUTTI TUTTI
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC24F_STARTER_KIT_H
#define HARDWARE_PROFILE_PIC24F_STARTER_KIT_H

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  U1OTGSTATbits.SESVD  //TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       U1OTGSTATbits.SESVD
   
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
#ifdef USA_BOOTLOADER
    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER	
#endif

    //If the application is going to be used with the HID bootloader
    //  then this will provide a function for the application to 
    //  enter the bootloader from the application (optional)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        #define EnterBootloader() __asm__("goto 0x400")
    #endif   

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These definitions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC24F_STARTER_KIT
    #define PIC24F_STARTER_KIT
    #define CLOCK_FREQ 32000000ul
   	#define GetSystemClock()		(CLOCK_FREQ)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/2)
		#define GetPeripheralClock()	GetInstructionClock()
   	#define FCY GetInstructionClock()		// per delay
   
    /** LED ************************************************************/
    #define mInitAllLEDs()      LATA &= 0xffef; TRISA &= 0xffef; LATB &= 0xfff3; TRISB &= 0xfff3; //RA4, RB2 RB3
    
    #define mGetLED_1()         (LATB & 0x0004 ? 1 : 0)
    #define mGetLED_2()         (LATB & 0x0008 ? 1 : 0)
    #define mGetLED_3()         (LATA & 0x0010 ? 1 : 0)
    #define mGetLED_4()              

    #define mLED_1_On()         LATB |= 0x0004; 
    #define mLED_2_On()         LATB |= 0x0008; 
    #define mLED_3_On()         LATA |= 0x0010; 
    #define mLED_4_On()          
    
    #define mLED_1_Off()        LATB &= ~0x0004; 
    #define mLED_2_Off()      	LATB &= ~0x0008; 
    #define mLED_3_Off()        LATA &= ~0x0010; 
    #define mLED_4_Off()         
    
    #define mLED_1_Toggle()     __builtin_btg(&LATB,2)			// ^= 0x0004;
    #define mLED_2_Toggle()     __builtin_btg(&LATB,3)			// ^= 0x0008;
    #define mLED_3_Toggle()     __builtin_btg(&LATA,4)			// ^= 0x0010;
    #define mLED_4_Toggle()      
    
    /** SWITCH *********************************************************/
    #define mInitSwitch1()      BUTTON0_TRIS=1;
    #define mInitSwitch2()      BUTTON1_TRIS=1;
    #define mInitAllSwitches()  mInitSwitch1();mInitSwitch2();
    #define sw1                 BUTTON0_IO
    #define sw2                 BUTTON1_IO

    /** POT ************************************************************/
    #define mInitPOT()  {}

		#define m_Rele LATAbits.LATA0

//Use SPI Module
#define USE_SPI

//SPI Freq Setting
#define SPI_12MHz
//#define SPI_3MHz

//output port definition
#define OUTP LATC
#define LTDI LATCbits.LATC4		//TDI
#define LTCK LATCbits.LATC0		//TCK
#define LACT LATBbits.LATB7		//Activity LED

//SPI,PIO output tris definition
#ifdef USE_SPI
#define TSDO TRISCbits.TRISC7	//SPI:TDI
#define TTDI TRISCbits.TRISC4	//PIO:TDI
#define TSCK TRISBbits.TRISB6	//SPI:TCK
#define TTCK TRISCbits.TRISC0	//PIO:TCK
#endif

//input tris definitions for PIO
#define TTDO TRISBbits.TRISB4	//JTAG:TDO
#define TADO TRISBbits.TRISB5	//AS:ASDO

//input port definitions
#define PTDO PORTBbits.RB4		//JTAG:TDO
#define PADO PORTBbits.RB5		//AS:ASDO
    
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

	#define BUTTON0_TRIS		(TRISBbits.TRISB5)	// Ref Sw1
	#define	BUTTON0_IO			(PORTBbits.RB5)
	#define BUTTON1_TRIS		(TRISBbits.TRISB15)	// Ref Sw2
	#define	BUTTON1_IO			(PORTBbits.RB15)

    
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0
#endif  //HARDWARE_PROFILE_PIC24F_STARTER_KIT_H
