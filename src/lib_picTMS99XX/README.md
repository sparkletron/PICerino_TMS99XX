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
void main(void) 
{
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
  __delay_ms(10);

  
  /* play this lovely tune forever */
  for(;;);
}
```
