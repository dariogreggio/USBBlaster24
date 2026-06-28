#include "plib.h"


/*************************************************************************************
Function:    char BusyADC10(void)

Overview:    This function returns the ADC conversion status.  

Parameters:  None

Returns:     If the value of DONE is ‘0’, then ‘1’ is returned,indicating that the
             ADC is busy in conversion.If the value of DONE is ‘1’, then ‘0’ is 
             returned, indicating that the ADC has completed conversion. 

Remarks:     This function returns the complement of the ADCON1 <DONE> bit
             status which indicates whether the ADC is busy in conversion.
            
***************************************************************************************/  
char BusyADC10(void)
{
    return !(AD1CON1bits.DONE);	/* returns the DONE bit status */
}


/***********************************************************************************************
Function:    void CloseADC10(void)

Overview:    This function turns off the ADC module and disables the ADC interrupts. 

Parameters:  None 

Returns:     None
 
Remarks:     This function first disables the ADC interrupt and then turns off the ADC
             module.The Interrupt Flag bit (ADIF) is also cleared.
***********************************************************************************************/

void CloseADC10(void)
{
    /* disable ADC interrupt */
    IEC0bits.AD1IE = 0;

    /* turn off ADC */
    AD1CON1bits.ADON = 0;

    /* clear ADIF bit */
    IFS0bits.AD1IF = 0;
}


/***************************************************************************************
Function           : void ConfigIntADC10(unsigned int config)

Overview           : This function configures the ADC interrupt.

Parameters         : config - ADC interrupt priority and enable/disable information 
                     as defined below 
					 
                     ADC Interrupt enable/disable
					   *	ADC_INT_ENABLE 
					   *	ADC_INT_DISABLE
					 ADC Interrupt priority
                       *	ADC_INT_PRI_0 
                       *	ADC_INT_PRI_1
                       *	ADC_INT_PRI_2
                       *	ADC_INT_PRI_3
                       *	ADC_INT_PRI_4
                       *	ADC_INT_PRI_5
                       *	ADC_INT_PRI_6
                       *	ADC_INT_PRI_7
                                            
Returns            : None 

Remarks            : This function clears the Interrupt Flag (ADIF) bit and then 
                     sets the interrupt priority and enables/disables the interrupt. 
****************************************************************************************/

void ConfigIntADC10(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS0bits.AD1IF = 0;

    /* Setting Priority */
    IPC3bits.AD1IP = config & 0x07;

    /* Setting the Interrupt enable bit */
    IEC0bits.AD1IE = (config & 0x08)>>3;
}


/************************************************************************************
Function           :void ConvertADC10(void)
 
Overview           :This function starts the A/D conversion.
 
Parameters         :None

Returns            :None 

Remarks            :This function clears the ADCON1<SAMP> bit and thus stops 
                    sampling and starts conversion.This happens only when 
                    trigger source for the A/D conversion is selected as Manual,
                    by clearing the ADCON1 <SSRC> bits.
**************************************************************************************/

void ConvertADC10(void)
{
     AD1CON1bits.SAMP = 0; /* clear SAMP to start conversion*/
}


/*************************************************************************************
Function    :void OpenADC10_v4(unsigned int config1, unsigned int config2, unsigned int config3,
             unsigned int config4,unsigned int configctmu_low,unsigned int configctmu_high,
			 unsigned int configscan_low, unsigned int configscan_high)					
					                                
Overview    : For seamless migration, it is recommended to call the above function as "OpenADC10".

Parameters  : config1 - This contains the parameters to be configured in the ADCON1 register register
			 config2 - This contains the parameters to be configured in the ADCON2 register
			 config3 - This contains the parameters to be configured in the ADCON3
			 config4 - This contains the parameters to be configured in the ADCON5 					 
			 configctmu_low- This contains the scan select parameter to be configured into the AD1CTMUENL
			 configctmu_high- This contains the scan select parameter to be configured into the AD1CTMUENH
			 configscan_low- This contains the scan select parameter to be configured into the AD1CSSL
			 configscan_high- This contains the scan select parameter to be configured into the AD1CSSH		
						 
Returns     : None
			
Remarks     : This function configures the ADC for the following parameters:
			Operating mode, Sleep mode behavior, Data o/p format, Sample Clk
			Source, VREF source, No of samples/int, Buffer Fill mode, Alternate i/p
			sample mode, Auto sample time, Charge Pump enable/disable,Conv clock source, 
			Conv Clock Select bits, Config Control bits.
		
************************************************************************************************/

void OpenADC10_v4(unsigned int config1, unsigned int config2, unsigned int config3,unsigned int config4,
                  unsigned int configchs123,unsigned int configchs0,unsigned int configscan_low, 
				  unsigned int configscan_high)
{
    /*configure ctmu selection bits*/
    AD1CHS0 = configchs0;
#if defined(__PIC24FJ64GB202__) || defined(__PIC24FJ128GB202__)
#else
    AD1CHS123 = configchs123;
#endif
	
    /* configures the input scan selection bits */
    AD1CSSL = configscan_low;
    AD1CSSH = (configscan_high & 0x7C03);
	
		/* config AD1CON4 */
    AD1CON4 = config4;
	
    /* config AD1CON3 */
    AD1CON3 = config3;

    /* config AD1CON2 */
    AD1CON2 = config2;

    /* config AD1CON1 */
    AD1CON1 = config1;

    /* assign SAMP bit */
    AD1CON1bits.SAMP = config1 >> 1;
}


/************************************************************************
Function           : unsigned int ReadADC10(unsigned char bufIndex) 

Overview           : This function reads the ADC Buffer register which contains 
                     the conversion value. 

Parameters         : bufIndex - This is the ADC buffer number which is to be read. 

Returns            : Returns the ADC Buffer value

Remarks            : This function returns the contents of the ADC Buffer register.
                     User should provide bufIndex value between ‘0’ to ‘15’ to 
                     ensure correct read of the ADCBUF0 to ADCBUFF.
 ************************************************************************/

unsigned int ReadADC10(unsigned char bufIndex)
{
     return(*(&ADC1BUF0+bufIndex));
}


/*********************************************************************
Function           : void SetChanADC10(unsigned int channel0) 

Overview           : This function sets the positive and negative inputs for 
                     the sample multiplexers A and B. 

Parameters         : channel0 - This contains the input select parameter to be 
                          configured into the ADCHS register
						  
Returns            : None 

Remarks            : This function configures the inputs for sample multiplexers 
                     A and B by writing to ADCHS register.
*********************************************************************/


void SetChanADC10(unsigned int channel0)
{
   
    AD1CHS0 = channel0;
// ?    AD1CHS123 = ;
	
}




/*******************************************************************************
Function Prototype : void OpenTimer1(unsigned int config,unsigned int period)
 
Include            : timer.h
 
Description        : This function configures the 16-bit timer module.
 
Arguments          : config - This contains the parameters to be configured in
                     the T1CON register as defined below
					 
			Timer Module On/Off						
			   *	T1_ON						
			   *	T1_OFF						
			Timer Module Idle mode On/Off						
			   *	T1_IDLE_CON						
			   *	T1_IDLE_STOP						
			Timer Gate time accumulation enable						
			   *	T1_GATE_ON						
			   *	T1_GATE_OFF						
			Timer prescaler						
			   *	T1_PS_1_1						
			   *	T1_PS_1_8						
			   *	T1_PS_1_64						
			   *	T1_PS_1_256						
			Timer Synchronous clock enable						
			   *	T1_SYNC_EXT_ON						
			   *	T1_SYNC_EXT_OFF						
			Timer clock source						
			   *	T1_SOURCE_EXT						
			   *	T1_SOURCE_INT						
			   
		  period - This contains the period match value to be stored 
		  into the PR register 
 
Return Value      : None
 
Remarks           : This function configures the 16-bit Timer Control register and 
                    sets the period match value into the PR register. 
**********************************************************************************/
void OpenTimer1(unsigned int config,unsigned int period)
{
    TMR1  = 0;          /* Reset Timer1 to 0x0000 */
    PR1   = period;     /* assigning Period to Timer period register */
    T1CON = config;     /* Configure timer control reg */
}


/***********************************************************************
Function Prototype : unsigned int ReadTimer1(void)
 
Include            : timer.h
 
Description        : This function reads the contents of the 16-bit 
                     Timer register.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function returns the contents of the 16-bit
                     TMRx register.
************************************************************************/


unsigned int ReadTimer1(void)
{
    return (TMR1);      /* Return the Timer1 register */
}


/****************************************************************************
Function Prototype : void ConfigIntTimer1(unsigned int config)

Include            : timer.h
 
Description        : This function configures the 16-bit timer interrupt.
 
Arguments          : config - Timer interrupt priority and enable/disable 
                     information as defined below
                     Timer Interrupt Priority
		   *	T1_INT_PRIOR_7					
		   *	T1_INT_PRIOR_6					
		   *	T1_INT_PRIOR_5					
		   *	T1_INT_PRIOR_4					
		   *	T1_INT_PRIOR_3					
		   *	T1_INT_PRIOR_2					
		   *	T1_INT_PRIOR_1					
		   *	T1_INT_PRIOR_0
		  Timer Interrupt Enable\Disable 					
		   *	T1_INT_ON					
		   *	T1_INT_OFF
					 
Return Value      : None
 
Remarks           : This function clears the 16-bit Interrupt Flag (TxIF) bit 
                    and then sets the interrupt priority and enables/disables 
                    the interrupt.
******************************************************************************/


void ConfigIntTimer1(unsigned int config)
{
    IFS0bits.T1IF = 0;                   /* clear IF bit */
    IPC0bits.T1IP = (config &0x0007);    /* assigning Interrupt Priority */
    IEC0bits.T1IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}


/************************************************************************
Function Prototype : void WriteTimer1(unsigned int timer)
 
Include            : timer.h
 
Description        : This function writes the 16-bit value into the 
                     Timer register.
 
Arguments          : timer - This is the 16-bit value to be stored into 
                     TMRx register.
 
Return Value       : None
 
Remarks            : None
*************************************************************************/
void WriteTimer1(unsigned int timer)
{
    TMR1 = timer;     /* assign timer value to Timer1 Register */
}


/****************************************************************************
Function Prototype : void CloseTimer1(void)
 
Include            : timer.h
 
Description        : This function turns off the 16-bit timer module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function first disables the 16-bit timer interrupt
                     and then turns off the timer module. The Interrupt 
                     Flag bit (TxIF) is also cleared.
****************************************************************************/

void CloseTimer1(void)
{
    IEC0bits.T1IE = 0;      /* Disable the Timer1 interrupt */
    T1CONbits.TON = 0;      /* Disable timer1 */
    IFS0bits.T1IF = 0;      /* Clear Timer interrupt flag */
}


/*******************************************************************************
Function Prototype : void OpenTimer2(unsigned int config,unsigned int period)
 
Include            : timer.h
 
Description        : This function configures the 16-bit timer module.
 
Arguments          : config - This contains the parameters to be configured in
                     the T2CON register as defined below
					 
			Timer Module On/Off						
			   *	T2_ON						
			   *	T2_OFF						
			Timer Module Idle mode On/Off						
			   *	T2_IDLE_CON						
			   *	T2_IDLE_STOP						
			Timer Gate time accumulation enable						
			   *	T2_GATE_ON						
			   *	T2_GATE_OFF						
			Timer prescaler						
			   *	T2_PS_1_1						
			   *	T2_PS_1_8						
			   *	T2_PS_1_64						
			   *	T2_PS_1_256						
			Timer 32bit mode enable/disable					
			   *	T2_32BIT_MODE_ON						
			   *	T2_32BIT_MODE_OFF					
			Timer clock source						
			   *	T2_SOURCE_EXT						
			   *	T2_SOURCE_INT						
			   
		  period - This contains the period match value to be stored 
		  into the PR register 
 
Return Value      : None
 
Remarks           : This function configures the 16-bit Timer Control register and 
                    sets the period match value into the PR register. 
**********************************************************************************/
void OpenTimer2(unsigned int config,unsigned int period)
{
    TMR2  = 0;          /* Reset Timer2 to 0x0000 */
    PR2   = period;     /* assigning Period to Timer period register */
    T2CON = config;     /* configure control reg */
    #if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4)
	T2CONbits.T32 = 0;
	#endif
	
}


/***********************************************************************
Function Prototype : unsigned int ReadTimer2(void)
 
Include            : timer.h
 
Description        : This function reads the contents of the 16-bit 
                     Timer register.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function returns the contents of the 16-bit
                     TMRx register.
************************************************************************/

unsigned int ReadTimer2(void)
{
    return (TMR2);      /* Return the Timer2 register */
}


/****************************************************************************
Function Prototype : void ConfigIntTimer2(unsigned int config)

Include            : timer.h
 
Description        : This function configures the 16-bit timer interrupt.
 
Arguments          : config - Timer interrupt priority and enable/disable 
                     information as defined below
                     Timer Interrupt Priority
		   *	T2_INT_PRIOR_7					
		   *	T2_INT_PRIOR_6					
		   *	T2_INT_PRIOR_5					
		   *	T2_INT_PRIOR_4					
		   *	T2_INT_PRIOR_3					
		   *	T2_INT_PRIOR_2					
		   *	T2_INT_PRIOR_1					
		   *	T2_INT_PRIOR_0
		  Timer Interrupt Enable\Disable 					
		   *	T2_INT_ON					
		   *	T2_INT_OFF
					 
Return Value      : None
 
Remarks           : This function clears the 16-bit Interrupt Flag (TxIF) bit 
                    and then sets the interrupt priority and enables/disables 
                    the interrupt.
******************************************************************************/


void ConfigIntTimer2(unsigned int config)
{
    IFS0bits.T2IF = 0;                   /* clear IF bit */
    IPC1bits.T2IP = (config &0x0007);    /* assigning Interrupt Priority */
    IEC0bits.T2IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}


/************************************************************************
Function Prototype : void WriteTimer2(unsigned int timer)
 
Include            : timer.h
 
Description        : This function writes the 16-bit value into the 
                     Timer register.
 
Arguments          : timer - This is the 16-bit value to be stored into 
                     TMRx register.
 
Return Value       : None
 
Remarks            : None
*************************************************************************/
void WriteTimer2(unsigned int timer)
{
    TMR2 = timer;     /* assign timer value to Timer2 Register */
}



/****************************************************************************
Function Prototype : void CloseTimer2(void)
 
Include            : timer.h
 
Description        : This function turns off the 16-bit timer module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function first disables the 16-bit timer interrupt
                     and then turns off the timer module. The Interrupt 
                     Flag bit (TxIF) is also cleared.
****************************************************************************/

void CloseTimer2(void)
{
    IEC0bits.T2IE = 0;      /* Disable the Timer2 interrupt */
    T2CONbits.TON = 0;      /* Disable timer2 */
    IFS0bits.T2IF = 0;      /* Clear Timer interrupt flag */
}


/*******************************************************************************
Function Prototype : void OpenTimer5(unsigned int config,unsigned int period)
 
Include            : timer.h
 
Description        : This function configures the 16-bit timer module.
 
Arguments          : config - This contains the parameters to be configured in
                     the T5CON register as defined below
					 
			Timer Module On/Off						
			   *	T5_ON						
			   *	T5_OFF						
			Timer Module Idle mode On/Off						
			   *	T5_IDLE_CON						
			   *	T5_IDLE_STOP						
			Timer Gate time accumulation enable						
			   *	T5_GATE_ON						
			   *	T5_GATE_OFF						
			Timer prescaler						
			   *	T5_PS_1_1						
			   *	T5_PS_1_8						
			   *	T5_PS_1_64						
			   *	T5_PS_1_256											
			Timer clock source						
			   *	T5_SOURCE_EXT						
			   *	T5_SOURCE_INT						
			   
		  period - This contains the period match value to be stored 
		  into the PR register 
 
Return Value      : None
 
Remarks           : This function configures the 16-bit Timer Control register and 
                    sets the period match value into the PR register. 
**********************************************************************************/
void OpenTimer5(unsigned int  config,unsigned int period)
{
    TMR5  = 0;          /* Reset Timer5 to 0x0000 */
    PR5   = period;     /* Assigning Period to Timer period register.*/
    T5CON =  config;    /* configure timer control reg */
}


/***********************************************************************
Function Prototype : unsigned int ReadTimer5(void)
 
Include            : timer.h
 
Description        : This function reads the contents of the 16-bit 
                     Timer register.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function returns the contents of the 16-bit
                     TMRx register.
************************************************************************/

unsigned int ReadTimer5(void)
{
    return (TMR5);      /* Return the Timer5 register */
}

/****************************************************************************
Function Prototype : void ConfigIntTimer5(unsigned int config)

Include            : timer.h
 
Description        : This function configures the 16-bit timer interrupt.
 
Arguments          : config - Timer interrupt priority and enable/disable 
                     information as defined below
					 
                     Timer Interrupt Priority
		   *	T5_INT_PRIOR_7					
		   *	T5_INT_PRIOR_6					
		   *	T5_INT_PRIOR_5					
		   *	T5_INT_PRIOR_4					
		   *	T5_INT_PRIOR_3					
		   *	T5_INT_PRIOR_2					
		   *	T5_INT_PRIOR_1					
		   *	T5_INT_PRIOR_0
		  Timer Interrupt Enable\Disable 					
		   *	T5_INT_ON					
		   *	T5_INT_OFF
					 
Return Value      : None
 
Remarks           : This function clears the 16-bit Interrupt Flag (TxIF) bit 
                    and then sets the interrupt priority and enables/disables 
                    the interrupt.
******************************************************************************/

void ConfigIntTimer5(unsigned int config)
{
    IEC1bits.T5IE = 0;                   /* clear IF bit */
    IPC7bits.T5IP = (config &0x0007);    /* assigning Interrupt Priority */
    IEC1bits.T5IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}

/************************************************************************
Function Prototype : void WriteTimer5(unsigned int timer)
 
Include            : timer.h
 
Description        : This function writes the 16-bit value into the 
                     Timer register.
 
Arguments          : timer - This is the 16-bit value to be stored into 
                     TMRx register.
 
Return Value       : None
 
Remarks            : None
*************************************************************************/

void WriteTimer5(unsigned int timer)
{
    TMR5 = timer;     /* assign timer value to Timer5 Register */
}

/****************************************************************************
Function Prototype : void CloseTimer5(void)
 
Include            : timer.h
 
Description        : This function turns off the 16-bit timer module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function first disables the 16-bit timer interrupt
                     and then turns off the timer module. The Interrupt 
                     Flag bit (TxIF) is also cleared.
****************************************************************************/
void CloseTimer5(void)
{
    IEC1bits.T5IE = 0;  /* Disable the Timer5 interrupt */
    T5CONbits.TON=0;    /* disable Timer 5 */
    IFS1bits.T5IF = 0;  /* Clear Timer5 interrupt flag */
}


