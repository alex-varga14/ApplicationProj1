/* 
 * File:   IOs.c
 * Author: Dominic Vandekerkhove, Alex Varga, Carter Fuchs 
 *
 * Created on October 7, 2021, 1:54 PM
 */
#include <xc.h>
#include <p24F16KA101.h>
#include "UART2.h"

//global variables
int CN30flag = 0;// flag for PB1
int CN1flag = 0;// flag for PB2
int CN0flag = 0;// flag for PB3

//function declarations
void IOinit();
void IOcheck();
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);

void IOinit() {
    AD1PCFG = 0xFFFF;
    
    TRISAbits.TRISA2 = 1;   //set PB1 as input
    CNPU2bits.CN30PUE = 1;  //pull up PB1
    CNEN2bits.CN30IE = 1;   //enable CN30 interrupt
    
    TRISBbits.TRISB4 = 1;   //set PB2 as input
    CNPU1bits.CN0PUE = 1;   //pull up PB2
    CNEN1bits.CN1IE = 1;   //enable CN1 interrupt
    
    TRISAbits.TRISA4 = 1;   //set PB3 as input
    CNPU1bits.CN1PUE = 1;   //pull up PB3
    CNEN1bits.CN0IE = 1;   //enable CN0 interrupt
    
    TRISBbits.TRISB8 = 0;   //set LED pin as output
    
    IPC4bits.CNIP = 5;      //set CN interrupt priority
    IFS1bits.CNIF = 0;      //clears the CN interrupt flag
    IEC1bits.CNIE = 1;      //enable the CN interrupt (general)
    
}

// PB1 pressed: 1 sec intervals ON and OFF
// PB2 pressed: 2 sec intervals ON and OFF
// PB3 pressed: 3 sec intervals ON and OFF
// two or more push buttons pressed: LED stays ON
// no PB pressed: LED stays OFF
void IOcheck() {
    
    if(CN30flag) { // if PB1 pressed
        if (CN1flag) { //PB2 also pressed
            if(CN0flag) {
                Disp2String("All buttons pressed"); //display message on terminal
            } else {
                Disp2String("PB1 and PB2 are pressed"); //display message on terminal
                LATBbits.LATB8 = 1; //Light up LED
            }
        } else if (CN0flag) {
            Disp2String("PB1 and PB3 are pressed"); //display message on terminal
            LATBbits.LATB8 = 1; //Light up LED
        } else { //only PB1 pressed
            Disp2String("PB1 is pressed"); //display message on terminal
            LATBbits.LATB8 = 1; //turn on LED
            Delay_ms(500); //wait 0.5 seconds
            LATBbits.LATB8 = 0; //turn off LED
            if(CN30flag && !CN1flag && !CN0flag) {
                //only PB1 still pressed by the time first delay finishes
                Delay_ms(500); //wait 0.5 seconds
            }
        }
    } else if(CN1flag) { //if PB2 pressed (and PB1 isn't)
        if (CN0flag) { //PB3 also pressed
            Disp2String("PB2 and PB3 are pressed"); //display message on terminal
            LATBbits.LATB8 = 1; //Light up LED
            //No delay
        } else {
            //only PB2 pressed
            Disp2String("PB2 is pressed"); //display message on terminal
            LATBbits.LATB8 = 1; //turn on LED
            Delay_ms(2000); //wait 2 seconds
            LATBbits.LATB8 = 0; //turn off LED
            if(!CN30flag && CN1flag && !CN0flag) {
                //only PB1 still pressed by the time first delay finishes
                Delay_ms(2000); //wait 2 seconds
            }
        }
    } else if (CN0flag) { //if PB3 pressed (and the other two aren't)
        //only PB3 is pressed
        Disp2String("PB3 is pressed"); //display message on terminal
        LATBbits.LATB8 = 1; //turn on LED
        Delay_ms(3000); //wait 3 seconds
        LATBbits.LATB8 = 0; //turn off LED
        if(!CN30flag && !CN1flag && CN0flag) {
            //only PB3 still pressed by the time first delay finishes
            Delay_ms(3000); //wait 3 seconds
        }
    } else { //no buttons are pressed
        Disp2String("Nothing pressed"); //display message on terminal
        LATBbits.LATB8 = 0; //turn off LED
    }
    Disp2String("\r\n"); //new line + carriage return for next terminal output
}


void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //clear T2 interrupt flag
    return;
}

void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt (void)
{
    if(IFS1bits.CNIF == 1)
    {   
        if(PORTAbits.RA2==0) {    // PB1 pressed
            CN30flag = 1; 
        }
        else {      // PB1 not pressed
            CN30flag = 0;
        }
        if (PORTBbits.RB4 == 0) // PB2 pressed
            CN1flag = 1; 
        else                    // PB2 not pressed
            CN1flag = 0;
        
        if (PORTAbits.RA4 == 0) // PB3 pressed
            CN0flag = 1; 
        else                    // PB3 not pressed
            CN0flag = 0;
        
        if ((CN0flag + CN1flag + CN30flag) == 0) {
            //none of the buttons are pressed
        }
    }
    
    IFS1bits.CNIF = 0; // clear IF flag
    Nop();
    
    return;
}