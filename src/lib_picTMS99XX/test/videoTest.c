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
unsigned char g_porteBuffer = 0;

void main(void) 
{
  /* happy fun time variables */
  int       index = 0;
  uint16_t  freq = 0;
  uint8_t   attn = 0;
  uint8_t   shiftRate = 0;
  uint8_t   color = 0;
  uint8_t   temp = 0;
  
  /* contains ti chip object */
  struct s_tms99XX tms99XX;
  
  char helloWorld[] = "Hello World!!!";
  
  char tag[] = "2022 Jay Convertino";
  
  /* GFX 8x8 characters */
  struct s_tms99XX_spritePatternTable8x8 tms8x8characters[] =
  {
    {{0x99, 0x66, 0x66, 0x99, 0x99, 0x66, 0x66, 0x99}},
    {{0x18, 0x99, 0x5A, 0x3C, 0x18, 0x18, 0x24, 0x42}},
    {{0x18, 0x99, 0x5A, 0x3C, 0x18, 0x18, 0x18, 0x24}},
    {{0x18, 0x99, 0x5A, 0x3C, 0x18, 0x18, 0x18, 0x18}}
  };
  
  /* Pattern table */
  //union u_tms99XX_patternTable8x8 patternTable[] = {{.data = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55}}};
  
  /* color table */
  //union u_tms99XX_colorTable colorTable[32] = {{.data = (TMS_LIGHT_RED << 4 | TMS_CYAN)}};
  
  /* sprite 1 */
  union u_tms99XX_spriteAttributeTable sprites[2] = {0};
  
  /* create struct to store ascii name table in order, skipping first 32 null patterns */
  uint8_t nameTable[1 + (sizeof(c_tms99XX_ascii) - (32 * 8))/8] = {0};

  /* buffer array to scoll a text line */
  uint8_t scrollArray[40] = {0};
  
  /* create nametable to display all ascii characters */
  for(index = 32; index < sizeof(nameTable)+32; index++)
  {
    nameTable[index-32] = (unsigned char)index;
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
  initTMS99XX(&tms99XX, GFXI_MODE, TMS_TRANSPARENT, &LATB, &PORTB, &LATD, &PORTC);
  
  setTMS99XXtxtColor(&tms99XX, TMS_WHITE);
  
  /* SYSTEM TESTS */
  
  /* check all vram */
  if(!checkTMS99XXvram(&tms99XX))
  {
    LATE = g_porteBuffer;
    return;
  }
  
  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);
  
  __delay_ms(1000);
  
  /* test all 16 background colors */
  for(index = 0; index <= TMS_WHITE; index++)
  {
    setTMS99XXbackgroundColor(&tms99XX, (unsigned char)index);
    __delay_ms(1000);
  }
  
  /* set to light blue for various tests */
  setTMS99XXbackgroundColor(&tms99XX, TMS_LIGHT_BLUE);
  
  /* MODE TESTS */
  /* FIRST: GFX I MODE, NORMAL 8x8 NO MAG*/
  setTMS99XXmode(&tms99XX, GFXI_MODE);
  
  setTMS99XXvramWriteAddr(&tms99XX, PATTERN_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, c_tms99XX_ascii, sizeof(c_tms99XX_ascii));
  
  /* write 2022 Jay Convertino on top line */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, tag, sizeof(tag)); 
  
  setTMS99XXvramWriteAddr(&tms99XX, COLOR_TABLE_ADDR);
  
  setTMS99XXvramConstData(&tms99XX, (TMS_BLACK << 4 | TMS_CYAN), 32);
  
  setTMS99XXvramWriteAddr(&tms99XX, SPRITE_PATTERN_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, tms8x8characters, sizeof(tms8x8characters));
  
  /* setup sprite 0 */
  sprites[0].dataNibbles.verticalPos = 0xFF;
  
  sprites[0].dataNibbles.horizontalPos = 0;
  
  sprites[0].dataNibbles.name = 0;
  
  sprites[0].dataNibbles.earlyClockBit = 0;
  
  sprites[0].dataNibbles.na = 0;
  
  sprites[0].dataNibbles.colorCode = TMS_DARK_RED;
  
  /* setup sprite 1 */
  sprites[1].dataNibbles.verticalPos = 177;
  
  sprites[1].dataNibbles.horizontalPos = 0;
  
  sprites[1].dataNibbles.name = 1;
  
  sprites[1].dataNibbles.earlyClockBit = 0;
  
  sprites[1].dataNibbles.na = 0;
  
  sprites[1].dataNibbles.colorCode = TMS_DARK_GREEN;
  
  /* write sprites to vram */
  setTMS99XXvramWriteAddr(&tms99XX, SPRITE_ATTRIBUTE_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, sprites, sizeof(sprites));
  
  /* enable screen */
  setTMS99XXblank(&tms99XX, 0);
  
  /* test GFX sprite in no mag mode */
  for(index = 0; index < 1000; index++)
  {
    LATE = g_porteBuffer;
    
    g_porteBuffer = (unsigned char)(g_porteBuffer == 4 ? 1 : g_porteBuffer << 1);
    
    __delay_ms(10);
    
    sprites[0].dataNibbles.verticalPos -= 5;
    
    sprites[0].dataNibbles.horizontalPos += 5;
    
    sprites[1].dataNibbles.horizontalPos += 1;
    
    if(!(sprites[1].dataNibbles.horizontalPos % 16))
    {
      sprites[1].dataNibbles.name++;
      
      if(sprites[1].dataNibbles.name == 4) sprites[1].dataNibbles.name = 1;
    }
    
    setTMS99XXvramWriteAddr(&tms99XX, SPRITE_ATTRIBUTE_TABLE_ADDR);
  
    setTMS99XXvramData(&tms99XX, sprites, sizeof(sprites));
  }
  
  /* test GFX sprite in mag mode */
  
  /* test GFX large sprite in no mag mode */
  
  /* test GFX large sprite in mag mode */
  
  LATE = 0;
  
  /* disable screen */
  setTMS99XXblank(&tms99XX, 1);
  
  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);
  
  /* LAST: TEXT MODE */
  setTMS99XXmode(&tms99XX, TXT_MODE);
  
  /* write to pattern table */
  setTMS99XXvramWriteAddr(&tms99XX, PATTERN_TABLE_ADDR);

  setTMS99XXvramData(&tms99XX, c_tms99XX_ascii, sizeof(c_tms99XX_ascii));
  
  /* first ascii letter is space in this table, no image */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramConstData(&tms99XX, 0, 0x7FF);
  
  /* write all ascii text */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, nameTable, sizeof(nameTable));
  
  
  /* write hello world on line 12 */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR + (40 * 11));
  
  setTMS99XXvramData(&tms99XX, helloWorld, sizeof(helloWorld));
  
  /* write 2022 Jay Convertino on last line (24 (23, offset 0)) */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR + (40 * 23));
  
  setTMS99XXvramData(&tms99XX, tag, sizeof(tag)); 
  
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
    g_porteBuffer = (unsigned char)(g_porteBuffer == 4 ? 1 : g_porteBuffer << 1);
    
    __delay_ms(50);
    
    /* read name table */
    setTMS99XXvramReadAddr(&tms99XX, NAME_TABLE_ADDR + (40 * 11));
    
    getTMS99XXvramData(&tms99XX, scrollArray, sizeof(scrollArray));
    
    /* shift all data from name table */
    /* write to name tabble */
    setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR + (40 * 11));
    
    setTMS99XXvramData(&tms99XX, &scrollArray[1], sizeof(scrollArray)-1);
    
    setTMS99XXvramData(&tms99XX, &scrollArray[0], 1);
  }
}
