#include <xc.h>
#include <p24F16KA101.h>


void Delay_ms(uint16_t time_ms) {
    //time_ms is in milliseconds, need to convert to PR2
    uint16_t PR2val = time_ms*16;
    /*
     1/(prescaler*(2/fosc))
     = 1/(256*(0.25 us))
     ~= 16
     units are 1/ms because this value is multiplied by time_ms which is in milliseconds
     */
    
    CLKDIV = 0; // change default timing from 2:1 to 1:1
    
    //T2 config
    T2CONbits.TSIDL = 0; // operate in idle mode
    T2CONbits.T32 = 0; // operate timer2 as 16-bit timer
    T2CONbits.TCS = 0; // use internal clock
    
    //T2CON prescaler
    T2CONbits.TCKPS0 = 0; 
    T2CONbits.TCKPS1 = 1;
    
    // Timer 2 interrupt config
    IPC1bits.T2IP = 2; // set priority for interrupt
    IEC0bits.T2IE = 1; //enables timer interrupt
    IFS0bits.T2IF = 0; // clears timer 2's flag
    
    PR2 = PR2val; //PR2 = time_ms translated to number of cycles
    TMR2 = 0; //start with timer 2 = 0
    
    T2CONbits.TON = 1; //start timer 2
    
    Idle(); //wait until interrupt
    
    T2CONbits.TON = 0; //stop timer 2
    TMR2 = 0;
    
    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //clear T2 interrupt flag
    return;
}
