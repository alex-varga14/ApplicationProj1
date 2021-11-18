#include <xc.h>
#include <p24F16KA101.h>

void IOinit() {
    AD1PCFG = 0xFFFF;
    
    TRISAbits.TRISA2 = 1; //set PB1 as input
    CNPU2bits.CN30PUE = 1; //pull up PB1
    
    TRISBbits.TRISB4 = 1; //set PB2 as input
    CNPU1bits.CN0PUE = 1; //pull up PB2
    
    TRISAbits.TRISA4 = 1; //set PB3 as input
    CNPU1bits.CN1PUE = 1; //pull up PB3
    
    TRISBbits.TRISB8 = 0; //set LED pin as output
    
    
}

// PB1 pressed: 1 sec intervals ON and OFF
// PB2 pressed: 2 sec intervals ON and OFF
// PB3 pressed: 3 sec intervals ON and OFF
// two or more push buttons pressed: LED stays ON
// no PB pressed: LED stays OFF
void IOcheck() {
    
    if(PORTAbits.RA2 == 0) { // if PB1 pressed
        if (PORTAbits.RA4 == 0 || PORTBbits.RB4 == 0) { //if PB2 or PB3 also pressed
            LATBbits.LATB8 = 1; //Light up LED
            //No delay
        } else { //only PB1 pressed
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
        }
    } else if(PORTAbits.RA4 == 0) { //if PB2 pressed (and PB1 isn't)
        if (PORTBbits.RB4 == 0) { //if PB3 pressed
            LATBbits.LATB8 = 1; //Light up LED
            //No delay
        } else {
            LATBbits.LATB8 = 1;
            Delay_ms(2000);
            LATBbits.LATB8 = 0;
            Delay_ms(2000);
        }
    } else if (PORTBbits.RB4 == 0) { //if PB3 pressed (and the other two aren't)
        LATBbits.LATB8 = 1;
        Delay_ms(3000);
        LATBbits.LATB8 = 0;
        Delay_ms(3000);
    } else { //no buttons are pressed
        LATBbits.LATB8 = 0; //turn off LED
    }
}
