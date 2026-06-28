#if defined(__PIC24FV32KA301__) || defined(__PIC24FV32KA302__)
#include <p24fxxxx.h>
#else
#include <xc.h>
#endif


 /******************************************************************************
 *
 *                  TIMER PERIPHERAL LIBRARY HEADER FILE
 *
 ******************************************************************************
 * FileName:        timer.h
 * Dependencies:    See include below
 * Processor:       PIC24
 * Compiler:        MPLAB C30
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 *****************************************************************************/

/*Registers Defaults*/
#define TMR1_VALUE          0x0000
#define PR1_VALUE           0xFFFF
#define T1CON_VALUE         0x0000


/* Timer1 Control Register (T1CON) Bit Defines */
#define T1_ON               0xffff  /* Timer1 ON */
#define T1_OFF              0x7fff  /* Timer1 OFF */

#define T1_IDLE_CON         0xdfff /* operate during sleep */
#define T1_IDLE_STOP        0xffff /* stop operation during sleep */

#if defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2)
#define T1_CLK_LPRC         0xfeff /* Timer extended clock source using LPRC oscillator */
#define T1_CLK_EXT        	0xfdff /* Timer extended clock source using external clock input */
#define T1_CLK_SOSC       	0xfcff /* Timer extended clock source using Secondary oscillator */
#endif

#define T1_GATE_ON          0xffff /* Timer Gate time accumulation enabled */
#define T1_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T1_PS_1_1           0xffcf /* Prescaler 1:1 */
#define T1_PS_1_8           0xffdf /* Prescaler 1:8 */
#define T1_PS_1_64          0xffef /* Prescaler 1:64 */
#define T1_PS_1_256         0xffff /* Prescaler 1:256 */

#define T1_SYNC_EXT_ON      0xffff /* Synch external clk input */
#define T1_SYNC_EXT_OFF     0xfffb /* Do not synch external clk input */

#define T1_SOURCE_EXT       0xffff /* External clock source */
#define T1_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T1_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T1_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T1_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T1_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T1_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T1_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T1_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T1_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T1_INT_ON           0xffff /* Interrupt Enable */
#define T1_INT_OFF          0xfff7 /* Interrupt Disable */


/**********************************************************************
Macro       : EnableIntT1( )

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT1                    (IEC0bits.T1IE = 1)

/**********************************************************************
Macro       : DisableIntT1

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT1                   (IEC0bits.T1IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT1(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT1(priority)     (IPC0bits.T1IP = priority)

/*******************************************************************
Macro       : T1_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T1_Clear_Intr_Status_Bit     (IFS0bits.T1IF = 0)


/* Timer1 Function Prototypes */
void __attribute__ ((section(".libperi"))) OpenTimer1( unsigned int config, unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer1(void);

unsigned int __attribute__ ((section (".libperi"))) ReadTimer1(void);

void __attribute__ ((section (".libperi"))) WriteTimer1( unsigned int timer);

void __attribute__ ((section (".libperi"))) ConfigIntTimer1(unsigned int config);



/*Registers Defaults*/
#define TMR2_VALUE          0x0000
#define PR2_VALUE           0xFFFF
#define T2CON_VALUE         0x0000


/* Timer2 Control Register (T2CON) Bit Defines */
#define T2_ON               0xffff /* Timer2 ON */
#define T2_OFF              0x7fff /* Timer2 OFF */

#define T2_IDLE_CON         0xdfff /* operate during sleep */
#define T2_IDLE_STOP        0xffff /* stop operation during sleep */

#define T2_GATE_ON          0xffff /* Timer2 Gate time accumulation enabled  */
#define T2_GATE_OFF         0xffbf /* Timer2 Gate time accumulation disabled */

#define T2_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T2_PS_1_8           0xffdf /*Prescaler 1:8   */
#define T2_PS_1_64          0xffef /*Prescaler 1:64  */
#define T2_PS_1_256         0xffff  /*Prescaler 1:256 */

/* Timer 2 and Timer 3 form a 32 bit Timer */
#define T2_32BIT_MODE_ON    0xffff      
#define T2_32BIT_MODE_OFF   0xfff7      

#define T2_SOURCE_EXT       0xffff /* External clock source */
#define T2_SOURCE_INT       0xfffd /* Internal clock source */

#define T2_POST_1_1    0x87  //Timer2 Postscaler 1:1
#define T2_POST_1_2    0x8f  //Timer2 Postscaler 1:2
#define T2_POST_1_3    0x97  //Timer2 Postscaler 1:3
#define T2_POST_1_4    0x9f  //Timer2 Postscaler 1:4
#define T2_POST_1_5    0xa7  //Timer2 Postscaler 1:5
#define T2_POST_1_6    0xaf  //Timer2 Postscaler 1:6
#define T2_POST_1_7    0xb7  //Timer2 Postscaler 1:7
#define T2_POST_1_8    0xbf  //Timer2 Postscaler 1:8
#define T2_POST_1_9    0xc7  //Timer2 Postscaler 1:9
#define T2_POST_1_10   0xcf  //Timer2 Postscaler 1:10
#define T2_POST_1_11   0xd7  //Timer2 Postscaler 1:11
#define T2_POST_1_12   0xdf  //Timer2 Postscaler 1:12
#define T2_POST_1_13   0xe7  //Timer2 Postscaler 1:13
#define T2_POST_1_14   0xef //Timer2 Postscaler 1:14
#define T2_POST_1_15   0xf7  //Timer2 Postscaler 1:15
#define T2_POST_1_16   0xff  //Timer2 Postscaler 1:16

/* defines for Timer Interrupts */
#define T2_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T2_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T2_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T2_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T2_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T2_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T2_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T2_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T2_INT_ON           0xffff /* Interrupt Enable */
#define T2_INT_OFF          0xfff7 /* Interrupt Disable */


/**********************************************************************
Macro       : EnableIntT2

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT2                    (IEC0bits.T2IE = 1)

/**********************************************************************
Macro       : DisableIntT2

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT2                  (IEC0bits.T2IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT2(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT2(priority)     (IPC1bits.T2IP = priority)

/*******************************************************************
Macro       : T2_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T2_Clear_Intr_Status_Bit     (IFS0bits.T2IF = 0)


/* Timer2 Function Prototypes */

/* OpenTimer2 */
void __attribute__ ((section(".libperi"))) OpenTimer2(unsigned int config, unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer2(void);

unsigned int __attribute__ ((section (".libperi"))) ReadTimer2(void);

void __attribute__ ((section (".libperi"))) WriteTimer2( unsigned int timer);

void __attribute__ ((section (".libperi"))) ConfigIntTimer2(unsigned int config);



#define TMR5_VALUE          0x0000
#define PR5_VALUE           0xFFFF
#define T5CON_VALUE         0x0000

#define T5_ON               0xffff /* Timer5 ON */
#define T5_OFF              0x7fff /* Timer5 OFF */

#define T5_IDLE_CON         0xdfff /* operate during sleep */
#define T5_IDLE_STOP        0xffff /* stop operation during sleep */

#define T5_GATE_ON          0xffff /* Timer Gate time accumulation enabled */
#define T5_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T5_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T5_PS_1_8           0xffdf /* Prescaler 1:8   */
#define T5_PS_1_64          0xffef /* Prescaler 1:64  */
#define T5_PS_1_256         0xffff /* Prescaler 1:256 */

#define T5_SOURCE_EXT       0xffff/* External clock source */
#define T5_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T5_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T5_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T5_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T5_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T5_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T5_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T5_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T5_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T5_INT_ON           0xffff /* Interrupt Enable */
#define T5_INT_OFF          0xfff7  /* Interrupt Disable */


/**********************************************************************
Macro       : EnableIntT5

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT5                    (IEC1bits.T5IE = 1)

/**********************************************************************
Macro       : DisableIntT5

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT5                  (IEC1bits.T5IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT5(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT5(priority)     (IPC7bits.T5IP = priority)

/*******************************************************************
Macro       : T5_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T5_Clear_Intr_Status_Bit     (IFS1bits.T5IF = 0)

/* Timer5 Function Declarations */

void  __attribute__ ((section(".libperi"))) OpenTimer5(unsigned int config, unsigned int period);

void  __attribute__ ((section (".libperi"))) CloseTimer5(void);

unsigned int  __attribute__ ((section (".libperi"))) ReadTimer5(void);

void  __attribute__ ((section (".libperi"))) WriteTimer5(unsigned int timer);

void  __attribute__ ((section (".libperi"))) ConfigIntTimer5(unsigned int config);





#define AD1CON1_VALUE                0x0000
#define AD1CON2_VALUE                0x0000
#define AD1CON3_VALUE                0x0000
#define AD1CON4_VALUE                0x0000
#define AD1CON5_VALUE                0x0000
#define AD1CHS123_VALUE              0x0000
#define AD1CH0_VALUE                 0x0000
#define AD1CHSS_VALUE                0x0000
#define AD1CSSL_VALUE                0x0000
#define AD1PCFGH_VALUE               0x0000
#define AD1PCFGL_VALUE               0x0000


/***** AD1CON1 register definition ****/
#define ADC_MODULE_ON               0xFFFF /*A/D Converter on */
#define ADC_MODULE_OFF              0x7FFF /* A/D Converter off */

#define ADC_IDLE_CONTINUE           0xDFFF /* A/D Operate in Idle mode */
#define ADC_IDLE_STOP               0xFFFF /* A/D Stop in Idle mode */

#define ADC_DMA_EXT_BUF_MODE     	0xFFFF /*A/D Extended DMA buffer mode is enabled*/
#define ADC_DMA_PIA_MODE          	0xEFFF /*A/D Peripheral Indirect Addressing mode is disabled*/ 

#define ADC_DMA_ENABLE              0xFFFF /*DMA operation of A/D is enabled*/
#define ADC_DMA_DISABLE             0xF7FF /*DMA operation of A/D is disabled*/

#define ADC_12BIT_MODE              0xFFFF /*12-bit A/D operation*/
#define ADC_10BIT_MODE              0xFFBF /*10-bit A/D operation*/

#define ADC_FORMAT_SIGN_FRACT       0xFFFF /* A/D data format signed fractional */
#define ADC_FORMAT_FRACT            0xFEFF /* A/D data format fractional */
#define ADC_FORMAT_SIGN_INT         0xFDFF /* A/D data format signed integer */
#define ADC_FORMAT_INTG             0xFCFF /* A/D data format integer */

#define ADC_CLK_AUTO              	0xFF7F /*The SAMP bit is cleared after SAMC<4:0> number of TAD clocks following 
                                           the SAMP bit being set.No Extended Sample Time is present.*/										   

#define ADC_CLK_CTMU                0xFF4F /* CTMU event ends sampling and starts conversion */

#define ADC_CLK_TMR5                0xFF7F /* Timer5 compare ends sampling and starts conversion */

#define ADC_CLK_TMR3                0xFF5F /* Timer3 compare ends sampling and starts conversion */
#define ADC_CLK_INT0                0xFF3F /* Active transition on INT0 ends sampling and starts conversion */
#define ADC_CLK_MANUAL              0xFF1F /* Clearing sample (SAMP) bit ends sampling and starts conversion */

#define ADC_CLK_TMR1                0xFF5F /* Timer1 compare ends sampling and starts conversion */
#define ADC_CLK_CLEAR           	0xFF0F /*The SAMP bit must be cleared by software*/

#define ADC_TRIG_INPUT15           0xFFFF /*The SAMP bit is cleared by a rising edge of trigger input 15*/
#define ADC_TRIG_INPUT14           0xFFEF /*The SAMP bit is cleared by a rising edge of trigger input 14*/
#define ADC_TRIG_INPUT13           0xFFDF /*The SAMP bit is cleared by a rising edge of trigger input 13*/
#define ADC_TRIG_INPUT12           0xFFCF /*The SAMP bit is cleared by a rising edge of trigger input 12*/
#define ADC_TRIG_INPUT11           0xFFBF /*The SAMP bit is cleared by a rising edge of trigger input 11*/
#define ADC_TRIG_INPUT10           0xFFAF /*The SAMP bit is cleared by a rising edge of trigger input 10*/
#define ADC_TRIG_INPUT9            0xFF9F /*The SAMP bit is cleared by a rising edge of trigger input 9*/
#define ADC_TRIG_INPUT8            0xFF8F /*The SAMP bit is cleared by a rising edge of trigger input 8*/
#define ADC_TRIG_AUTO              0xFF7F /*The SAMP bit is cleared after SAMC<4:0> number of TAD clocks following 
                                           the SAMP bit being set.No Extended Sample Time is present.*/										   
#define ADC_TRIG_INPUT6            0xFF6F /*The SAMP bit is cleared by a rising edge of trigger input 6*/
#define ADC_TRIG_INPUT5            0xFF5F /*The SAMP bit is cleared by a rising edge of trigger input 5*/
#define ADC_TRIG_INPUT4            0xFF4F /*The SAMP bit is cleared by a rising edge of trigger input 4*/
#define ADC_TRIG_INPUT3            0xFF3F /*The SAMP bit is cleared by a rising edge of trigger input 3*/
#define ADC_TRIG_INPUT2            0xFF2F /*The SAMP bit is cleared by a rising edge of trigger input 2*/
#define ADC_TRIG_INPUT1            0xFF1F /*The SAMP bit is cleared by a rising edge of trigger input 1*/
#define ADC_TRIG_MANUAL            0xFF0F /*The SAMP bit must be cleared by software*/

#define ADC_SAMPLE_SIMULTANEOUS     0xFFFF /* Samples CH0,CH1 simultaneously or CH0, CH1,CH2,CH3 simultaneously*/
#define ADC_SAMPLE_INDIVIDUAL       0xFFF7 /* Samples multiple channels individually in sequence*/

#define ADC_AUTO_SAMPLING_ON        0xFFFF /* Sampling begins immediately after last conversion */
#define ADC_AUTO_SAMPLING_OFF       0xFFFB /* Sampling begins when SAMP bit is set */

#define ADC_SAMP_ON                 0xFFFF /* sample / hold amplifiers are sampling */
#define ADC_SAMP_OFF                0xFFFD /* sample / hold amplifiers are holding */

/***** AD1CON2 control register definition ****/
#define ADC_VREF_AVDD_AVSS          0x0FFF /* A/D Voltage reference configuration Vref+ is AVdd and Vref- is AVss */
#define ADC_VREF_EXT_AVSS           0x2FFF /* A/D Voltage reference configuration Vref+ external and Vref- is AVss */
#define ADC_VREF_AVDD_EXT           0x4FFF /* A/D Voltage reference configuration Vref+ AVdd and Vref- external */
#define ADC_VREF_EXT_EXT            0x6FFF /* A/D Voltage reference configuration both Vref+ and Vref- are external */

#define ADC_POS_VREF_INT_VRH2      0xFFFF /*Converter Positive Voltage Reference - Internal VRH2 */
#define ADC_POS_VREF_INT_VRH1      0xBFFF /*Converter Positive Voltage Reference - Internal VRH1 */

#define ADC_POS_VREF_EXT           0x7FFF /*Converter Positive Voltage Reference - External VREF+*/
#define ADC_POS_VREF_AVDD          0x0FFF /*Converter Positive Voltage Reference - AVDD*/

#define ADC_NEG_VREF_EXT           0xFFFF /*Converter Negative Voltage Reference - External VREF- */
#define ADC_NEG_VREF_AVSS          0xDFFF /*Converter Negative Voltage Reference - AVSS */

#define ADC_BUF_REG_ENABLE          0xFFFF /* Conversion result is loaded into buffer location determined by the converted channel*/
#define ADC_BUF_REG_DISABLE         0xF7FF /* A/D result buffer is treated as a FIFO */

#define ADC_OFFSET_CAL_ON           0xFFFF /* Converts to get the Offset calibration value */
#define ADC_OFFSET_CAL_OFF          0xEFFF /* Coverts to get the actual input value */

#define ADC_SCAN_ON                 0xFFFF /* A/D Scan Input Selections for CH0 during SAMPLE A */
#define ADC_SCAN_OFF                0xFBFF /* A/D Do notScan Input Selections for CH0+ during SAMPLE A */

#define ADC_CONVERT_CH_0123         0xFFFF /*Converts CH0,CH1,CH2 and CH3*/
#define ADC_CONVERT_CH_01           0xFDFF /*Converts CH0 and CH1*/
#define ADC_CONVERT_CH0             0xFCFF /*Converts CH0 */

#define ADC_INTR_EACH_CONV          0xFF83 /* Interrupts at the completion of conversion of each sample */
#define ADC_INTR_2_CONV             0xFF87 /* Interrupts at the completion of conversion of 2 samples */
#define ADC_INTR_3_CONV             0xFF8B /* Interrupts at the completion of conversion of 3 samples */
#define ADC_INTR_4_CONV             0xFF8F /* Interrupts at the completion of conversion of 4 samples */
#define ADC_INTR_5_CONV             0xFF93 /* Interrupts at the completion of conversion of 5 samples */
#define ADC_INTR_6_CONV             0xFF97 /* Interrupts at the completion of conversion of 6 samples */
#define ADC_INTR_7_CONV             0xFF9B /* Interrupts at the completion of conversion of 7 samples */
#define ADC_INTR_8_CONV             0xFF9F /* Interrupts at the completion of conversion of 8 samples */
#define ADC_INTR_9_CONV             0xFFA3 /* Interrupts at the completion of conversion of 9 samples */
#define ADC_INTR_10_CONV            0xFFA7 /* Interrupts at the completion of conversion of 10 samples */
#define ADC_INTR_11_CONV            0xFFAB /* Interrupts at the completion of conversion of 11 samples */
#define ADC_INTR_12_CONV            0xFFAF /* Interrupts at the completion of conversion of 12 samples */
#define ADC_INTR_13_CONV            0xFFB3 /* Interrupts at the completion of conversion of 13 samples */
#define ADC_INTR_14_CONV            0xFFB7 /* Interrupts at the completion of conversion of 14 samples */
#define ADC_INTR_15_CONV            0xFFBB /* Interrupts at the completion of conversion of 15 samples */
#define ADC_INTR_16_CONV            0xFFBF /* Interrupts at the completion of conversion of 16 samples */

#define ADC_INTR_17_CONV            0xFFC3 /* Interrupts at the completion of conversion of 17 samples */
#define ADC_INTR_18_CONV            0xFFC7 /* Interrupts at the completion of conversion of 18 samples */
#define ADC_INTR_19_CONV            0xFFCB /* Interrupts at the completion of conversion of 19 samples */
#define ADC_INTR_20_CONV            0xFFCF /* Interrupts at the completion of conversion of 20 samples */
#define ADC_INTR_21_CONV            0xFFD3 /* Interrupts at the completion of conversion of 21 samples */
#define ADC_INTR_22_CONV            0xFFD7 /* Interrupts at the completion of conversion of 22 samples */
#define ADC_INTR_23_CONV            0xFFDB /* Interrupts at the completion of conversion of 23 samples */
#define ADC_INTR_24_CONV            0xFFDF /* Interrupts at the completion of conversion of 24 samples */
#define ADC_INTR_25_CONV            0xFFE3 /* Interrupts at the completion of conversion of 25 samples */
#define ADC_INTR_26_CONV            0xFFE7 /* Interrupts at the completion of conversion of 26 samples */
#define ADC_INTR_27_CONV            0xFFEB /* Interrupts at the completion of conversion of 27 samples */
#define ADC_INTR_28_CONV            0xFFEF /* Interrupts at the completion of conversion of 28 samples */
#define ADC_INTR_29_CONV            0xFFF3 /* Interrupts at the completion of conversion of 29 samples */
#define ADC_INTR_30_CONV            0xFFF7 /* Interrupts at the completion of conversion of 30 samples */
#define ADC_INTR_31_CONV            0xFFFB /* Interrupts at the completion of conversion of 31 samples */
#define ADC_INTR_32_CONV            0xFFFF /* Interrupts at the completion of conversion of 32 samples */

#define ADC_ALT_BUF_ON              0xFFFF /* Buffer configured as 2 8-word buffers */
#define ADC_ALT_BUF_OFF             0xFFFD /* Buffer configured as 1 16-word buffer */

#define ADC_ALT_INPUT_ON            0xFFFF /* alternate between MUXA and MUXB */
#define ADC_ALT_INPUT_OFF           0xFFFE /* use MUXA only */

/**** AD1CON3 register definition ****/
#define ADC_CONV_CLK_INTERNAL_RC    0xFFFF /* A/D Conversion Clock Source internal RC Clock */
#define ADC_CONV_CLK_SYSTEM         0x7FFF /* A/D Conversion Clock Source Clock derived from system clock */

#define ADC_EXT_SAMP_ON             0xFFFF /*A/D is still sampling after SAMP = 0*/
#define ADC_EXT_SAMP_OFF            0xBFFF /*A/D is finished sampling*/

#define ADC_CHARGE_PUMP_ENABLE      0xFFFF /*Charge pump for switches is enabled*/
#define ADC_CHARGE_PUMP_DISABLE     0xDFFF /*Charge pump for switches is enabled*/

#define ADC_SAMPLE_TIME_0           0xE0FF /* A/D Auto Sample Time 0 Tad */
#define ADC_SAMPLE_TIME_1           0xE1FF /* A/D Auto Sample Time 1 Tad */
#define ADC_SAMPLE_TIME_2           0xE2FF /* A/D Auto Sample Time 2 Tad */
#define ADC_SAMPLE_TIME_3           0xE3FF /* A/D Auto Sample Time 3 Tad */
#define ADC_SAMPLE_TIME_4           0xE4FF /* A/D Auto Sample Time 4 Tad */
#define ADC_SAMPLE_TIME_5           0xE5FF /* A/D Auto Sample Time 5 Tad */
#define ADC_SAMPLE_TIME_6           0xE6FF /* A/D Auto Sample Time 6 Tad */
#define ADC_SAMPLE_TIME_7           0xE7FF /* A/D Auto Sample Time 7 Tad */
#define ADC_SAMPLE_TIME_8           0xE8FF /* A/D Auto Sample Time 8 Tad */
#define ADC_SAMPLE_TIME_9           0xE9FF /* A/D Auto Sample Time 9 Tad */
#define ADC_SAMPLE_TIME_10          0xEAFF /* A/D Auto Sample Time 10 Tad */
#define ADC_SAMPLE_TIME_11          0xEBFF /* A/D Auto Sample Time 11 Tad */
#define ADC_SAMPLE_TIME_12          0xECFF /* A/D Auto Sample Time 12 Tad */
#define ADC_SAMPLE_TIME_13          0xEDFF /* A/D Auto Sample Time 13 Tad */
#define ADC_SAMPLE_TIME_14          0xEEFF /* A/D Auto Sample Time 14 Tad */
#define ADC_SAMPLE_TIME_15          0xEFFF /* A/D Auto Sample Time 15 Tad */
#define ADC_SAMPLE_TIME_16          0xF0FF /* A/D Auto Sample Time 16 Tad */
#define ADC_SAMPLE_TIME_17          0xF1FF /* A/D Auto Sample Time 17 Tad */
#define ADC_SAMPLE_TIME_18          0xF2FF /* A/D Auto Sample Time 18 Tad */
#define ADC_SAMPLE_TIME_19          0xF3FF /* A/D Auto Sample Time 19 Tad */
#define ADC_SAMPLE_TIME_20          0xF4FF /* A/D Auto Sample Time 20 Tad */
#define ADC_SAMPLE_TIME_21          0xF5FF /* A/D Auto Sample Time 21 Tad */
#define ADC_SAMPLE_TIME_22          0xF6FF /* A/D Auto Sample Time 22 Tad */
#define ADC_SAMPLE_TIME_23          0xF7FF /* A/D Auto Sample Time 23 Tad */
#define ADC_SAMPLE_TIME_24          0xF8FF /* A/D Auto Sample Time 24 Tad */
#define ADC_SAMPLE_TIME_25          0xF9FF /* A/D Auto Sample Time 25 Tad */
#define ADC_SAMPLE_TIME_26          0xFAFF /* A/D Auto Sample Time 26 Tad */
#define ADC_SAMPLE_TIME_27          0xFBFF /* A/D Auto Sample Time 27 Tad */
#define ADC_SAMPLE_TIME_28          0xFCFF /* A/D Auto Sample Time 28 Tad */
#define ADC_SAMPLE_TIME_29          0xFDFF /* A/D Auto Sample Time 29 Tad */
#define ADC_SAMPLE_TIME_30          0xFEFF /* A/D Auto Sample Time 30 Tad */
#define ADC_SAMPLE_TIME_31          0xFFFF /* A/D Auto Sample Time 31 Tad */

#define ADC_CONV_CLK_1Tcy          0xFF00 /* A/D Conversion Clock is Tcy */
#define ADC_CONV_CLK_2Tcy          0xFF01 /* A/D Conversion Clock is 2*Tcy */
#define ADC_CONV_CLK_3Tcy          0xFF02 /* A/D Conversion Clock is 3*Tcy */
#define ADC_CONV_CLK_4Tcy          0xFF03 /* A/D Conversion Clock is 4*Tcy */
#define ADC_CONV_CLK_5Tcy          0xFF04 /* A/D Conversion Clock is 5*Tcy */
#define ADC_CONV_CLK_6Tcy          0xFF05 /* A/D Conversion Clock is 6*Tcy */
#define ADC_CONV_CLK_7Tcy          0xFF06 /* A/D Conversion Clock is 7*Tcy */
#define ADC_CONV_CLK_8Tcy          0xFF07 /* A/D Conversion Clock is 8*Tcy */
#define ADC_CONV_CLK_9Tcy          0xFF08 /* A/D Conversion Clock is 9*Tcy */
#define ADC_CONV_CLK_10Tcy         0xFF09 /* A/D Conversion Clock is 10*Tcy */
#define ADC_CONV_CLK_11Tcy         0xFF0A /* A/D Conversion Clock is 11*Tcy */
#define ADC_CONV_CLK_12Tcy         0xFF0B /* A/D Conversion Clock is 12*Tcy */
#define ADC_CONV_CLK_13Tcy         0xFF0C /* A/D Conversion Clock is 13*Tcy */
#define ADC_CONV_CLK_14Tcy         0xFF0D /* A/D Conversion Clock is 14*Tcy */
#define ADC_CONV_CLK_15Tcy         0xFF0E /* A/D Conversion Clock is 15*Tcy */
#define ADC_CONV_CLK_16Tcy         0xFF0F /* A/D Conversion Clock is 16*Tcy */
#define ADC_CONV_CLK_17Tcy         0xFF10 /* A/D Conversion Clock is 17*Tcy */
#define ADC_CONV_CLK_18Tcy         0xFF11 /* A/D Conversion Clock is 18*Tcy */
#define ADC_CONV_CLK_19Tcy         0xFF12 /* A/D Conversion Clock is 19*Tcy */
#define ADC_CONV_CLK_20Tcy         0xFF13 /* A/D Conversion Clock is 20*Tcy */
#define ADC_CONV_CLK_21Tcy         0xFF14 /* A/D Conversion Clock is 21*Tcy */
#define ADC_CONV_CLK_22Tcy         0xFF15 /* A/D Conversion Clock is 22*Tcy */
#define ADC_CONV_CLK_23Tcy         0xFF16 /* A/D Conversion Clock is 23*Tcy */
#define ADC_CONV_CLK_24Tcy         0xFF17 /* A/D Conversion Clock is 24*Tcy */
#define ADC_CONV_CLK_25Tcy         0xFF18 /* A/D Conversion Clock is 25*Tcy */
#define ADC_CONV_CLK_26Tcy         0xFF19 /* A/D Conversion Clock is 26*Tcy */
#define ADC_CONV_CLK_27Tcy         0xFF1A /* A/D Conversion Clock is 27*Tcy */
#define ADC_CONV_CLK_28Tcy         0xFF1B /* A/D Conversion Clock is 28*Tcy */
#define ADC_CONV_CLK_29Tcy         0xFF1C /* A/D Conversion Clock is 29*Tcy */
#define ADC_CONV_CLK_30Tcy         0xFF1D /* A/D Conversion Clock is 40*Tcy */
#define ADC_CONV_CLK_31Tcy         0xFF1E /* A/D Conversion Clock is 31*Tcy */
#define ADC_CONV_CLK_32Tcy         0xFF1F /* A/D Conversion Clock is 32*Tcy */
#define ADC_CONV_CLK_33Tcy         0xFF20 /* A/D Conversion Clock is 33*Tcy */
#define ADC_CONV_CLK_34Tcy         0xFF21 /* A/D Conversion Clock is 34*Tcy */
#define ADC_CONV_CLK_35Tcy         0xFF22 /* A/D Conversion Clock is 35*Tcy */
#define ADC_CONV_CLK_36Tcy         0xFF23 /* A/D Conversion Clock is 36*Tcy */
#define ADC_CONV_CLK_37Tcy         0xFF24 /* A/D Conversion Clock is 37*Tcy */
#define ADC_CONV_CLK_38Tcy         0xFF25 /* A/D Conversion Clock is 38*Tcy */
#define ADC_CONV_CLK_39Tcy         0xFF26 /* A/D Conversion Clock is 39*Tcy */
#define ADC_CONV_CLK_40Tcy         0xFF27 /* A/D Conversion Clock is 40*Tcy */
#define ADC_CONV_CLK_41Tcy         0xFF28 /* A/D Conversion Clock is 41*Tcy */
#define ADC_CONV_CLK_42Tcy         0xFF29 /* A/D Conversion Clock is 42*Tcy */
#define ADC_CONV_CLK_43Tcy         0xFF2A /* A/D Conversion Clock is 43*Tcy */
#define ADC_CONV_CLK_44Tcy         0xFF2B /* A/D Conversion Clock is 44*Tcy */
#define ADC_CONV_CLK_45Tcy         0xFF2C /* A/D Conversion Clock is 45*Tcy */
#define ADC_CONV_CLK_46Tcy         0xFF2D /* A/D Conversion Clock is 46*Tcy */
#define ADC_CONV_CLK_47Tcy         0xFF2E /* A/D Conversion Clock is 47*Tcy */
#define ADC_CONV_CLK_48Tcy         0xFF2F /* A/D Conversion Clock is 48*Tcy */
#define ADC_CONV_CLK_49Tcy         0xFF30 /* A/D Conversion Clock is 49*Tcy */
#define ADC_CONV_CLK_50Tcy         0xFF31 /* A/D Conversion Clock is 50*Tcy */
#define ADC_CONV_CLK_51Tcy         0xFF32 /* A/D Conversion Clock is 51*Tcy */
#define ADC_CONV_CLK_52Tcy         0xFF33 /* A/D Conversion Clock is 52*Tcy */
#define ADC_CONV_CLK_53Tcy         0xFF34 /* A/D Conversion Clock is 53*Tcy */
#define ADC_CONV_CLK_54Tcy         0xFF35 /* A/D Conversion Clock is 54*Tcy */
#define ADC_CONV_CLK_55Tcy         0xFF36 /* A/D Conversion Clock is 55*Tcy */
#define ADC_CONV_CLK_56Tcy         0xFF37 /* A/D Conversion Clock is 56*Tcy */
#define ADC_CONV_CLK_57Tcy         0xFF38 /* A/D Conversion Clock is 57*Tcy */
#define ADC_CONV_CLK_58Tcy         0xFF39 /* A/D Conversion Clock is 58*Tcy */
#define ADC_CONV_CLK_59Tcy         0xFF3A /* A/D Conversion Clock is 59*Tcy */
#define ADC_CONV_CLK_60Tcy         0xFF3B /* A/D Conversion Clock is 60*Tcy */
#define ADC_CONV_CLK_61Tcy         0xFF3C /* A/D Conversion Clock is 61*Tcy */
#define ADC_CONV_CLK_62Tcy         0xFF3D /* A/D Conversion Clock is 62*Tcy */
#define ADC_CONV_CLK_63Tcy         0xFF3E /* A/D Conversion Clock is 63*Tcy */
#define ADC_CONV_CLK_64Tcy         0xFF3F /* A/D Conversion Clock is 64*Tcy */

/*On selecting the macros from 65*Tcy to 256*Tcy will be set to 64*Tcy value*/
#define ADC_CONV_CLK_65Tcy         0xFF40 /* A/D Conversion Clock is 65*Tcy */
#define ADC_CONV_CLK_66Tcy         0xFF41 /* A/D Conversion Clock is 66*Tcy */
#define ADC_CONV_CLK_67Tcy         0xFF42 /* A/D Conversion Clock is 67*Tcy */
#define ADC_CONV_CLK_68Tcy         0xFF43 /* A/D Conversion Clock is 68*Tcy */
#define ADC_CONV_CLK_69Tcy         0xFF44 /* A/D Conversion Clock is 69*Tcy */
#define ADC_CONV_CLK_70Tcy         0xFF45 /* A/D Conversion Clock is 70*Tcy */
#define ADC_CONV_CLK_71Tcy         0xFF46 /* A/D Conversion Clock is 71*Tcy */
#define ADC_CONV_CLK_72Tcy         0xFF47 /* A/D Conversion Clock is 72*Tcy */
#define ADC_CONV_CLK_73Tcy         0xFF48 /* A/D Conversion Clock is 73*Tcy */
#define ADC_CONV_CLK_74Tcy         0xFF49 /* A/D Conversion Clock is 74*Tcy */
#define ADC_CONV_CLK_75Tcy         0xFF4A /* A/D Conversion Clock is 75*Tcy */
#define ADC_CONV_CLK_76Tcy         0xFF4B /* A/D Conversion Clock is 76*Tcy */
#define ADC_CONV_CLK_77Tcy         0xFF4C /* A/D Conversion Clock is 77*Tcy */
#define ADC_CONV_CLK_78Tcy         0xFF4D /* A/D Conversion Clock is 78*Tcy */
#define ADC_CONV_CLK_79Tcy         0xFF4E /* A/D Conversion Clock is 79*Tcy */
#define ADC_CONV_CLK_80Tcy         0xFF4F /* A/D Conversion Clock is 80*Tcy */
#define ADC_CONV_CLK_81Tcy         0xFF50 /* A/D Conversion Clock is 81*Tcy */
#define ADC_CONV_CLK_82Tcy         0xFF51 /* A/D Conversion Clock is 82*Tcy */
#define ADC_CONV_CLK_83Tcy         0xFF52 /* A/D Conversion Clock is 83*Tcy */
#define ADC_CONV_CLK_84Tcy         0xFF53 /* A/D Conversion Clock is 84*Tcy */
#define ADC_CONV_CLK_85Tcy         0xFF54 /* A/D Conversion Clock is 85*Tcy */
#define ADC_CONV_CLK_86Tcy         0xFF55 /* A/D Conversion Clock is 86*Tcy */
#define ADC_CONV_CLK_87Tcy         0xFF56 /* A/D Conversion Clock is 87*Tcy */
#define ADC_CONV_CLK_88Tcy         0xFF57 /* A/D Conversion Clock is 88*Tcy */
#define ADC_CONV_CLK_89Tcy         0xFF58 /* A/D Conversion Clock is 89*Tcy */
#define ADC_CONV_CLK_90Tcy         0xFF59 /* A/D Conversion Clock is 90*Tcy */
#define ADC_CONV_CLK_91Tcy         0xFF5A /* A/D Conversion Clock is 91*Tcy */
#define ADC_CONV_CLK_92Tcy         0xFF5B /* A/D Conversion Clock is 92*Tcy */
#define ADC_CONV_CLK_93Tcy         0xFF5C /* A/D Conversion Clock is 93*Tcy */
#define ADC_CONV_CLK_94Tcy         0xFF5D /* A/D Conversion Clock is 94*Tcy */
#define ADC_CONV_CLK_95Tcy         0xFF5E /* A/D Conversion Clock is 95*Tcy */
#define ADC_CONV_CLK_96Tcy         0xFF5F /* A/D Conversion Clock is 96*Tcy */
#define ADC_CONV_CLK_97Tcy         0xFF60 /* A/D Conversion Clock is 97*Tcy */
#define ADC_CONV_CLK_98Tcy         0xFF61 /* A/D Conversion Clock is 98*Tcy */
#define ADC_CONV_CLK_99Tcy         0xFF62 /* A/D Conversion Clock is 99*Tcy */
#define ADC_CONV_CLK_100Tcy        0xFF63 /* A/D Conversion Clock is 100*Tcy */
#define ADC_CONV_CLK_101Tcy        0xFF64 /* A/D Conversion Clock is 101*Tcy */
#define ADC_CONV_CLK_102Tcy        0xFF65 /* A/D Conversion Clock is 102*Tcy */
#define ADC_CONV_CLK_103Tcy        0xFF66 /* A/D Conversion Clock is 103*Tcy */
#define ADC_CONV_CLK_104Tcy        0xFF67 /* A/D Conversion Clock is 104*Tcy */
#define ADC_CONV_CLK_105Tcy        0xFF68 /* A/D Conversion Clock is 105*Tcy */
#define ADC_CONV_CLK_106Tcy        0xFF69 /* A/D Conversion Clock is 106*Tcy */
#define ADC_CONV_CLK_107Tcy        0xFF6A /* A/D Conversion Clock is 107*Tcy */
#define ADC_CONV_CLK_108Tcy        0xFF6B /* A/D Conversion Clock is 108*Tcy */
#define ADC_CONV_CLK_109Tcy        0xFF6C /* A/D Conversion Clock is 109*Tcy */
#define ADC_CONV_CLK_110Tcy        0xFF6D /* A/D Conversion Clock is 110*Tcy */
#define ADC_CONV_CLK_111Tcy        0xFF6E /* A/D Conversion Clock is 111*Tcy */
#define ADC_CONV_CLK_112Tcy        0xFF6F /* A/D Conversion Clock is 112*Tcy */
#define ADC_CONV_CLK_113Tcy        0xFF70 /* A/D Conversion Clock is 113*Tcy */
#define ADC_CONV_CLK_114Tcy        0xFF71 /* A/D Conversion Clock is 114*Tcy */
#define ADC_CONV_CLK_115Tcy        0xFF72 /* A/D Conversion Clock is 115*Tcy */
#define ADC_CONV_CLK_116Tcy        0xFF73 /* A/D Conversion Clock is 116*Tcy */
#define ADC_CONV_CLK_117Tcy        0xFF74 /* A/D Conversion Clock is 117*Tcy */
#define ADC_CONV_CLK_118Tcy        0xFF75 /* A/D Conversion Clock is 118*Tcy */
#define ADC_CONV_CLK_119Tcy        0xFF76 /* A/D Conversion Clock is 119*Tcy */
#define ADC_CONV_CLK_120Tcy        0xFF77 /* A/D Conversion Clock is 120*Tcy */
#define ADC_CONV_CLK_121Tcy        0xFF78 /* A/D Conversion Clock is 121*Tcy */
#define ADC_CONV_CLK_122Tcy        0xFF79 /* A/D Conversion Clock is 122*Tcy */
#define ADC_CONV_CLK_123Tcy        0xFF7A /* A/D Conversion Clock is 123*Tcy */
#define ADC_CONV_CLK_124Tcy        0xFF7B /* A/D Conversion Clock is 124*Tcy */
#define ADC_CONV_CLK_125Tcy        0xFF7C /* A/D Conversion Clock is 125*Tcy */
#define ADC_CONV_CLK_126Tcy        0xFF7D /* A/D Conversion Clock is 126*Tcy */
#define ADC_CONV_CLK_127Tcy        0xFF7E /* A/D Conversion Clock is 127*Tcy */
#define ADC_CONV_CLK_128Tcy        0xFF7F /* A/D Conversion Clock is 128*Tcy */
#define ADC_CONV_CLK_129Tcy        0xFF80 /* A/D Conversion Clock is 129*Tcy */
#define ADC_CONV_CLK_130Tcy        0xFF81 /* A/D Conversion Clock is 130*Tcy */
#define ADC_CONV_CLK_131Tcy        0xFF82 /* A/D Conversion Clock is 131*Tcy */
#define ADC_CONV_CLK_132Tcy        0xFF83 /* A/D Conversion Clock is 132*Tcy */
#define ADC_CONV_CLK_133Tcy        0xFF84 /* A/D Conversion Clock is 133*Tcy */
#define ADC_CONV_CLK_134Tcy        0xFF85 /* A/D Conversion Clock is 134*Tcy */
#define ADC_CONV_CLK_135Tcy        0xFF86 /* A/D Conversion Clock is 135*Tcy */
#define ADC_CONV_CLK_136Tcy        0xFF87 /* A/D Conversion Clock is 136*Tcy */
#define ADC_CONV_CLK_137Tcy        0xFF88 /* A/D Conversion Clock is 137*Tcy */
#define ADC_CONV_CLK_138Tcy        0xFF89 /* A/D Conversion Clock is 138*Tcy */
#define ADC_CONV_CLK_139Tcy        0xFF8A /* A/D Conversion Clock is 139*Tcy */
#define ADC_CONV_CLK_140Tcy        0xFF8B /* A/D Conversion Clock is 140*Tcy */
#define ADC_CONV_CLK_141Tcy        0xFF8C /* A/D Conversion Clock is 141*Tcy */
#define ADC_CONV_CLK_142Tcy        0xFF8D /* A/D Conversion Clock is 142*Tcy */
#define ADC_CONV_CLK_143Tcy        0xFF8E /* A/D Conversion Clock is 143*Tcy */
#define ADC_CONV_CLK_144Tcy        0xFF8F /* A/D Conversion Clock is 144*Tcy */
#define ADC_CONV_CLK_145Tcy        0xFF90 /* A/D Conversion Clock is 145*Tcy */
#define ADC_CONV_CLK_146Tcy        0xFF91 /* A/D Conversion Clock is 146*Tcy */
#define ADC_CONV_CLK_147Tcy        0xFF92 /* A/D Conversion Clock is 147*Tcy */
#define ADC_CONV_CLK_148Tcy        0xFF93 /* A/D Conversion Clock is 148*Tcy */
#define ADC_CONV_CLK_149Tcy        0xFF94 /* A/D Conversion Clock is 149*Tcy */
#define ADC_CONV_CLK_150Tcy        0xFF95 /* A/D Conversion Clock is 150*Tcy */
#define ADC_CONV_CLK_151Tcy        0xFF96 /* A/D Conversion Clock is 151*Tcy */
#define ADC_CONV_CLK_152Tcy        0xFF97 /* A/D Conversion Clock is 152*Tcy */
#define ADC_CONV_CLK_153Tcy        0xFF98 /* A/D Conversion Clock is 153*Tcy */
#define ADC_CONV_CLK_154Tcy        0xFF99 /* A/D Conversion Clock is 154*Tcy */
#define ADC_CONV_CLK_155Tcy        0xFF9A /* A/D Conversion Clock is 155*Tcy */
#define ADC_CONV_CLK_156Tcy        0xFF9B /* A/D Conversion Clock is 156*Tcy */
#define ADC_CONV_CLK_157Tcy        0xFF9C /* A/D Conversion Clock is 157*Tcy */
#define ADC_CONV_CLK_158Tcy        0xFF9D /* A/D Conversion Clock is 158*Tcy */
#define ADC_CONV_CLK_159Tcy        0xFF9E /* A/D Conversion Clock is 159*Tcy */
#define ADC_CONV_CLK_160Tcy        0xFF9F /* A/D Conversion Clock is 160*Tcy */
#define ADC_CONV_CLK_161Tcy        0xFFA0 /* A/D Conversion Clock is 161*Tcy */
#define ADC_CONV_CLK_162Tcy        0xFFA1 /* A/D Conversion Clock is 162*Tcy */
#define ADC_CONV_CLK_163Tcy        0xFFA2 /* A/D Conversion Clock is 163*Tcy */
#define ADC_CONV_CLK_164Tcy        0xFFA3 /* A/D Conversion Clock is 164*Tcy */
#define ADC_CONV_CLK_165Tcy        0xFFA4 /* A/D Conversion Clock is 165*Tcy */
#define ADC_CONV_CLK_166Tcy        0xFFA5 /* A/D Conversion Clock is 166*Tcy */
#define ADC_CONV_CLK_167Tcy        0xFFA6 /* A/D Conversion Clock is 167*Tcy */
#define ADC_CONV_CLK_168Tcy        0xFFA7 /* A/D Conversion Clock is 168*Tcy */
#define ADC_CONV_CLK_169Tcy        0xFFA8 /* A/D Conversion Clock is 169*Tcy */
#define ADC_CONV_CLK_170Tcy        0xFFA9 /* A/D Conversion Clock is 170*Tcy */
#define ADC_CONV_CLK_171Tcy        0xFFAA /* A/D Conversion Clock is 171*Tcy */
#define ADC_CONV_CLK_172Tcy        0xFFAB /* A/D Conversion Clock is 172*Tcy */
#define ADC_CONV_CLK_173Tcy        0xFFAC /* A/D Conversion Clock is 173*Tcy */
#define ADC_CONV_CLK_174Tcy        0xFFAD /* A/D Conversion Clock is 174*Tcy */
#define ADC_CONV_CLK_175Tcy        0xFFAE /* A/D Conversion Clock is 175*Tcy */
#define ADC_CONV_CLK_176Tcy        0xFFAF /* A/D Conversion Clock is 176*Tcy */
#define ADC_CONV_CLK_177Tcy        0xFFB0 /* A/D Conversion Clock is 177*Tcy */
#define ADC_CONV_CLK_178Tcy        0xFFB1 /* A/D Conversion Clock is 178*Tcy */
#define ADC_CONV_CLK_179Tcy        0xFFB2 /* A/D Conversion Clock is 179*Tcy */
#define ADC_CONV_CLK_180Tcy        0xFFB3 /* A/D Conversion Clock is 180*Tcy */
#define ADC_CONV_CLK_181Tcy        0xFFB4 /* A/D Conversion Clock is 181*Tcy */
#define ADC_CONV_CLK_182Tcy        0xFFB5 /* A/D Conversion Clock is 182*Tcy */
#define ADC_CONV_CLK_183Tcy        0xFFB6 /* A/D Conversion Clock is 183*Tcy */
#define ADC_CONV_CLK_184Tcy        0xFFB7 /* A/D Conversion Clock is 184*Tcy */
#define ADC_CONV_CLK_185Tcy        0xFFB8 /* A/D Conversion Clock is 185*Tcy */
#define ADC_CONV_CLK_186Tcy        0xFFB9 /* A/D Conversion Clock is 186*Tcy */
#define ADC_CONV_CLK_187Tcy        0xFFBA /* A/D Conversion Clock is 187*Tcy */
#define ADC_CONV_CLK_188Tcy        0xFFBB /* A/D Conversion Clock is 188*Tcy */
#define ADC_CONV_CLK_189Tcy        0xFFBC /* A/D Conversion Clock is 189*Tcy */
#define ADC_CONV_CLK_190Tcy        0xFFBD /* A/D Conversion Clock is 190*Tcy */
#define ADC_CONV_CLK_191Tcy        0xFFBE /* A/D Conversion Clock is 191*Tcy */
#define ADC_CONV_CLK_192Tcy        0xFFBF /* A/D Conversion Clock is 192*Tcy */
#define ADC_CONV_CLK_193Tcy        0xFFC0 /* A/D Conversion Clock is 193*Tcy */
#define ADC_CONV_CLK_194Tcy        0xFFC1 /* A/D Conversion Clock is 194*Tcy */
#define ADC_CONV_CLK_195Tcy        0xFFC2 /* A/D Conversion Clock is 195*Tcy */
#define ADC_CONV_CLK_196Tcy        0xFFC3 /* A/D Conversion Clock is 196*Tcy */
#define ADC_CONV_CLK_197Tcy        0xFFC4 /* A/D Conversion Clock is 197*Tcy */
#define ADC_CONV_CLK_198Tcy        0xFFC5 /* A/D Conversion Clock is 198*Tcy */
#define ADC_CONV_CLK_199Tcy        0xFFC6 /* A/D Conversion Clock is 199*Tcy */
#define ADC_CONV_CLK_200Tcy        0xFFC7 /* A/D Conversion Clock is 200*Tcy */
#define ADC_CONV_CLK_201Tcy        0xFFC8 /* A/D Conversion Clock is 201*Tcy */
#define ADC_CONV_CLK_202Tcy        0xFFC9 /* A/D Conversion Clock is 202*Tcy */
#define ADC_CONV_CLK_203Tcy        0xFFCA /* A/D Conversion Clock is 203*Tcy */
#define ADC_CONV_CLK_204Tcy        0xFFCB /* A/D Conversion Clock is 204*Tcy */
#define ADC_CONV_CLK_205Tcy        0xFFCC /* A/D Conversion Clock is 205*Tcy */
#define ADC_CONV_CLK_206Tcy        0xFFCD /* A/D Conversion Clock is 206*Tcy */
#define ADC_CONV_CLK_207Tcy        0xFFCE /* A/D Conversion Clock is 207*Tcy */
#define ADC_CONV_CLK_208Tcy        0xFFCF /* A/D Conversion Clock is 208*Tcy */
#define ADC_CONV_CLK_209Tcy        0xFFD0 /* A/D Conversion Clock is 209*Tcy */
#define ADC_CONV_CLK_210Tcy        0xFFD1 /* A/D Conversion Clock is 210*Tcy */
#define ADC_CONV_CLK_211Tcy        0xFFD2 /* A/D Conversion Clock is 211*Tcy */
#define ADC_CONV_CLK_212Tcy        0xFFD3 /* A/D Conversion Clock is 212*Tcy */
#define ADC_CONV_CLK_213Tcy        0xFFD4 /* A/D Conversion Clock is 213*Tcy */
#define ADC_CONV_CLK_214Tcy        0xFFD5 /* A/D Conversion Clock is 214*Tcy */
#define ADC_CONV_CLK_215Tcy        0xFFD6 /* A/D Conversion Clock is 215*Tcy */
#define ADC_CONV_CLK_216Tcy        0xFFD7 /* A/D Conversion Clock is 216*Tcy */
#define ADC_CONV_CLK_217Tcy        0xFFD8 /* A/D Conversion Clock is 217*Tcy */
#define ADC_CONV_CLK_218Tcy        0xFFD9 /* A/D Conversion Clock is 218*Tcy */
#define ADC_CONV_CLK_219Tcy        0xFFDA /* A/D Conversion Clock is 219*Tcy */
#define ADC_CONV_CLK_220Tcy        0xFFDB /* A/D Conversion Clock is 220*Tcy */
#define ADC_CONV_CLK_221Tcy        0xFFDC /* A/D Conversion Clock is 221*Tcy */
#define ADC_CONV_CLK_222Tcy        0xFFDD /* A/D Conversion Clock is 222*Tcy */
#define ADC_CONV_CLK_223Tcy        0xFFDE /* A/D Conversion Clock is 223*Tcy */
#define ADC_CONV_CLK_224Tcy        0xFFDF /* A/D Conversion Clock is 224*Tcy */
#define ADC_CONV_CLK_225Tcy        0xFFE0 /* A/D Conversion Clock is 225*Tcy */
#define ADC_CONV_CLK_226Tcy        0xFFE1 /* A/D Conversion Clock is 226*Tcy */
#define ADC_CONV_CLK_227Tcy        0xFFE2 /* A/D Conversion Clock is 227*Tcy */
#define ADC_CONV_CLK_228Tcy        0xFFE3 /* A/D Conversion Clock is 228*Tcy */
#define ADC_CONV_CLK_229Tcy        0xFFE4 /* A/D Conversion Clock is 229*Tcy */
#define ADC_CONV_CLK_230Tcy        0xFFE5 /* A/D Conversion Clock is 230*Tcy */
#define ADC_CONV_CLK_231Tcy        0xFFE6 /* A/D Conversion Clock is 231*Tcy */
#define ADC_CONV_CLK_232Tcy        0xFFE7 /* A/D Conversion Clock is 232*Tcy */
#define ADC_CONV_CLK_233Tcy        0xFFE8 /* A/D Conversion Clock is 233*Tcy */
#define ADC_CONV_CLK_234Tcy        0xFFE9 /* A/D Conversion Clock is 234*Tcy */
#define ADC_CONV_CLK_235Tcy        0xFFEA /* A/D Conversion Clock is 235*Tcy */
#define ADC_CONV_CLK_236Tcy        0xFFEB /* A/D Conversion Clock is 236*Tcy */
#define ADC_CONV_CLK_237Tcy        0xFFEC /* A/D Conversion Clock is 237*Tcy */
#define ADC_CONV_CLK_238Tcy        0xFFED /* A/D Conversion Clock is 238*Tcy */
#define ADC_CONV_CLK_239Tcy        0xFFEE /* A/D Conversion Clock is 239*Tcy */
#define ADC_CONV_CLK_240Tcy        0xFFEF /* A/D Conversion Clock is 240*Tcy */
#define ADC_CONV_CLK_241Tcy        0xFFF0 /* A/D Conversion Clock is 241*Tcy */
#define ADC_CONV_CLK_242Tcy        0xFFF1 /* A/D Conversion Clock is 242*Tcy */
#define ADC_CONV_CLK_243Tcy        0xFFF2 /* A/D Conversion Clock is 243*Tcy */
#define ADC_CONV_CLK_244Tcy        0xFFF3 /* A/D Conversion Clock is 244*Tcy */
#define ADC_CONV_CLK_245Tcy        0xFFF4 /* A/D Conversion Clock is 245*Tcy */
#define ADC_CONV_CLK_246Tcy        0xFFF5 /* A/D Conversion Clock is 246*Tcy */
#define ADC_CONV_CLK_247Tcy        0xFFF6 /* A/D Conversion Clock is 247*Tcy */
#define ADC_CONV_CLK_248Tcy        0xFFF7 /* A/D Conversion Clock is 248*Tcy */
#define ADC_CONV_CLK_249Tcy        0xFFF8 /* A/D Conversion Clock is 249*Tcy */
#define ADC_CONV_CLK_250Tcy        0xFFF9 /* A/D Conversion Clock is 250*Tcy */
#define ADC_CONV_CLK_251Tcy        0xFFFA /* A/D Conversion Clock is 251*Tcy */
#define ADC_CONV_CLK_252Tcy        0xFFFB /* A/D Conversion Clock is 252*Tcy */
#define ADC_CONV_CLK_253Tcy        0xFFFC /* A/D Conversion Clock is 253*Tcy */
#define ADC_CONV_CLK_254Tcy        0xFFFD /* A/D Conversion Clock is 254*Tcy */
#define ADC_CONV_CLK_255Tcy        0xFFFE /* A/D Conversion Clock is 255*Tcy */
#define ADC_CONV_CLK_256Tcy        0xFFFF /* A/D Conversion Clock is 256*Tcy */

/**** AD1CON4 register definition ****/
#define ADC_DMA_BUF_LEN1 			0xFFF8 /*Allocates 1 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN2 			0xFFF9 /*Allocates 2 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN4 			0xFFFA /*Allocates 4 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN8 			0xFFFB /*Allocates 8 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN16 			0xFFFC /*Allocates 16 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN32			0xFFFD /*Allocates 32 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN64			0xFFFE /*Allocates 64 words of buffer to each analog input*/
#define ADC_DMA_BUF_LEN128			0xFFFF /*Allocates 128 words of buffer to each analog input*/



/**** AD1CHS register definition ****/
#define ADC_CH0_NEG_SAMPLEB_VREFN   0x0000 /* CH0 negative input is VREF- */
#define ADC_CH0_NEG_SAMPLEB_MASK    (~ADC_CH0_NEG_SAMPLEB_AN1)  /* A/D channel0 negative sampleB mask */

#define ADC_CH0_NEG_SAMPLEB_VREFN   0x0000  /* CH0 negative input is VREF- */

#define ADC_CH0_POS_SAMPLEB_AN0     0x0000 /* A/D CH0 pos i/p sel for SAMPLE B is AN0 */
#define ADC_CH0_POS_SAMPLEB_AN1     0x0100 /* A/D CH0 pos i/p sel for SAMPLE B is AN1 */
#define ADC_CH0_POS_SAMPLEB_AN2     0x0200 /* A/D CH0 pos i/p sel for SAMPLE B is AN2 */
#define ADC_CH0_POS_SAMPLEB_AN3     0x0300 /* A/D CH0 pos i/p sel for SAMPLE B is AN3 */
#define ADC_CH0_POS_SAMPLEB_AN4     0x0400 /* A/D CH0 pos i/p sel for SAMPLE B is AN4 */
#define ADC_CH0_POS_SAMPLEB_AN5     0x0500 /* A/D CH0 pos i/p sel for SAMPLE B is AN5 */

#define ADC_CH0_POS_SAMPLEB_AN6     0x0600 /* A/D CH0 pos i/p sel for SAMPLE B is AN6 */
#define ADC_CH0_POS_SAMPLEB_AN7     0x0700 /* A/D CH0 pos i/p sel for SAMPLE B is AN7 */

#define ADC_CH0_POS_SAMPLEB_AVSS	0x0600 /* A/D CH0 pos i/p sel for SAMPLE B is AVSS */
#define ADC_CH0_POS_SAMPLEB_AVDD	0x0700 /* A/D CH0 pos i/p sel for SAMPLE B is AVDD */

#define ADC_CH0_POS_SAMPLEB_AN8     0x0800 /* A/D CH0 pos i/p sel for SAMPLE B is AN8 */

#define ADC_CH0_POS_SAMPLEB_AN9     0x0900 /* A/D CH0 pos i/p sel for SAMPLE B is AN9 */

#define ADC_CH0_POS_SAMPLEB_AN10    0x0A00 /* A/D CH0 pos i/p sel for SAMPLE B is AN10 */

#define ADC_CH0_POS_SAMPLEB_AN11    0x0B00 /* A/D CH0 pos i/p sel for SAMPLE B is AN11 */

#define ADC_CH0_POS_SAMPLEB_AN12    0x0C00 /* A/D CH0 pos i/p sel for SAMPLE B is AN12 */

#define ADC_CH0_POS_SAMPLEB_AN13    0x0D00 /* A/D CH0 pos i/p sel for SAMPLE B is AN13 */

#define ADC_CH0_POS_SAMPLEB_AN14    0x0E00 /* A/D CH0 pos i/p sel for SAMPLE B is AN14 */

#define ADC_CH0_POS_SAMPLEB_AN15    0x0F00 /* A/D CH0 pos i/p sel for SAMPLE B is AN15 */

#define ADC_CH0_POS_SAMPLEB_AN16    0x1000 /* A/D CH0 pos i/p sel for SAMPLE B is AN16 */
#define ADC_CH0_POS_SAMPLEB_AN17    0x1100 /* A/D CH0 pos i/p sel for SAMPLE B is AN17 */

#define ADC_CH0_POS_SAMPLEB_CTMU_TEMP    0x1000 /* No Channel used; all input floating; used for CTMU temperature sensor input*/
#define ADC_CH0_POS_SAMPLEB_CTMU         0x1100 /* No Channel used; all input floating; used for CTMU*/

#define ADC_CH0_POS_SAMPLEB_AN18     0x1200 /* A/D CH0 pos i/p sel for SAMPLE B is AN18 */
#define ADC_CH0_POS_SAMPLEB_AN19     0x1300 /* A/D CH0 pos i/p sel for SAMPLE B is AN19 */
#define ADC_CH0_POS_SAMPLEB_AN20     0x1400 /* A/D CH0 pos i/p sel for SAMPLE B is AN20 */
#define ADC_CH0_POS_SAMPLEB_AN21     0x1500 /* A/D CH0 pos i/p sel for SAMPLE B is AN21 */
#define ADC_CH0_POS_SAMPLEB_AN22     0x1600 /* A/D CH0 pos i/p sel for SAMPLE B is AN22 */
#define ADC_CH0_POS_SAMPLEB_AN23     0x1700 /* A/D CH0 pos i/p sel for SAMPLE B is AN23 */

#define ADC_CH0_POS_SAMPLEB_VDDCORE	 0x1A00 /* A/D CH0 pos i/p sel for SAMPLE B is Core Voltage (VDDCORE) */
#define ADC_CH0_POS_SAMPLEB_VBGDIV6  0x1B00 /* A/D CH0 pos i/p sel for SAMPLE B is band gap divided-by-six-reference (VBG/6)*/
#define ADC_CH0_POS_SAMPLEB_VBGDIV2  0x1B00 /* A/D CH0 pos i/p sel for SAMPLE B is band gap divided-by-two-reference (VBG/2) */
#define ADC_CH0_POS_SAMPLEB_VBG		 0x1C00 /* A/D CH0 pos i/p sel for SAMPLE B is band gap reference (VBG) */

#define ADC_CH0_POS_SAMPLEB_215VDD 0x1B00 /* A/D CH0 pos i/p sel for SAMPLE B is Upper guardband rail (0.215*VDD) */
#define ADC_CH0_POS_SAMPLEB_785VDD 0x1C00 /* A/D CH0 pos i/p sel for SAMPLE B is Upper guardband rail (0.785*VDD) */

#define ADC_CH0_POS_SAMPLEB_VBAT     0x1F00 /* A/D CH0 pos i/p sel for SAMPLE B is VBAT */

#define ADC_CH0_POS_SAMPLEB_VOLTREG  0x1D00 /* A/D CH0 pos i/p sel for SAMPLE B is voltage regulator output */

#define ADC_CH0_POS_SAMPLEB_MASK    (~0x1F00)  /* A/D channel0 positive sampleA mask */

#define ADC_CH0_NEG_SAMPLEA_VREFN   0x0000 /*A/D CH0 neg I/P sel for SAMPLE A is Vrefn */
#define ADC_CH0_NEG_SAMPLEA_MASK    (~ADC_CH0_NEG_SAMPLEA_AN1) /* A/D channel0 negative sampleA mask */

#define ADC_CH0_NEG_SAMPLEA_VREFN   0x0000  /* CH0 negative input is VREF- */
#define ADC_CH0_NEG_SAMPLEA_AN1     0x0040 /* CH0 negative input is AN1 */

#define ADC_CH0_NEG_SAMPLEA_AN0     0x0020 /* CH0 negative input is AN0 */
#define ADC_CH0_NEG_SAMPLEA_AN2     0x0060 /* CH0 negative input is AN2 */
#define ADC_CH0_NEG_SAMPLEA_AN3     0x0080 /* CH0 negative input is AN3 */
#define ADC_CH0_NEG_SAMPLEA_AN4     0x00A0 /* CH0 negative input is AN4*/

#define ADC_CH0_NEG_SAMPLEA_AN5     0x00C0 /* CH0 negative input is AN5 */

#define ADC_CH0_NEG_SAMPLEA_AN6     0x00E0 /* CH0 negative input is AN6 */

#define ADC_CH0_POS_SAMPLEA_AN0     0x0000 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN0 */
#define ADC_CH0_POS_SAMPLEA_AN1     0x0001 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN1 */
#define ADC_CH0_POS_SAMPLEA_AN2     0x0002 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN2 */
#define ADC_CH0_POS_SAMPLEA_AN3     0x0003 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN3 */
#define ADC_CH0_POS_SAMPLEA_AN4     0x0004 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN4 */
#define ADC_CH0_POS_SAMPLEA_AN5     0x0005 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN5 */

#define ADC_CH0_POS_SAMPLEA_AN6     0x0006 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN6 */
#define ADC_CH0_POS_SAMPLEA_AN7     0x0007 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN7 */
#define ADC_CH0_POS_SAMPLEA_AVSS	 0x0006 /* A/D CH0 pos i/p sel for SAMPLE A is AVSS */
#define ADC_CH0_POS_SAMPLEA_AVDD	 0x0007 /* A/D CH0 pos i/p sel for SAMPLE A is AVDD */
#define ADC_CH0_POS_SAMPLEA_VBG		 0x0006 /* A/D CH0 pos i/p sel for SAMPLE B is VBG */
#define ADC_CH0_POS_SAMPLEA_215VDD	 0x0007 /* A/D CH0 pos i/p sel for SAMPLE B is Upper guardband rail (0.215*VDD) */

#define ADC_CH0_POS_SAMPLEA_AN8     0x0008 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN8 */
#define ADC_CH0_POS_SAMPLEA_785VDD	 0x0008 /* A/D CH0 pos i/p sel for SAMPLE B is Upper guardband rail (0.785*VDD) */

#define ADC_CH0_POS_SAMPLEA_AN9     0x0009 /* A/D Chan 0 pos i/p sel for SAMPLE A is AN9 */

#define ADC_CH0_POS_SAMPLEA_AN10    0x000A /* A/D Chan 0 pos i/p sel for SAMPLE A is AN10 */

#define ADC_CH0_POS_SAMPLEA_AN11    0x000B /* A/D Chan 0 pos i/p sel for SAMPLE A is AN11 */

#define ADC_CH0_POS_SAMPLEA_AN12    0x000C /* A/D Chan 0 pos i/p sel for SAMPLE A is AN12 */

#define ADC_CH0_POS_SAMPLEA_AN13    0x000D /* A/D Chan 0 pos i/p sel for SAMPLE A is AN13 */
#define ADC_CH0_POS_SAMPLEA_CTMU         0x000D /* No Channel used; all input floating; used for CTMU*/

#define ADC_CH0_POS_SAMPLEA_AN14    0x000E /* A/D Chan 0 pos i/p sel for SAMPLE A is AN14 */
#define ADC_CH0_POS_SAMPLEA_VBGDIV2 0x000E /* A/D CH0 pos i/p sel for SAMPLE A is VBG/2*/ 

#define ADC_CH0_POS_SAMPLEA_AN15    0x000F /* A/D Chan 0 pos i/p sel for SAMPLE A is AN15 */

#define ADC_CH0_POS_SAMPLEA_AN16    0x0010 /* A/D CH0 pos i/p sel for SAMPLE A is AN16 */
#define ADC_CH0_POS_SAMPLEA_AN17    0x0011 /* A/D CH0 pos i/p sel for SAMPLE A is AN17 */

#define ADC_CH0_POS_SAMPLEA_AN18    0x0012 /* A/D CH0 pos i/p sel for SAMPLE A is AN18 */
#define ADC_CH0_POS_SAMPLEA_AN19    0x0013 /* A/D CH0 pos i/p sel for SAMPLE A is AN19 */
#define ADC_CH0_POS_SAMPLEA_AN20    0x0014 /* A/D CH0 pos i/p sel for SAMPLE A is AN20 */
#define ADC_CH0_POS_SAMPLEA_AN21    0x0015 /* A/D CH0 pos i/p sel for SAMPLE A is AN21 */
#define ADC_CH0_POS_SAMPLEA_AN22    0x0016 /* A/D CH0 pos i/p sel for SAMPLE A is AN22 */
#define ADC_CH0_POS_SAMPLEA_AN23    0x0017 /* A/D CH0 pos i/p sel for SAMPLE A is AN23 */

#define ADC_CH0_POS_SAMPLEA_VDDCORE	 0x001A /* A/D CH0 pos i/p sel for SAMPLE A is Core Voltage (VDDCORE) */
#define ADC_CH0_POS_SAMPLEA_VBGDIV6  0x001B /* A/D CH0 pos i/p sel for SAMPLE A is band gap divided-by-six-reference (VBG/6)*/

#define ADC_CH0_POS_SAMPLEA_VBAT     0x001F /* A/D CH0 pos i/p sel for SAMPLE A is VBAT */

#define ADC_CH0_POS_SAMPLEA_VOLTREG  0x001D /* A/D CH0 pos i/p sel for SAMPLE A is voltage regulator output */

#define ADC_CH0_POS_SAMPLEA_MASK    (~0x001F )  /* A/D channel0 positive sampleA mask */

/*** AD1CHS123 register definition ***/
#define ADC_CH123_NEG_SAMPLEB_AVSS		0x0200 /*Channel 1,2,3 Negative Input Select for Sample B bits is AVSS*/
#define ADC_CH123_NEG_SAMPLEB_GND		0x0000 /*Channel 1,2,3 Negative Input Select for Sample B bits is AVSS*/
#define ADC_CH123_NEG_SAMPLEB_MASK      (~ADC_CH123_NEG_SAMPLEB_AVSS) /* Channel 1,2,3 Negative Input Select for Sample B bits Mask*/

#define ADC_CH123_POS_SAMPLEB_AN012		0x0000  /* CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2 */
#define ADC_CH123_POS_SAMPLEB_MASK      (~ADC_CH123_POS_SAMPLEB_AN012) /* Channel1 sample B Mask*/
#define ADC_CH1_POS_SAMPLEB_AN3			0x0100  /* CH1 positive input is AN3, CH2 and CH3 positive inputs are not connected */
#define ADC_CH1_POS_SAMPLEB_AN3_MASK  (~ADC_CH1_POS_SAMPLEB_AN3) /* Channel 1,2,3 Positive Input Select for Sample B Mask */

#define ADC_CH123_POS_SAMPLEB_AN345		0xFFFF  /* CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5 */
#define ADC_CH123_POS_SAMPLEB_AN345_MASK  (~ADC_CH1_POS_SAMPLEB_AN3) /* Channel 1,2,3 Positive Input Select for Sample B Mask */

#define ADC_CH123_NEG_SAMPLEA_AVSS		0x0002 /*Channel 1,2,3 Negative Input Select for Sample A bits is AVSS*/ 
#define ADC_CH123_NEG_SAMPLEA_GND		0x0000 /*Channel 1,2,3 Negative Input Select for Sample A bits is AVSS*/ 
#define ADC_CH123_NEG_SAMPLEA_MASK      (~ADC_CH123_NEG_SAMPLEA_AVSS) /* Channel 1,2,3 Negative Input Select for Sample B bits Mask*/

#define ADC_CH123_POS_SAMPLEA_AN012		0xFFFE  /* CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2 */
#define ADC_CH123_POS_SAMPLEA_MASK      (~ADC_CH123_POS_SAMPLEA_AN012) /* Channel1 sample B Mask*/
#define ADC_CH1_POS_SAMPLEA_AN3			0xFFFF  /* CH1 positive input is AN3, CH2 and CH3 positive inputs are not connected */
#define ADC_CH1_POS_SAMPLEA_AN3_MASK    (~ADC_CH1_POS_SAMPLEA_AN3) /* Channel 1,2,3 Positive Input Select for Sample B Mask */



#define ADC_SCAN_AN0      			0xFFFF /*Enable Input Scan AN0 */
#define ADC_SKIP_SCAN_AN0      		0xFFFE /* Disable Input Scan AN0 */
#define ADC_SCAN_AN1      			0xFFFF /*Enable Input Scan AN1 */
#define ADC_SKIP_SCAN_AN1      		0xFFFD /* Disable Input Scan AN1 */
#define ADC_SCAN_AN2      			0xFFFF /*Enable Input Scan AN2 */
#define ADC_SKIP_SCAN_AN2      		0xFFFB /* Disable Input Scan AN2 */
#define ADC_SCAN_AN3      			0xFFFF /*Enable Input Scan AN3 */
#define ADC_SKIP_SCAN_AN3      		0xFFF7 /* Disable Input Scan AN3 */
#define ADC_SCAN_AN4      			0xFFFF /*Enable Input Scan AN4 */
#define ADC_SKIP_SCAN_AN4      		0xFFEF /* Disable Input Scan AN4 */
#define ADC_SCAN_AN5      			0xFFFF /*Enable Input Scan AN5 */
#define ADC_SKIP_SCAN_AN5      		0xFFDF /* Disable Input Scan AN5 */

#define ADC_SCAN_AN6      			0xFFFF /*Enable Input Scan AN6 */
#define ADC_SKIP_SCAN_AN6     		0xFFBF /* Disable Input Scan AN6 */
#define ADC_SCAN_AN7      			0xFFFF /*Enable Input Scan AN7 */
#define ADC_SKIP_SCAN_AN7      		0xFF7F /* Disable Input Scan AN7 */
#define ADC_SCAN_AN8      			0xFFFF /*Enable Input Scan AN8 */
#define ADC_SKIP_SCAN_AN8      		0xFEFF /* Disable Input Scan AN8 */

#define ADC_SCAN_AN9      		    0xFFFF /*Enable Input Scan AN9 */
#define ADC_SKIP_SCAN_AN9      		0xFDFF /* Disable Input Scan AN9 */

#define ADC_SCAN_AN10     			0xFFFF /*Enable Input Scan AN10 */
#define ADC_SKIP_SCAN_AN10     		0xFBFF /* Disable Input Scan AN10 */
#define ADC_SCAN_AN11     			0xFFFF /*Enable Input Scan AN11 */
#define ADC_SKIP_SCAN_AN11     		0xF7FF /* Disable Input Scan AN11 */

#define ADC_SCAN_AN12     			0xFFFF /*Enable Input Scan AN12 */
#define ADC_SKIP_SCAN_AN12          0xEFFF /* Disable Input Scan AN12 */

#define ADC_SCAN_AN13    			0xFFFF /*Enable Input Scan AN13 */
#define ADC_SKIP_SCAN_AN13     		0xDFFF /* Disable Input Scan AN13 */

#define ADC_SCAN_AN14    			0xFFFF /*Enable Input Scan AN14 */
#define ADC_SKIP_SCAN_AN14     		0xBFFF /* Disable Input Scan AN14 */

#define ADC_SCAN_AN15    			0xFFFF /*Enable Input Scan AN15 */
#define ADC_SKIP_SCAN_AN15    		0x7FFF /* Disable Input Scan AN15 */

#define ENABLE_ALL_INPUT_SCAN       0xFFFF /*Enable Input Scan AN0-AN15 */
#define DISABLE_ALL_INPUT_SCAN      0x0000 /*Disable Input Scan AN0-AN15 */


/**** AD1CSSH register definition ****/
#define ADC_SCAN_VBGDIV2           0xFFFF /*Internal VBG/2 channel selected for input scan*/
#define ADC_SKIP_SCAN_VBGDIV2      0xFFFE /*Analog channel omitted from input scan*/
#define ADC_SCAN_VBG               0xFFFF /*Internal band gap (VBG) channel selected for input scan */
#define ADC_SKIP_SCAN_VBG          0xFFFD /*Analog channel omitted from input scan*/

#define ADC_SCAN_AN16     			0xFFFF /*Enable Input Scan AN16 */
#define ADC_SKIP_SCAN_AN16    		0xFFFE /* Disable Input Scan AN16 */
#define ADC_SCAN_AN17     			0xFFFF /*Enable Input Scan AN17 */
#define ADC_SKIP_SCAN_AN17    		0xFFFD /* Disable Input Scan AN17 */

#define ADC_SCAN_AN18     			0xFFFF /*Enable Input Scan AN18 */
#define ADC_SKIP_SCAN_AN18    		0xFFFB /* Disable Input Scan AN18 */
#define ADC_SCAN_AN19     			0xFFFF /*Enable Input Scan AN19 */
#define ADC_SKIP_SCAN_AN19    		0xFFF7 /* Disable Input Scan AN19 */
#define ADC_SCAN_AN20     			0xFFFF /*Enable Input Scan AN20 */
#define ADC_SKIP_SCAN_AN20   		0xFFEF /* Disable Input Scan AN20 */
#define ADC_SCAN_AN21     			0xFFFF /*Enable Input Scan AN21 */
#define ADC_SKIP_SCAN_AN21    		0xFFDF /* Disable Input Scan AN21 */
#define ADC_SCAN_AN22     			0xFFFF /*Enable Input Scan AN22 */
#define ADC_SKIP_SCAN_AN22    		0xFFBF /* Disable Input Scan AN22 */
#define ADC_SCAN_AN23     			0xFFFF /*Enable Input Scan AN23 */
#define ADC_SKIP_SCAN_AN23    		0xFF7F /* Disable Input Scan AN23 */

#define ADC_SCAN_AN24     			0xFFFF /*Enable Input Scan AN24 */
#define ADC_SKIP_SCAN_AN24    		0xFEFF /* Disable Input Scan AN24 */
#define ADC_SCAN_AN25     			0xFFFF /*Enable Input Scan AN25 */
#define ADC_SKIP_SCAN_AN25    		0xFDFF /* Disable Input Scan AN25 */

#define ADC_SCAN_AN26     			0xFFFF /*Enable Input Scan AN26 */
#define ADC_SKIP_SCAN_AN26    		0xFBFF /* Disable Input Scan AN26 */
#define ADC_SCAN_AN27     			0xFFFF /*Enable Input Scan AN27 */
#define ADC_SKIP_SCAN_AN27    		0xF7FF/* Disable Input Scan AN27 */

#define ADC_SCAN_AN28     			0xFFFF /*Enable Input Scan AN28 */
#define ADC_SKIP_SCAN_AN28    		0xEFFF /* Disable Input Scan AN28 */
#define ADC_SCAN_AN29     			0xFFFF /*Enable Input Scan AN29 */
#define ADC_SKIP_SCAN_AN29    		0xDFFF/* Disable Input Scan AN29 */
#define ADC_SCAN_AN30     			0xFFFF /*Enable Input Scan AN30 */
#define ADC_SKIP_SCAN_AN30    		0xBFFF/* Disable Input Scan AN30 */


/***********************************************************************
Macro      : EnableIntADC1
Overview   : This macro enables the ADC interrupt.
Parameters : None
Remarks    : This macro sets ADC Interrupt Enable bit of Interrupt
             Enable Control Register.
************************************************************************/
#define EnableIntADC1                (IEC0bits.AD1IE = 1)

/***********************************************************************
Macro      : DisableIntADC1
Overview   : This macro disables the ADC interrupt.
Parameters : None
Remarks    : This macro clears ADC Interrupt Enable bit of Interrupt
             Enable Control register.
************************************************************************/
#define DisableIntADC1                (IEC0bits.AD1IE = 0)

/***********************************************************************
Macro      : SetPriorityIntADC1(priority)
Overview   : This macro sets priority for ADC interrupt.
Parameters : priority - This input parameter is the level of interrupt priority
Remarks    : This macro sets ADC Interrupt Priority bits of Interrupt
             Priority Control register.
************************************************************************/
#define SetPriorityIntADC1(priority)     (IPC3bits.AD1IP = priority)

/********************************************************************
Macro       : ADC1_Clear_Intr_Status_Bit
Overview    : Macro to Clear ADC Interrupt Status bit
Parameters  : None
Remarks     : None
*******************************************************************/
#define ADC1_Clear_Intr_Status_Bit (IFS0bits.AD1IF = 0)

/************************************************************************
Macro       : StopSampADC1
Overview    : This function is identical to ConvertADC10
Parameters  : None
Remarks     : This macro clears the ADCON1<SAMP> bit and thus stops sampling
              and starts conversion.
**************************************************************************/
#define StopSampADC1                 ConvertADC10

/************************************************************************
Macro       : BusySampADC1
Overview    : This function is identical to ConvertADC10
Parameters  : None
Remarks     : This macro clears the ADCON1<SAMP> bit and thus stops sampling
              and starts conversion.
**************************************************************************/
#define BusySampADC1              !(AD1CON1bits.SAMP)

/************************************************************************
Macro       : EnableADC1
Overview    : This function enables the ADC module
Parameters  : None
Remarks     : None.
**************************************************************************/
#define EnableADC1                (AD1CON1bits.ADON = 1)

/************************************************************************
Macro       : DisableADC1
Overview    : This function disables the ADC module
Parameters  : None
Remarks     : None.
**************************************************************************/
#define DisableADC1                (AD1CON1bits.ADON = 0)

/***********************************************************************
Macro      : EnableDMAADC1
Overview   : This macro enables the DMA functionality of ADC.
Parameters : None
Remarks    : This macro sets  the DMA functionality of ADC in AD1CON1 register.
************************************************************************/
#define EnableDMAADC1               (AD1CON1bits.DMAEN = 1)

/***********************************************************************
Macro      : DisableDMA_ADC1
Overview   : This macro disables the DMA functionality of ADC.
Parameters : None
Remarks    : This macro disables the DMA functionality of ADC in AD1CON1 register.
************************************************************************/
#define DisableDMAADC1               (AD1CON1bits.DMAEN = 0)

/***********************************************************************
Macro      : EnableDMAEXTNDBUFMODE  
Overview   : This macro enables the Extended Buffer mode of DMA functionality in ADC.
Parameters : None
Remarks    : This macro enables the Extended Buffer mode of DMA functionality 
			of ADC in AD1CON1 register.
************************************************************************/
#define EnableDMAEXTNDBUFMODE           (AD1CON1bits.DMABM = 1)

/***********************************************************************
Macro      : EnableDMAPIAMODE  
Overview   : This macro enables the Peripheral Indirect Adressing mode of 
			DMA functionality in ADC.
Parameters : None
Remarks    : This macro enables the Peripheral Indirect Adressing 
			of DMA functionality of ADC in AD1CON1 register.
************************************************************************/
#define EnableDMAPIAMODE                 (AD1CON1bits.DMABM = 0)


#define OpenADC10  OpenADC10_v4
void __attribute__ ((section (".libperi")))OpenADC10_v4(unsigned int config1,unsigned int config2,
            unsigned int config3,unsigned int config4,unsigned int configctmu_low,unsigned int configctmu_high,unsigned int configscan_low,unsigned int configscan_high);

/* Set A/D to specified channel */
void __attribute__ ((section (".libperi")))SetChanADC10(unsigned int channel0);

void __attribute__ ((section (".libperi")))ConvertADC10(void);

/* Read A/D result */
unsigned int __attribute__ ((section (".libperi")))ReadADC10(unsigned char bufIndex);

/* Turn off A/D */
void __attribute__ ((section (".libperi")))CloseADC10(void);

/* Check status of A/D conversion */
char __attribute__ ((section (".libperi")))BusyADC10(void) ;

void __attribute__ ((section (".libperi")))ConfigIntADC10(unsigned int config);

