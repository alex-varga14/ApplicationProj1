/* 
 * File:   main.c
 * Author: Dominic Vandekerkhove, Alex Varga, Carter Fuchs 
 *
 * Created on October 7, 2021, 1:54 PM
 */

// PIC24F16KA101 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Start up CLK = 8 MHz
#pragma config IESO = OFF               // 2-speed startup disabled

// FOSC
#pragma config POSCMOD = NONE           // Primary oscillator mode is disabled
#pragma config OSCIOFNC = ON            // CLKO output disabled on pin 8, use as IO. 
#pragma config POSCFREQ = MS            // Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config SOSCSEL = SOSCLP         // Secondary oscillator for Low Power Operation
#pragma config FCKSM = CSECMD           // Clock switching is enabled, clock monitor disabled

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled)

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = OFF             // Power-up Timer Enable bit (PWRT disabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

//Include the compiler structures
#include <xc.h>
#include <p24F16KA101.h>
#include "UART2.h"

/*
 * 
 */



int main(int argc, char** argv) {
    InitUART2(); //initialize UART
    IOinit(); //initialize IO pins
    while(1) {
        IOcheck(); //Repeatedly check state of IO
    }
    
}
