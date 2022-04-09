/*******************************************************************************
 * @file      picTEST.c
 * @author    Jay Convertino
 * @date      2022.03.01
 * @brief     Test PICerino platform
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>

#include <tms9928.h>

//setup to XTAL freq, for _delay macros
#define _XTAL_FREQ  48000000

/* 16K of memory */
#define _MEM_SIZE (1 << 14)

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
  uint8_t color = 0;
  
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
  ANSELB = 0;
  ANSELC = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  WPUB = 0;
  IOCB = 0;

  /* Port E set all to output */
  TRISE = 0;

  LATE = 0;

  g_porteBuffer = 1;

  /* wait for chip to be ready */
  __delay_ms(100);
  
  /* setup ports in struct for proper i/o */
  initTMS9928port(&tms9928, &TRISB, &TRISD, &TRISC, 3, 2, 0, 1, 6);
  
  /* setup tms9928 chip and finish setting up struct */
  initTMS9928(&tms9928, TXT_MODE, 0x80, 0x04, 0x0B, &LATB, &PORTB, &LATD, &PORTC);
  
  /* set start address */
  setTMS9928vramAddr(&tms9928, 0x0000);
  
  /* clear all ti vdp memory */
  clearTMS9928vramData(&tms9928, _MEM_SIZE);
  
  /* enable screen */
  setTMS9928blank(&tms9928, 0);
  
  for(;;)
  {
    setTMS9928backgroundColor(&tms9928, color);
    
    color++;
    
    color &= 0x0F;
    
    LATE = g_porteBuffer;
    g_porteBuffer = (g_porteBuffer == 4 ? 1 : (unsigned)g_porteBuffer << 1);
    __delay_ms(100);
  }
}
