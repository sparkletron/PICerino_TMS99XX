/*******************************************************************************
 * @file      picTEST.c
 * @author    Jay Convertino
 * @date      2022.03.01
 * @brief     Test PICerino platform
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>
#include <tms99XX.h>
#include <tms99XXascii.h>

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
  uint8_t   index = 0;
  uint16_t  freq = 0;
  uint8_t   attn = 0;
  uint8_t   shiftRate = 0;
  uint8_t   color = 0;
  uint8_t   temp = 0;
  
  uint16_t table_addr = NAME_TABLE_ADDR;
  
  struct s_tms99XX tms99XX;
  
  /* could just use an array, struct is for code consistency. */
  struct s_tms99XX_nameTable tms99XX_hello_name[] =
  {
    {0x00},
    {0x01},
    {0x02},
    {0x02},
    {0x03}
  };
  
  uint8_t nameTable[sizeof(c_tms99XX_ascii)/8] = {0};

  uint8_t scrollArray[40] = {0};
  
  for(index = 0; index < sizeof(nameTable); index++)
  {
    nameTable[index] = index;
  }
  
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
  
  /* disable pull ups */
  WPUB = 0;
  IOCB = 0;

  /* Port E set all to output */
  TRISE = 0;

  LATE = 0;

  g_porteBuffer = 1;

  /* wait for chip to be ready */
  __delay_ms(100);
  
  /* setup ports in struct for proper i/o */
  initTMS99XXport(&tms99XX, &TRISB, &TRISD, &TRISC, 3, 2, 0, 1, 6);
  
  /* setup tms9928 chip and finish setting up struct */
  initTMS99XX(&tms99XX, TXT_MODE, TMS_DARK_GREEN, &LATB, &PORTB, &LATD, &PORTC);
  
  setTMS99XXtxtColor(&tms99XX, TMS_WHITE);
  
  /* check all vram */
  if(!checkTMS99XXvram(&tms99XX))
  {
    LATE = g_porteBuffer;
    return;
  }
  
  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);
  
  /* write to pattern table */
  setTMS99XXvramWriteAddr(&tms99XX, PATTERN_TABLE_ADDR);

  setTMS99XXvramData(&tms99XX, c_tms99XX_ascii, sizeof(c_tms99XX_ascii));
  
  /* pattern 4 is all 0's, no image */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramConstData(&tms99XX, 0x04, 0x7FF);
  
  /* write hello world */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, nameTable, sizeof(nameTable));
  
  /* enable irq */
  /* when irq is enabled, polling will be used */
  /* disable to test 8 us delay method, no polling */
  setTMS99XXirq(&tms99XX, 1);
  
  /* enable screen */
  setTMS99XXblank(&tms99XX, 0);
  
  __delay_ms(1000);
  
  for(;;)
  {
    LATE = g_porteBuffer;
    g_porteBuffer = (g_porteBuffer == 4 ? 1 : (unsigned)g_porteBuffer << 1);
    
    __delay_ms(50);
    
    /* read name table */
    setTMS99XXvramReadAddr(&tms99XX, NAME_TABLE_ADDR);
    
    getTMS99XXvramData(&tms99XX, scrollArray, sizeof(scrollArray));
    
    /* shift all data from name table */
    /* write to name tabble */
    setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR-1);
    
    setTMS99XXvramData(&tms99XX, scrollArray, sizeof(scrollArray));
    
    setTMS99XXvramData(&tms99XX, &scrollArray[0], 1);
  }
}
