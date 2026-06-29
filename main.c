/********************************************************************
 FileName:     main.c
 Dependencies: See INCLUDES section
 Processor:		PIC18, PIC24, and PIC32 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Compiler:  	Microchip C30 (for PIC24)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0   Initial release
  2.1   Updated for simplicity and to use common coding style
	2.1.1	2026 fuck humans updated version
********************************************************************/

#ifndef MAIN_C
#define MAIN_C

/** INCLUDES *******************************************************/
#include "HardwareProfile.h"
#include "usb.h"
//#include "usb_function_hid.h"

#include <timer.h>
#include <ports.h>
#include <outcompare.h>
#include <pps.h>
#include <libpic30.h>

#include <DEE Emulation 16-bit.h>
#include "blastermacros.h"
#include "bitreverse.h"

/** CONFIGURATION **************************************************/
#if defined(__PIC24FJ64GB202__) || defined(__PIC24FJ128GB202__)

// PIC24FJ128GB202 Configuration Bit Settings
// 'C' source line config statements

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
#pragma config DSSWEN = OFF             // DSEN Bit Enable (Deep Sleep operation is always disabled)
#pragma config PLLDIV = DISABLED        // USB 96 MHz PLL Prescaler Select bits (PLL Disabled)
#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (Once set, the IOLOCK bit cannot be cleared)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = OFF            // SOSC Selection bits (Digital (SCLKI) mode)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config BOREN = ON               // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = NONE            // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = OFF           // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config ALTRB6 = APPEND          // Alternate RB6 pin function enable bit (Append the RP6/ASCL1/PMPD6 functions of RB6 to RA1 pin functions)
#pragma config ALTCMPI = CxINC_RB       // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
#pragma config WDTCMX = WDTCLK          // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config IESO = ON                // Internal External Switchover (Enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT enabled in hardware)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF               // General Segment Write Protect (Write to program memory allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (Enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#else

/*	 provare, per USB senza quarzo, http://www.microchip.com/forums/tm.aspx?m=491233&mpage=1&#491523 */
 _CONFIG1(WDTPS_PS16 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
//        _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_NODIV & IESO_ON)		// quarzo 4MHz
  _CONFIG2(POSCMOD_NONE /*POSCMOD_HS*/ & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)		// osc int
//  _CONFIG2(POSCMOD_NONE & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_NODIV & IESO_OFF)		// osc int
	// POSCMOD_NONE sopra serve per poter usare OSCIOFNC ossia ra2-3!

//        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)			SOSC??? secondari osc.. NO RB4!
  _CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
  _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)

#endif



BYTE OutPacket[2][64];
BYTE InPacket[1][64];
extern volatile BYTE CtrlTrfData[8];
#define ctrl_trf_buf CtrlTrfData

BYTE fifo_wp,fifo_rp;		//FIFO Write Pos / Read Pos
BYTE acc0,acc1;			//AccessRAM for FastTemporaly
BYTE recv_byte;			//byte count received
BYTE jtag_byte;			//byte count fot jtag mode
BYTE aser_byte;			//byte count fot active-serial mode
BYTE_VAL _flags;
#define read _flags.bits.b0		//simulteneous reading flag
#define received _flags.bits.b1	//OUT Packet Received flag
#ifdef ENABLE_PPB
  #define PPB _flags.bits.b7	//current ping-pong-buffer
  #define TogglePPB() PPB=!PPB 
#else
  #define PPB 0 
  #define TogglePPB()
#endif
BYTE bufptr;

USB_HANDLE USBOutHandle0;
USB_HANDLE USBOutHandle1;
USB_HANDLE USBInHandle0;

BYTE InFIFO[256];

BOOL blinkStatusValid = TRUE;

BYTE FLAGA;        //GENERAL PURPOSE FLAG

unsigned int DEEaddr1 = 0x0004;			// per emulazione EEprom in Flash
//extern long junk;			//placeholder per flash, ma metto al fondo di altri sorgenti se no shifta tutto... BOH, NO|

WORD CounterL;

volatile BYTE second,second_2,Timer1,Timer100;

const static const char USB_BL_C[]="$Id:USB_BLASTER.C Ver 2.0.1 - 29/6/26";
// was: a day past the Pope and Manuela the rat :)



/** PRIVATE PROTOTYPES *********************************************/
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);
BOOL Switch3IsPressed(void);
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void handle_events(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();


/** VECTOR REMAPPING ***********************************************/
#if defined(__C30__)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions 
         *	line up with the remapped vectors from the bootloader's linker script.
         *  
         *  For more information about how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
//        void __attribute__ ((address(0x1404))) ISRTable(){
//        
//        	asm("reset"); //reset instruction to prevent runaway code
//        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
//        }


//#define BL_ENTRY_BUTTON PORTEbits.RE0 //button 1...
 //USARE RB4 per entrare bootloader, = Buzzer			 su AndroidGSP / SkyUSB24

//If defined, the reset vector pointer and boot mode entry delay
// value will be stored in the device's vector space at addresses 0x100 and 0x102
#define USE_VECTOR_SPACE
//****************************************

//Bootloader Vectors *********************
#ifdef USE_VECTOR_SPACE
	/*
		Store delay timeout value & user reset vector at 0x100 
		(can't be used with bootloader's vector protect mode).
		
		Value of userReset should match reset vector as defined in linker script.
		BLreset space must be defined in linker script.
	*/
	unsigned char timeout  __attribute__ ((space(prog),section(".BLreset"))) = 0x0A;
	unsigned int userReset  __attribute__ ((space(prog),section(".BLreset"))) = 0x1400; 
//cambiato ordine o le metteva a cazzo... 
#else
	/*
		Store delay timeout value & user reset vector at start of user space
	
		Value of userReset should be the start of actual program code since 
		these variables will be stored in the same area.
	*/
	unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
	unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 5 ;
#endif

#endif
#endif

	

void __attribute__ (( interrupt, /*shadow, */ no_auto_psv )) _T2Interrupt(void) {
	static BYTE divider1s;

//	WriteTimer2(0);	// 
  TMR2=0;

	mLED_1_Toggle(); //check timer	 

	divider1s++;
	Timer100++;			// 100mS 
	if(divider1s==5 || divider1s==10) 		// per Timer1, ogni 0.5 sec
		Timer1++;
	if(divider1s==10) {		// per RealTimeClock
		divider1s=0;
		second_2=1;					// flag
		second++;		// 
		}
	

	IFS0bits.T2IF = 0; 			//Clear the Timer2 interrupt status flag
//	T2_Clear_Intr_Status_Bit;			boh non lo trova... ott 2010
	}




void __attribute__ (( interrupt, shadow, no_auto_psv )) _T4Interrupt(void) {

//	WriteTimer4(0);	// 
  TMR4=0;

//	mLED_1_Toggle(); //check timer	 , 100uS


	IFS1bits.T4IF = 0; 			//Clear the Timer4 interrupt status flag
//	T4_Clear_Intr_Status_Bit;			boh non lo trova... ott 2010
	}





/** DECLARATIONS ***************************************************/

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
int main(void) {   

  InitializeSystem();
	RCON=0;		// IMPORTANTE per bootloader!

  #if defined(USB_INTERRUPT)
    USBDeviceAttach();
  #endif


  while(1) {
  	#if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
      USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // frequently (such as once about every 100 microseconds) at any
        				  // time that a SETUP packet might reasonably be expected to
        				  // be sent by the host to your device.  In most cases, the
        				  // USBDeviceTasks() function does not take very long to
        				  // execute (~50 instruction cycles) before it returns.
    #endif
    				  
	
		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
    ProcessIO();        

    if((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl==1)) {
			//Something to do in not connected to host.
			LACT=0;
			}
		else {
			//Check and transmit queued data
			if(!USBHandleBusy(USBInHandle0)) {
				acc0=fifo_used();
				if(62<=acc0) {		//send filled packet to host
					dequeue(InPacket[0]+2,62);
					mUSBTxOnePacket(USBInHandle0,1,InPacket[0],2+62);
					IFS0bits.T2IF=1;	//schedule to send indicator			
//	mLED_1_On();
					} 
				else if(acc0) {			//send non-filled packet to host
					dequeue(InPacket[0]+2,acc0);
					mUSBTxOnePacket(USBInHandle0,1,InPacket[0],2+acc0);
					IFS0bits.T2IF=1;	//schedule sending indicator
	
//	mLED_1_On();
					}
				else if(IFS0bits.T2IF) {	//send packet indicator
					PR2=2500;	//(65536-5536)/(12000/2)=10ms  (clock=16000000, prescaler=64 => 250000Hz
					TMR2=0;
					IFS0bits.T2IF=0;
//	mLED_1_Off();
					mUSBTxOnePacket(USBInHandle0,1,InPacket[0],2);
					}
				}

	    //Check to see if data has arrived.
			if(!recv_byte) {
				if(PPB==0) {	//even packet or no ping-pong
					if(!USBHandleBusy(USBOutHandle0)) {
//	mLED_3_On();
						recv_byte=USBHandleGetLength(USBOutHandle0);
						//p=USBHandleGetAddr(USBOutHandle0);
						bufptr=0;
						received=1;
						}
					}
				else {		//odd packet
					if(!USBHandleBusy(USBOutHandle1)) {
						recv_byte=USBHandleGetLength(USBOutHandle1);
						//p=USBHandleGetAddr(USBOutHandle1);
						bufptr=64;
						received=1;
						}
					}
				}
//			if(fifo_able() < recv_byte) 		// tolto GD 29/6/26 se no non va/si blocca su comando ricevuto
	//			continue;	//FIFO Full check

			if(recv_byte) {
				LACT=0;
				do {
					if(jtag_byte) {
						#ifdef USE_SPI
						ChangeSPI();
						acc0=bitreverse[OutPacket[0][bufptr++]];
						#endif
						if(!read) {
							do {
								#ifdef USE_SPI
								SPI1BUF=acc0;
								acc0=bitreverse[OutPacket[0][bufptr++]];
								SPI_Wait();
	SPI1BUF; // serve??
								#else
								acc0=OutPacket[0][bufptr++];
								JTAG_Write(acc0);
								#endif
								jtag_byte--;
								recv_byte--;
								} while(jtag_byte && recv_byte);
							}
						else {
							do {
								#ifdef USE_SPI
								SPI1BUF=acc0;
								acc0=bitreverse[OutPacket[0][bufptr++]];
								SPI_Wait();
								acc1=bitreverse[SPI1BUF];
								enqueue(acc1);
								#else
								acc0=OutPacket[0][bufptr++];
								JTAG_RW(acc0,acc1);
								enqueue(acc1);
								#endif
								jtag_byte--;
								recv_byte--;
								} while(jtag_byte && recv_byte);
							}
						#ifdef USE_SPI
						bufptr--;
						ChangePIO();
						#endif
						}
					else if(aser_byte) {
						if(!read) {
							#ifdef USE_SPI
							ChangeSPI();
							acc0=bitreverse[OutPacket[0][bufptr++]];
							#endif
							do {
								#ifdef USE_SPI
								SPI1BUF=acc0;
								acc0=bitreverse[OutPacket[0][bufptr++]];
								SPI_Wait();
	SPI1BUF; // serve??
								#else
								acc0=OutPacket[0][bufptr++];
								JTAG_Write(acc0);
								#endif
								aser_byte--;
								recv_byte--;
								} while(aser_byte && recv_byte);
							#ifdef USE_SPI
							bufptr--;
							ChangePIO();
							#endif
							} 
						else {
							do {
								acc0=OutPacket[0][bufptr++];
								ASer_RW(acc0,acc1);
								enqueue(acc1);
								aser_byte--;
								recv_byte--;
								} while(aser_byte && recv_byte);
							}
						}
					else {
						do {
							acc0=OutPacket[0][bufptr++];
							bitcopy(bitmask(acc0,6),read);
							if(bitmask(acc0,7)){		//EnterSerialMode
								LTCK=0;		//bug fix
								if(OUTP & 0x2 /*0x8*/)	//nCS=1:JTAG
									jtag_byte=acc0 & 0x3F;
								else		//nCS=0:ActiveSerial
									aser_byte=acc0 & 0x3F;
								recv_byte--;
								break;
								}
							else {			//BitBangMode
								WORD outp1=0;
								outp1 |= (acc0 & 0b1100) >> 2;		// RC3..2 => RB1..0
								outp1 |= (acc0 & 0b0001) ? 0b0000001000000000 : 0;		// RC0 => RB9
								outp1 |= (acc0 & 0b0010) ? 0b0000000100000000 : 0;		// RC1 => RB8
								outp1 |= (acc0 & 0b10010000) ? 0b0010000000000000 : 0;		// RC4/7 => RB13
								OUTP=outp1;
								if(read) {
									acc1=0;
									if(PADO)
										acc1 |= 0x02;
									if(PTDO) 
										acc1 |= 0x01;
									enqueue(acc1);
									}
								recv_byte--;
								}
							}	while(recv_byte);
						}
					} while(recv_byte);
				}

			if(received && !recv_byte) {
				LACT=1;
				if(PPB==0) {
					mUSBRxOnePacket(USBOutHandle0,2,OutPacket[0],64);
					TogglePPB();
					}
				else{
					mUSBRxOnePacket(USBOutHandle1,2,OutPacket[1],64);
					TogglePPB();
					}
				received=0;
				}
			}

		handle_events();
    }	//end while
	}	//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void) {

#if defined(__PIC24FJ64GB202__) || defined(__PIC24FJ64GB204__) || defined(__PIC24FJ128GB202__) || defined(__PIC24FJ128GB204__)
//          #if defined (USE_INTERNAL_OSC)
            OSCTUN = 0x9000;             //Enable active clock tuning with USB
                   // STLOCK, b11
            // prendo da config ... OSCCON = 0xFC;          //16MHz HFINTOSC with 3x PLL enabled (48MHz operation)
#endif

     
   #if defined(PIC24FJ64GB004_PIM) || defined(PIC24FJ256DA210_DEV_BOARD)
	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }

    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif


//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif



	// LEDs
//	LED0_TRIS = 0;
	TRISA=0b0000000000000000;			// 
	TRISB=0b0000000000000000;			// 

	ODCB =0b0000000000000000;			// ev. open collector per I2C...


// Default all pins to digital
#if defined(__PIC24FJ64GB202__) || defined(__PIC24FJ128GB202__)
  ANSA=0x0000;
  ANSB=0x0000;
#else
	AD1PCFG=0b1111111111111111;		//AN?
#endif


	LATA=0b0000000000000000;			//  
	LATB=0b0000000000000000;			//  




#ifdef USE_SPI
// Unlock Registers
 PPSUnLock;

#if defined(__PIC24FJ64GB202__) || defined(__PIC24FJ128GB202__)
  PPSInput(PPS_SDI1, PPS_RP14);      // pin 25		
	
	// Outputs
  PPSOutput(PPS_SCK1,PPS_RP9);			// pin 18
  //PPSInput(PPS_SCK1,PPS_RP9);			// servirà anche questo??
  PPSOutput(PPS_SDO1,PPS_RP13);					// pin 24

//  PPSOutput(PPS_OC1,PPS_RP4);      // pin 11 prova mmm qua è solo RPI
#else
  PPSInput(PPS_SDI1, PPS_RP14);      // pin 25		
	
	// Outputs
  PPSOutput(PPS_SCK1,PPS_RP9);			// pin 18
  PPSOutput(PPS_SDO1,PPS_RP13);					// pin 24

//  PPSOutput(PPS_RP4, PPS_OC1);      // pin 11 prova
#endif


// Lock Registers
 PPSLock;
#endif


		#if defined(__PIC24F__)
			CLKDIVbits.RCDIV = 0;		// Set 1:1 8MHz FRC postscalar
		#endif




//	OpenTimer2(T2_ON & T2_IDLE_CON & T2_GATE_OFF & T2_PS_1_8 & T2_32BIT_MODE_OFF /* & T2_32BIT_MODE_ON */ & T2_SOURCE_INT,
//		10000);		//
//	OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256  &	T2_SOURCE_INT, 100);

//	ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON);
//	EnableIntT2;


	
//	EnablePullUpCN12;			// pull-up
//	EnableCN12;
//	EnableIntInputChange;


//	OpenOC1(OC_IDLE_CON & OC_TIMER2_SRC /* & CMP_FAULT2_IN_DISABLE */ /* & OC_FAULT1_IN_DISABLE */ & OC_PWM_FAULT_CLEAR & OC_TRIG_CLEAR_SYNC & OC_CONTINUE_PULSE,
//		OC_FAULT_MODE_PWM_CYCLE & OC_PWM_FAULT_OUT_HIGH & OC_FAULT_PIN_UNCHANGE & OC_OUT_NOT_INVERT & OC_CASCADE_DISABLE /* & OC_SYNC_ENABLE */ & OC_UNTRIGGER_TIMER & OC_DIRN_TRIS & OC_SYNC_TRIG_IN_DISABLE,
//		0,0); FARE!



  UserInit();
    
  USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware variables to known states.

//  DataEEInit();
  dataEEFlags.val = 0;
  Nop();
  Nop();


	}	//end InitializeSystem




/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/
void UserInit(void) {
	BYTE i;

	ClrWdt();


	__delay_ms(25);		// per EEprom ecc, PRIMA DI IRQ!
	ClrWdt();
	__delay_ms(25);		// (occhio a watchdog!)
	ClrWdt();
	__delay_ms(25);
	ClrWdt();
	__delay_ms(25);
	ClrWdt();



	//EnablePullUpCN1;			// pull-up , non lo trova, ott 2010...
	CNPU1bits.CN11PUE = 1;		//puls2
	CNPU2bits.CN27PUE = 1;		//puls.


//	CNPU2bits.CN23PUE=1;			// INT
	//CNPU2bits.CN12PUE=1;			// MISO? mettere?


	//IO Initialize
//	ANSEL  = 0;
//	ANSELH = 0;
//	SLRCON = 0;

	//Port direction setup
	TRISA=0b0000000000000000;
	TRISB=0b0000000000000000;
	TTDO=1;
	TADO=1;

  //Initialize all of the LED pins
  mInitAllLEDs();
  
  //Initialize all of the push buttons
  mInitAllSwitches();
  
	//Initial value setup
	OUTP=0b0110001100000000;		// TMS,nCE,TDI,nCS

	//Peripheral setup
	T2CON=0b1000000000100000;		//On,16bit,Fcy/64
	IEC0bits.T2IE=0;	//Polling

//    #define PROPER_SPICON1  (0x0013 | 0x0120)   /* 1:1 primary prescaler, 4:1 secondary prescale, CKE=1, MASTER mode */
//    #define PROPER_SPICON1  (0x21)      /* SSPEN bit is set, SPI in master mode, FOSC/16, IDLE state is low level */
// 4MHz pare, 21.5.17

//   SPI1CON1 = PROPER_SPICON1; // See PROPER_SPICON1 definition above


	#ifdef USE_SPI
	SPI1STAT=0b0000000000000000;		//
	#ifdef SPI_3MHz
	SPI1CON1=0b0000000100101111;		//SMP=0,CKE=1; Master, 8bit; Fspi=3MHz  IN EFFETTI 3.2  16/5
	SPI1CON2=0b0000000000000000;
	#endif
	#ifdef SPI_12MHz
	SPI1CON1=0b0000000100111011;		//SMP=0,CKE=1; Master, 8bit; Fspi=12MHz  IN EFFETTI 8   16/2
	SPI1CON2=0b0000000000000000;
	#endif
	ChangePIO();
	#endif	

	//Program Initialize
	InPacket[0][0]=0x31;
	InPacket[0][1]=0x60;
	eeprom_init();



	}	//end UserInit




/********************************************************************
 * Function:        void ProcessIO(void)
 *	
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void) {  
	int i; 
    
	//Blink the LEDs according to the USB device status
  BlinkUSBStatus();

  // User Application USB tasks
  if((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl==1)) 
		return;



	}	//end ProcessIO


void handle_events(void) {
	static WORD divider=0,divider2=0;
	BYTE n,i;

	ClrWdt();
	divider++;


	if(!(divider % 7000)) {		// ???' 40-50mS
//		rowState=0;

		divider2++;



		if(!m_Puls1Bit) {
	
			}
		}



	}





// ----------------------------------------------------------------------------------------


/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs 
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void) {
  static WORD led_count=0;
  
  if(led_count == 0)
		led_count = 20000U;
  led_count--;


  if(led_count == 0) {
    if(USBSuspendControl == 1) {
			led_count = 40000U;
//	    mLED_1_Toggle();
//	    mLED_2_Off();
			}
  	else {
     if(USBDeviceState == CONFIGURED_STATE) {
   	    mLED_2_Toggle();
//	    	mLED_1_Off();
				}
			else {

   	    mLED_2_On();



//	    	mLED_1_Off();
				}
			}
		}


	}		//end BlinkUSBStatus





// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.




// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void) {
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

  #if defined(__C30__)
    USBSleepOnSuspend();
  #endif
	}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void) {

    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
	}
#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void) {
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
	}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void) {
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
	}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void) {
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
	}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
extern volatile CTRL_TRF_SETUP SetupPkt;
void USBCBCheckOtherReq(void) {

	//FT245 emulation
	BYTE index;

	if(SetupPkt.RequestType==2) {	//Vendor request
		if(SetupPkt.DataDir==0) {	//0utput
			//Responce by sending zero-length packet
			//I don't know if this way is right, but working :)
			USBEP0SendRAMPtr(ctrl_trf_buf,0,USB_EP0_INCLUDE_ZERO);
			return;
			}
		if(SetupPkt.bRequest==0x90) {
			index=(SetupPkt.wIndex << 1) & 0x7E;
			ctrl_trf_buf[0]=eeprom_read(index);
			ctrl_trf_buf[1]=eeprom_read(index+1);
			}
		else {
			ctrl_trf_buf[0]=0x36;
			ctrl_trf_buf[1]=0x83;
			}
		USBEP0SendRAMPtr(ctrl_trf_buf,2,USB_EP0_INCLUDE_ZERO);
		}
	}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void) {

  // Must claim session ownership if supporting this request
	}	//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void) {

  USBEnableEndpoint(1,USB_IN_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
  USBEnableEndpoint(2,USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
  //initialize the variable holding the handle for the last transmission
	USBOutHandle0=0;
	USBOutHandle1=0;
	USBInHandle0=0;
	fifo_wp=0;
	fifo_rp=0;
	recv_byte=0;
	jtag_byte=0;
	aser_byte=0;
	_flags.Val=0;
	//(TODO: Buffer pointer reset
	bufptr=0;
	}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function should only be called when:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void) {
    static WORD delay_count;
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus()) {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended()) {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do {
              delay_count--;
            	} while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do {
              delay_count--;
            	} while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
	}


                                                  // When receive data is less than or equal to 8 byte (USB_EP0_BUFF_SIZE),
                                                  // CtrlTrfData[] on the stack is available for the receive buffer.
                                                  // Otherwise, place a receive buffer in global scope (or static in this file).
                                                  // This buffer is not necessary to place on USB RAM area.

void UserSetReport_Callback_0(void);            // Prototype for callback function

#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void){}
#endif


/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size) {

    switch(event) {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).
            break;
        default:
            break;
	    }      
  return TRUE; 
	}



//for debug use - measure cycle counts
void test(){
	BYTE *p;

	bufptr=64;
	fifo_wp=0;
	fifo_rp=0;
	acc0=0x53;
	acc1=bitreverse[SPI1BUF];	//10cy
	enqueue(acc0);		//9cy
	enqueue(acc1);		//9cy
	JTAG_Write(acc0);		//56cy
	JTAG_RW(acc0,acc1);	//73cy
	ASer_RW(acc0,acc1);	//73cy
	dequeue(InPacket[0]+2,fifo_used());	// 116cy@2byte
	fifo_wp=0; for(acc0=0;1;acc0++) { enqueue(acc0); if(acc0==255) break; }
	fifo_wp=100; fifo_rp=190;
	dequeue(InPacket[0]+2,62);	//818cy@62byte
	dequeue(InPacket[0]+2,62);	//890cy@62byte
	acc1=bitreverse[OutPacket[0][bufptr++]];	//17cy
	enqueue(bitreverse[SPI1BUF]);	//20cy
	Nop();
	}


/** EOF main.c *************************************************/
#endif

