/********************************************************************
 FileName:     	HardwareProfile - PIC24FJ64GB004 PIM.h
 Dependencies:  See INCLUDES section
 Processor:     PIC24FJ64GB004
 Hardware:      PIC24FJ64GB004 PIM
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
  2.4b  04/08/2009   Initial support for PIC24FJ64GB004 family
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC24FJ64GB004_PIM_H
#define HARDWARE_PROFILE_PIC24FJ64GB004_PIM_H

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
//    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          0				// per compliance USBCV !

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1 
   
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
    //  initialization functions for the board.  These definitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC24FJ64GB004_PIM
    #define EXPLORER_16
    #define PIC24FJ64GB004_PIM
    #define CLOCK_FREQ 32000000
   	#define GetSystemClock()		(CLOCK_FREQ)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/2)
		#define GetPeripheralClock()	GetInstructionClock()
//   	#define FCY GetInstructionClock()		// per delay


    /** LED ************************************************************/
    #define mInitAllLEDs()      LATA &= 0xffef; TRISA &= 0xffef; LATB &= 0xfff3; TRISB &= 0xfff3; //RA4, RB2 RB3
    
    #define mLED_1              LATBbits.LATB2
    #define mLED_2              LATBbits.LATB3		// uso i due estremi sul pcb! ossia non questo
    #define mLED_3              LATAbits.LATA4
    #define mLED_4              1 //LATAbits.LATA9

    #define mGetLED_1()         (mLED_1)
    #define mGetLED_2()         (mLED_2)
    #define mGetLED_3()         (mLED_3)
    #define mGetLED_4()              

    #define mLED_1_On()         mLED_1=1;
    #define mLED_2_On()         mLED_2=1;
    #define mLED_3_On()         mLED_3=1;
    #define mLED_4_On()          
    
    #define mLED_1_Off()        mLED_1=0;
    #define mLED_2_Off()      	mLED_2=0;
    #define mLED_3_Off()        mLED_3=0;
    #define mLED_4_Off()         
    
    #define mLED_1_Toggle()     __builtin_btg(&LATB,2)			// ^= 0x0004;
    #define mLED_2_Toggle()     __builtin_btg(&LATB,3)			// ^= 0x0008; v.sopra
    #define mLED_3_Toggle()     __builtin_btg(&LATA,4)			// ^= 0x0010;
    #define mLED_4_Toggle()      
    
    /** SWITCH *********************************************************/
    #define mInitSwitch1()      BUTTON0_TRIS=1;
    #define mInitSwitch2()      BUTTON1_TRIS=1;
    #define mInitAllSwitches()  mInitSwitch1();mInitSwitch2();
    #define m_Puls1Bit					BUTTON0_IO
    #define sw2                 BUTTON1_IO


    /** POT ************************************************************/
    #define mInitPOT()  {}
    
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

	#define BUTTON0_TRIS		(TRISBbits.TRISB5)	// Ref Sw1
	#define	BUTTON0_IO			(PORTBbits.RB5)
	#define BUTTON1_TRIS		(TRISBbits.TRISB15)	// Ref Sw2
	#define	BUTTON1_IO			(PORTBbits.RB15)


//Use SPI Module
#define USE_SPI

//SPI Freq Setting
#define SPI_12MHz
//#define SPI_3MHz

//output port definition
#define OUTP LATB			// OCCHIO faccio traslazione!
#define LTDI LATBbits.LATB13		//TDI
#define LTCK LATBbits.LATB9		//TCK
#define LACT mLED_3		//Activity LED

//SPI,PIO output tris definition
#ifdef USE_SPI
#define TSDO TRISBbits.TRISB13	//SPI:TDI
#define TTDI TRISBbits.TRISB13	//PIO:TDI
#define TSCK TRISBbits.TRISB9	//SPI:TCK
#define TTCK TRISBbits.TRISB9	//PIO:TCK
#endif

// in teoria (sullo schema 18F45K50) ci sono anche nCE e nCS... che però qua non vedo 
// CS = RB8 lo uso come TMS; 
// per gli altri per ora uso nCE=RB0 e nCS=RB1 (ossia PGEx, verificare

//input tris definitions for PIO
#define TTDO TRISBbits.TRISB14	//JTAG:TDO
#define TADO TRISBbits.TRISB14	//AS:ASDO

//input port definitions
#define PTDO PORTBbits.RB14		//JTAG:TDO
#define PADO PORTBbits.RB14		//AS:ASDO
    

#endif  //HARDWARE_PROFILE_PIC24FJ64GB004_PIM_H
