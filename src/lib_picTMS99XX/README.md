# TMS99XX Video Display Processor Library

Software Library for TI TMS9918,28,29 video display processors.  

author: Jay Convertino  

data: 2022.01.31  

license: MIT

## Release Versions
### Current
  - release_v0.0.1

### Past
  - none
  
## Requirements
  - xc8-cc V2.32
  - PIC18F45K50 (MCU can be changed in makefile)
  - PICerino development board

## Building
  - make : builds all
  - make dox_gen : doxygen only
  - make test : test only
  - make libTMS99XX.a : static library only
  - make clean : remove all build outputs.
  
## Documentation
  - See doxygen generated document
  
### Example Code
```c
#include <xc.h>
#include <stdint.h>
#include <tms99XX.h>
#include <tms99XXascii.h>

void main(void) 
{
  int index = 0;

  /* contains ti chip object */
  struct s_tms99XX tms99XX;

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

  /* wait for chip to be ready */
  __delay_ms(100);

  /* setup ports in struct for proper i/o */
  initTMS99XXport(&tms99XX, &TRISB, &TRISD, &TRISC, 3, 2, 0, 1, 6);

  /* setup tms9928 chip and finish setting up struct */
  initTMS99XX(&tms99XX, GFXI_MODE, TMS_TRANSPARENT, &LATB, &PORTB, &LATD, &PORTC);

  /* SYSTEM TESTS */

  /* check all vram */
  if(!checkTMS99XXvram(&tms99XX))
  {
    __delay_ms(2000);
    return;
  }

  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);

  /* enable screen */
  setTMS99XXblank(&tms99XX, 0);
  
  /* Change the background color... forever */
  for(;;)
  {
    setTMS99XXbackgroundColor(&tms99XX, (unsigned char)index);

    __delay_ms(1000);

    /** wrap around at 16... values will be 0 to 15 **/
    index = (index + 1) % 16;
  }
}
```
