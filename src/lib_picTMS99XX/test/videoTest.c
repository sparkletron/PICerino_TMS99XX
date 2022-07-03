/*******************************************************************************
 * @file      videoTEST.c
 * @author    Jay Convertino
 * @date      2022.03.01
 * @brief     Test PICerino TMS99XX card.
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>
#include <tms99XX.h>
#include <tms99XXascii.h>

#define SPRITES_8X8_NUM 5

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

/* used since chip is read-modify write only */
unsigned char g_porteBuffer = 0;

void main(void) 
{
  /* happy fun time variables */
  int       index = 0;
  int       row = 0;
  int       col = 0;
  int       spriteIndex = 0;
  uint16_t  freq = 0;
  uint8_t   attn = 0;
  uint8_t   shiftRate = 0;
  uint8_t   color = 0;
  uint8_t   temp = 0;
  
  /* contains ti chip object */
  struct s_tms99XX tms99XX;
  
  char helloWorld[] = "Hello World!!!";
  
  char tag[] = "2022 Jay Convertino";
  
  char gfxi[] = "GFX I";
  
  char gfximag[] = "GFX I MAG";
  
  char txtmode[] = "TXT";
  
  /* GFX 8x8 sprites */
  struct s_tms99XX_spritePatternTable8x8 tms8x8sprites[] =
  {
    {{0x99, 0x66, 0x66, 0x99, 0x99, 0x66, 0x66, 0x99}}, //ship 1
    {{0x00, 0x18, 0x24, 0xFF, 0xFF, 0x24, 0x18, 0x00}}, //ship 2
    {{0x24, 0x3C, 0x18, 0x3C, 0x66, 0x7E, 0xC3, 0xFF}}, //ship 3
    {{0x24, 0x24, 0x24, 0x3C, 0x18, 0xFF, 0x66, 0xFF}}, //ship 4
    {{0x81, 0x42, 0x3C, 0x18, 0x3C, 0x66, 0xFF, 0xFF}}  //ship 5
  };
  
  /* sprite 1 */
  union u_tms99XX_spriteAttributeTable sprites[SPRITES_8X8_NUM] = {0};

  /* colors for bitmap bars */
  union u_tms99XX_BMPpixelBlock tmsWhitePixelBlock = {.dataNibbles = {TMS_WHITE, TMS_WHITE, TMS_WHITE, TMS_WHITE}};

  union u_tms99XX_BMPpixelBlock tmsYellowPixelBlock = { .dataNibbles = {TMS_LIGHT_YELLOW, TMS_LIGHT_YELLOW, TMS_LIGHT_YELLOW, TMS_LIGHT_YELLOW}};

  union u_tms99XX_BMPpixelBlock tmsCyanPixelBlock = { .dataNibbles = {TMS_CYAN, TMS_CYAN, TMS_CYAN, TMS_CYAN}};

  union u_tms99XX_BMPpixelBlock tmsGreenPixelBlock = { .dataNibbles = {TMS_LIGHT_GREEN, TMS_LIGHT_GREEN, TMS_LIGHT_GREEN, TMS_LIGHT_GREEN}};

  union u_tms99XX_BMPpixelBlock tmsMagentaPixelBlock = { .dataNibbles = {TMS_MAGENTA, TMS_MAGENTA, TMS_MAGENTA, TMS_MAGENTA}};

  union u_tms99XX_BMPpixelBlock tmsRedPixelBlock = { .dataNibbles = {TMS_MEDIUM_RED, TMS_MEDIUM_RED, TMS_MEDIUM_RED, TMS_MEDIUM_RED}};

  union u_tms99XX_BMPpixelBlock tmsBluePixelBlock = { .dataNibbles = {TMS_DARK_BLUE, TMS_DARK_BLUE, TMS_DARK_BLUE, TMS_DARK_BLUE}};

  union u_tms99XX_BMPpixelBlock tmsBlackPixelBlock = { .dataNibbles = {TMS_BLACK, TMS_BLACK, TMS_BLACK, TMS_BLACK}};
  
  /* create struct to store ascii name table in order, removing first 32 null patterns */
  uint8_t nameTable[1 + (sizeof(c_tms99XX_ascii)/8) - 32] = {0};

  /* buffer array to scoll a text line */
  uint8_t scrollArray[40] = {0};
  
  /* create nametable to display all ascii characters */
  for(index = 0; index < sizeof(nameTable); index++)
  {
    /** offset to skip first 32 nulls **/
    nameTable[index] = (unsigned char)index + 32;
  }
  
  /* OSCCON SETUP */
  OSCCONbits.IRCF = 0x7;
  OSCCONbits.OSTS = 0;
  OSCCONbits.SCS  = 0x3;

  OSCCON2bits.PLLEN = 1;

  /* disable analog inputs */
  ANSELA = 0;
  ANSELB = 0;
  ANSELC = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  /* enable pull ups */
  INTCON2bits.nRBPU = 0;
  WPUB = 0xFF;
  IOCB = 0;

  /* Port E set all to output */
  TRISE = 0;

  LATE = 0;

  g_porteBuffer = 4;

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
    __delay_ms(2000);
    return;
  }
  
  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);
  
  /* test all 16 background colors */
  for(index = 0; index <= TMS_WHITE; index++)
  {
    setTMS99XXbackgroundColor(&tms99XX, (unsigned char)index);
    
    __delay_ms(1000);
  }
  
  /* set to TMS_CYAN for various tests */
  setTMS99XXbackgroundColor(&tms99XX, TMS_CYAN);
  
  /* MODE TESTS */
  /* FIRST: GFX I MODE, NORMAL 8x8 NO MAG*/
  setTMS99XXmode(&tms99XX, GFXI_MODE);
  
  /* ascii chars */
  setTMS99XXvramWriteAddr(&tms99XX, PATTERN_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, c_tms99XX_ascii, sizeof(c_tms99XX_ascii));
  
  /* write 2022 Jay Convertino on top line */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, tag, sizeof(tag)); 
  
  setTMS99XXvramData(&tms99XX, gfxi, sizeof(gfxi));
  
  /* set colors for all patterns */
  setTMS99XXvramWriteAddr(&tms99XX, COLOR_TABLE_ADDR);
  
  setTMS99XXvramConstData(&tms99XX, (TMS_DARK_BLUE << 4 | TMS_BLACK), 32);
  
  setTMS99XXvramWriteAddr(&tms99XX, SPRITE_PATTERN_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, tms8x8sprites, sizeof(tms8x8sprites));
  
  /* setup sprites */
  for(spriteIndex = 0; spriteIndex < SPRITES_8X8_NUM; spriteIndex++)
  {
    /** border is 8x8 **/
    /** display is 256x192 Y top is 255 (-1). -1 to 191 (191 is in border) */ 
    sprites[spriteIndex].dataNibbles.verticalPos = rand()%184;
    
    /** display is 256x192 X left is 0. 0 to 255 (255 is in border) */
    sprites[spriteIndex].dataNibbles.horizontalPos = rand()%248;
    
    sprites[spriteIndex].dataNibbles.name = (uint8_t)spriteIndex;
    
    sprites[spriteIndex].dataNibbles.earlyClockBit = 0;
    
    sprites[spriteIndex].dataNibbles.na = 0;
    
    sprites[spriteIndex].dataNibbles.colorCode = 15 - (uint8_t)spriteIndex;
  }
  
  /* write sprites to vram */
  setTMS99XXvramWriteAddr(&tms99XX, SPRITE_ATTRIBUTE_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, sprites, sizeof(sprites));
  
  setTMS99XXvramSpriteTerm(&tms99XX, SPRITES_8X8_NUM);
  
  /* enable screen */
  setTMS99XXblank(&tms99XX, 0);
  
  /* test GFX sprite in no mag mode */
  for(index = 0; index < 1000; index++)
  {
    LATE = g_porteBuffer;
    
    g_porteBuffer = (unsigned char)(g_porteBuffer == 4 ? 1 : g_porteBuffer << 1);
    
    __delay_ms(10);
    
    for(spriteIndex = 0; spriteIndex < SPRITES_8X8_NUM; spriteIndex++)
    {
      if(sprites[spriteIndex].dataNibbles.verticalPos == 248)
      {
        sprites[spriteIndex].dataNibbles.verticalPos = 192;
      }
      
      sprites[spriteIndex].dataNibbles.verticalPos -= 1;
    }
    
    setTMS99XXvramWriteAddr(&tms99XX, SPRITE_ATTRIBUTE_TABLE_ADDR);
  
    setTMS99XXvramData(&tms99XX, sprites, sizeof(sprites));
  }
  
  /* test GFX sprite in mag mode */
  setTMS99XXspriteMagnify(&tms99XX, 1);
  
  /* write 2022 Jay Convertino on top line */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  
  setTMS99XXvramData(&tms99XX, tag, sizeof(tag)); 
  
  setTMS99XXvramData(&tms99XX, gfximag, sizeof(gfximag));
  
  for(index = 0; index < 1000; index++)
  {
    LATE = g_porteBuffer;
    
    g_porteBuffer = (unsigned char)(g_porteBuffer == 4 ? 1 : g_porteBuffer << 1);
    
    __delay_ms(10);
    
    for(spriteIndex = 0; spriteIndex < SPRITES_8X8_NUM; spriteIndex++)
    {
      if(sprites[spriteIndex].dataNibbles.verticalPos == 248)
      {
        sprites[spriteIndex].dataNibbles.verticalPos = 192;
      }
      
      sprites[spriteIndex].dataNibbles.verticalPos -= 1;
    }
    
    setTMS99XXvramWriteAddr(&tms99XX, SPRITE_ATTRIBUTE_TABLE_ADDR);
  
    setTMS99XXvramData(&tms99XX, sprites, sizeof(sprites));
  }
  
  /* test GFX large sprite in no mag mode */
  
  /* test GFX large sprite in mag mode */
  
  LATE = 0;
  
  /* SET TO BLACK */
  setTMS99XXbackgroundColor(&tms99XX, TMS_BLACK);

  /* disable screen */
  setTMS99XXblank(&tms99XX, 1);
  
  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);

  /* test multicolor bitmap mode */
  setTMS99XXmode(&tms99XX, BMP_MODE);

  /* write to pattern table */
  setTMS99XXvramWriteAddr(&tms99XX, PATTERN_TABLE_ADDR);

  /*
   * write white pixel block 4 times (8 bytes total, each block contains 2 bytes).
   * then write next, and the next and so on every 4... so for 8 colors thats 4*8 total
   * for 32 times. Every 4++ changes block to write.
   */
  for(index = 0; index < 32; index++)
  {
    if(index < 4)
    {
      setTMS99XXvramData(&tms99XX, &tmsWhitePixelBlock, sizeof(tmsWhitePixelBlock));
    }
    else if(index < 8)
    {
      setTMS99XXvramData(&tms99XX, &tmsYellowPixelBlock, sizeof(tmsYellowPixelBlock));
    }
    else if(index < 12)
    {
      setTMS99XXvramData(&tms99XX, &tmsCyanPixelBlock, sizeof(tmsCyanPixelBlock));
    }
    else if(index < 16)
    {
      setTMS99XXvramData(&tms99XX, &tmsGreenPixelBlock, sizeof(tmsGreenPixelBlock));
    }
    else if(index < 20)
    {
      setTMS99XXvramData(&tms99XX, &tmsMagentaPixelBlock, sizeof(tmsMagentaPixelBlock));
    }
    else if(index < 24)
    {
      setTMS99XXvramData(&tms99XX, &tmsRedPixelBlock, sizeof(tmsRedPixelBlock));
    }
    else if(index < 28)
    {
      setTMS99XXvramData(&tms99XX, &tmsBluePixelBlock, sizeof(tmsBluePixelBlock));
    }
    else
    {
      setTMS99XXvramData(&tms99XX, &tmsBlackPixelBlock, sizeof(tmsBlackPixelBlock));
    }
  }

  /* write to name table */
  setTMS99XXvramWriteAddr(&tms99XX, NAME_TABLE_ADDR);
  /*
   * populate name table... Row 0 is 0 for 4, then 1 for 4 till reaching 32.
   * Each row repeats this. There are 24 rows.
   */
  for(row = 0; row < 24; row++)
  {
    for(col = 0; col < 8; col++)
    {
      setTMS99XXvramConstData(&tms99XX, (uint8_t)col, 4);
    }
  }

  /* enable screen */
  setTMS99XXblank(&tms99XX, 0);

  /* test all 16 background colors */
  for(index = 0; index <= TMS_WHITE; index++)
  {
    setTMS99XXbackgroundColor(&tms99XX, (unsigned char)index);

    __delay_ms(1000);
  }

  /* dinable screen */
  setTMS99XXblank(&tms99XX, 1);

  /* clear all ti vdp memory */
  clearTMS99XXvramData(&tms99XX);

  /* LAST: TEXT MODE */
  setTMS99XXmode(&tms99XX, TXT_MODE);
  
  /* SET TO BLACK */
  setTMS99XXbackgroundColor(&tms99XX, TMS_BLACK);
  
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
  
  setTMS99XXvramData(&tms99XX, txtmode, sizeof(txtmode));
  
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
