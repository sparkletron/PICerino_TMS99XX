/*******************************************************************************
 * @file      picTEST.c
 * @author    Jay Convertino
 * @date      2021.12.14
 * @brief     Test PICerino platform
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>

#include <tms9928.h>

//setup to XTAL freq, for _delay macros
#define _XTAL_FREQ  48000000

/* configuration bits */
#pragma config PLLSEL   = PLL3X
#pragma config CFGPLLEN = ON
#pragma config CPUDIV   = NOCLKDIV
#pragma config LS48MHZ  = SYS48X8
#pragma config FOSC     = INTOSCIO
#pragma config PCLKEN   = OFF
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config nPWRTEN  = OFF
#pragma config BOREN    = OFF
#pragma config BORV     = 190
#pragma config nLPBOR   = OFF
#pragma config WDTEN    = OFF
#pragma config WDTPS    = 32768
#pragma config CCP2MX   = RC1
#pragma config PBADEN   = OFF
#pragma config MCLRE    = OFF

//needed since chip is read-modify write only, and read in the same line doesn't work
uint8_t g_porteBuffer = 0;

void main(void) 
{
  uint16_t freq = 0;
  uint8_t attn = 0;
  uint8_t shiftRate = 0;
  
struct s_tms9928 tms9928;

  /* OSCCON SETUP */
  OSCCONbits.IRCF = 0x7;
  OSCCONbits.OSTS = 0;
  OSCCONbits.SCS  = 0x3;

  OSCCON2bits.PLLEN = 1;

  /* PORT E SETUP */
  INTCON2bits.nRBPU = 1;

  /* disable analog inputs */
  ANSELA = 0;
  ANSELC = 0;
  ANSELD = 0;
  ANSELE = 0;

  /* Port E set all to output */
  TRISE = 0;

  LATE = 0;

  g_porteBuffer = 1;

  /* wait for chip to be ready */
  __delay_ms(10);
  
  initTMS9928port(&tms9928, &TRISB, &TRISD, &TRISC, 3, 2, 0, 1, 6);
  
  initTMS9928(&tms9928, TXT_MODE, 0x80, 0x04, 0x0B, &LATB, &PORTB, &LATD, &PORTC);

  for(;;)
  {
    LATE = g_porteBuffer;
    g_porteBuffer = (g_porteBuffer == 4 ? 1 : (unsigned)g_porteBuffer << 1);
    __delay_ms(100);
  }
}
