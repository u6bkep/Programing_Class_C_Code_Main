/********************************************************************
* FileName:     main.c
* Dependencies:    
* Processor:    PIC24FV16KM202
* Hardware:     Microstick for 5V PIC24 K Series
* Compiler:     XC16 v1.1 or later
* Company:      Microchip Technology, Inc.
*
* Software License Agreement
*
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
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
* 
* Change History:
*
* Author        Revision #      Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* B. Ivey       1.00            01-15-2013  Initial code
********************************************************************/

#include <p24Fxxxx.h>

// Configuration Bits to make the part run from Internal FRCDIV

// Oscillator.


_FBS
(
    BWRP_OFF &      // Boot Segment Write Protect (Disabled)
    BSS_OFF         // Boot segment Protect (No boot flash segment)
)

_FGS
(
    GWRP_OFF &      // General Segment Flash Write Protect (General segment may be written)
    GCP_OFF        // General Segment Code Protect (No Protection)
)

_FOSCSEL
(
    FNOSC_FRCDIV &  // Oscillator Select (8MHz FRC with Postscaler (FRCDIV))
    SOSCSRC_ANA &   // SOSC Source Type (Analog Mode for use with crystal)
    LPRCSEL_HP &    // LPRC Power and Accuracy (High Power/High Accuracy)
    IESO_ON         // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))
)

_FOSC
(
    POSCMOD_NONE &   // Primary Oscillator Mode (Primary oscillator disabled)
    OSCIOFNC_IO &   // CLKO Enable Configuration bit (CLKO output signal enabled)
    POSCFREQ_MS &   // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock frequency between 100kHz to 8MHz)
    SOSCSEL_SOSCHP &// SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
    FCKSM_CSECME    // Clock Switching and Monitor Selection (Clock Switching and Fail-safe Clock Monitor Enabled)
)

_FWDT
(
    WDTPS_PS32768 & // Watchdog Timer Postscale Select bits (1:32768)
    FWPSA_PR128 &   // WDT Prescaler bit (WDT prescaler ratio of 1:128)
    FWDTEN_OFF &    // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
    WINDIS_OFF      // Windowed Watchdog Timer Disable bit (Standard WDT selected (windowed WDT disabled))
)

// Warning:
// Always enable MCLRE_ON config bit setting so that the MCLR pin function will
// work for low-voltage In-Circuit Serial Programming (ICSP). The Microstick
// programming circuitry only supports low-voltage ICSP. If you disable MCLR pin
// functionality, a high-voltage ICSP tool will be required to re-program the
// part in the future.
_FPOR
(
    BOREN_BOR3 &    // Brown-out Reset Enable bits (Enabled in hardware; SBOREN bit disabled)
    PWRTEN_ON &     // Power-up Timer Enable (PWRT enabled)
    I2C1SEL_PRI &   // Alternate I2C1 Pin Mapping bit (Default SCL1/SDA1 Pins for I2C1)
    BORV_V18 &      // Brown-out Reset Voltage bits (Brown-out Reset at 1.8V)
    MCLRE_ON        // MCLR Pin Enable bit (RA5 input disabled; MCLR enabled)
)

_FICD
(
    ICS_PGx3        // ICD Pin Placement Select (EMUC/EMUD share PGC3/PGD3)
)

// declare table
unsigned int LookupTable[10] = {0x3f00, 0x0600, 0x5B00, 0x4f00, 0x6600,
0x6D00,0x7D00, 0x0700, 0x7F00, 0x6F00};

// declare variables

  int NextTime = 7812;
  int Number = 0;


int main(void)
{


// setup outputes
    TRISAbits.TRISA0 = 0;
    TRISB = 0;

// configure timer
    PR1 = 0xFFFF;
    T1CON = 0x8030;
    TMR1 = 0;

//main program loop
    while(1)
    {
        // if number = 10, reset to 0
        if (Number == 10)
        {Number = 0;}

        // read timer
        if ((NextTime - (signed int) TMR1) <= 0)
        {
           NextTime = NextTime + 0x1E84;     // add to Next Time
           LATAbits.LATA0 ^= 1;              // Toggle the LED
           LATB = LookupTable[Number];       // write to display
           Number = Number + 1;              // increment Number
        }
    }
    
}