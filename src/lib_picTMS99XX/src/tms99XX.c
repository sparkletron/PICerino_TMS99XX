/*******************************************************************************
 * @file    tms99XX.c
 * @brief   Library for TI video display processor.
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2022.02.12
 * @details VDP default is:
 *          1  = nCSR
 *          1  = nCSW
 *          1  = MODE
 *          FF = dataTRIS (all data lines are input).
 *          This allows for mode setting and data direction setting to be
 *          skipped for read.
 *          16K is assumed for memory.
 * 
 * @license mit
 * 
 * Copyright 2022 Johnathan Convertino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>

#include <tms99XX.h>

#define _XTAL_FREQ  48000000

/** SEE MY PRIVATES **/
/*** read VDP status register ***/
inline uint8_t readVDPstatus(struct s_tms99XX *p_tms99XX);
/*** read VDP vram ***/
inline int readVDPvram(struct s_tms99XX *p_tms99XX, uint8_t *p_data, int size, int modLen);
/*** write VDP vram ***/
inline int writeVDPvram(struct s_tms99XX *p_tms99XX, uint8_t *p_data, int size, int modLen);
/*** set write or read VDP vram address ***/
inline void writeVDPvramAddr(struct s_tms99XX *p_tms99XX, uint16_t address, int rnw);
/*** write VDP registers ***/
inline void writeVDPregister(struct s_tms99XX *p_tms99XX, uint8_t regNum, uint8_t data);
/*** graphics mode ***/
inline void initVDPmode(struct s_tms99XX *p_tms99XX);
/*** reset vdp ***/
inline void resetVDP(struct s_tms99XX *p_tms99XX);
/** bit setters **/
/*** NO NULL CHECK, USED INSIDE FUNCTIONS THAT DO THAT FIRST ***/
inline void setCtrlBitToOne(struct s_tms99XX *p_tms99XX, uint8_t bitNum);
inline void setCtrlBitToZero(struct s_tms99XX *p_tms99XX, uint8_t bitNum);

/** INITIALIZE AND FREE MY STRUCTS **/

/*** Initialize TMS99XX ports for correct I/O and set pin numbers ***/
void initTMS99XXport(struct s_tms99XX *p_tms99XX, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  if(!p_dataTRIS) return;
  
  if(!p_ctrlTRIS) return;
  
  if(!p_intTRIS) return;
  
  /**** populate TMS99XX structure ****/
  
  p_tms99XX->p_dataTRIS = p_dataTRIS;
  
  p_tms99XX->nCSR = nCSR;
  
  p_tms99XX->nCSW = nCSW;
  
  p_tms99XX->mode = mode;
  
  p_tms99XX->nreset = nreset;
  
  p_tms99XX->nINT = nINT;
  
  /**** setup control ports to default state ****/
  *p_tms99XX->p_dataTRIS = ~0;
  
  *p_ctrlTRIS &= (unsigned char)~((1 << nCSR) | (1 << nCSW) | (1 << mode) | (1 << nreset));
  
  *p_intTRIS |= (unsigned char)(1 << nINT);
}

/*** Initialize TMS99XX struct with ports to use for input output, must match direction registers above. ***/
void initTMS99XX(struct s_tms99XX *p_tms99XX, uint8_t vdpMode, uint8_t backColor, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  if(!p_dataPortW) return;
  
  if(!p_dataPortR) return;
  
  if(!p_ctrlPortW) return;
  
  if(!p_intPortR) return;
  
  /**** setup vdp struct ****/
  p_tms99XX->vdpMode = vdpMode;

  /**** clear register 0 ****/
  p_tms99XX->register0 = 0;
  
  /**** clear register 1, and set to 16k ****/
  p_tms99XX->register1 = (1 << VMEM_AMT_BIT);
  
  p_tms99XX->colorReg = (unsigned char)(backColor & 0x0F);
  
  /**** set vdp addresses ****/
  p_tms99XX->nameTableAddr = NAME_TABLE_ADDR;
  
  p_tms99XX->colorTableAddr = COLOR_TABLE_ADDR;
  
  p_tms99XX->patternTableAddr = PATTERN_TABLE_ADDR;
  
  p_tms99XX->spriteAttributeAddr = SPRITE_ATTRIBUTE_TABLE_ADDR;
  
  p_tms99XX->spritePatternAddr = SPRITE_PATTERN_TABLE_ADDR;
  
  /**** set VDP ports ****/
  p_tms99XX->p_dataPortW = p_dataPortW;
  
  p_tms99XX->p_dataPortR = p_dataPortR;
  
  p_tms99XX->p_ctrlPortW = p_ctrlPortW;
  
  p_tms99XX->p_intPortR = p_intPortR;
  
  /**** set ports to output default values ****/
  *p_tms99XX->p_dataPortW = 0x00;
  
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nreset);
  
  setCtrlBitToOne(p_tms99XX, p_tms99XX->mode);
  
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSR);
  
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);
  
  /**** reset vdp ****/
  resetVDP(p_tms99XX);
  
  /**** init vdp with defaults ****/
  initVDPmode(p_tms99XX);
}

/*** Set the TMS99XX mode to one of 4. Text, Graphics I, Graphics II, and bitmap. ***/
void setTMS99XXmode(struct s_tms99XX *p_tms99XX, uint8_t vdpMode, uint8_t register1)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  p_tms99XX->vdpMode = vdpMode;
  
  p_tms99XX->register1 = register1;
  
  initVDPmode(p_tms99XX);
}

/*** Set the TMS99XX to blank the current sprite and pattern planes. ***/
void setTMS99XXblank(struct s_tms99XX *p_tms99XX, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  /**** blank is active low, so for mode on (one) set reg bit to 0 ****/
  if(mode)
  {
    p_tms99XX->register1 &= (uint8_t)~(1 << BLK_SCRN_BIT);
  }
  else
  {
    p_tms99XX->register1 |= (uint8_t)(1 << BLK_SCRN_BIT);
  }
  
  writeVDPregister(p_tms99XX, REGISTER_1, p_tms99XX->register1);
}

/*** Set the TMS99XX to irq to enabled or disabled. ***/
void setTMS99XXirq(struct s_tms99XX *p_tms99XX, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  if(mode)
  {
    p_tms99XX->register1 |= (uint8_t)(1 << IRQ_BIT);
  }
  else
  {
    p_tms99XX->register1 &= (uint8_t)~(1 << IRQ_BIT);
  }
  
  writeVDPregister(p_tms99XX, REGISTER_1, p_tms99XX->register1);
}

/*** Set the TMS99XX to sprite size to 8x8 or 16x16. ***/
void setTMS99XXspriteSize(struct s_tms99XX *p_tms99XX, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  if(mode)
  {
    p_tms99XX->register1 |= (uint8_t)(1 << SPRITE_SIZE_BIT);
  }
  else
  {
    p_tms99XX->register1 &= (uint8_t)~(1 << SPRITE_SIZE_BIT);
  }
  
  writeVDPregister(p_tms99XX, REGISTER_1, p_tms99XX->register1);
}

/*** Set the TMS99XX to sprite magnify to on or off (double set size). ***/
void setTMS99XXspriteMagnify(struct s_tms99XX *p_tms99XX, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  if(mode)
  {
    p_tms99XX->register1 |= (uint8_t)(1 << SPRITE_MAG_BIT);
  }
  else
  {
    p_tms99XX->register1 &= (uint8_t)~(1 << SPRITE_MAG_BIT);
  }
  
  writeVDPregister(p_tms99XX, REGISTER_1, p_tms99XX->register1);
}

/*** Set the TMS99XX text color in text mode. ***/
void setTMS99XXtxtColor(struct s_tms99XX *p_tms99XX, uint8_t color)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  p_tms99XX->colorReg = (uint8_t)((p_tms99XX->colorReg & 0x0F) | ((color & 0x0F) << 4));
  
  writeVDPregister(p_tms99XX, REGISTER_7, p_tms99XX->colorReg);
}

/*** Set the TMS99XX background color. ***/
void setTMS99XXbackgroundColor(struct s_tms99XX *p_tms99XX, uint8_t color)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  p_tms99XX->colorReg = (uint8_t)((p_tms99XX->colorReg & 0xF0) | (color & 0x0F));
  
  writeVDPregister(p_tms99XX, REGISTER_7, p_tms99XX->colorReg);
}

/*** Set a register with a 8 bit value. ***/
void setTMS99XXreg(struct s_tms99XX *p_tms99XX, uint8_t regNum, uint8_t regData)
{
  writeVDPregister(p_tms99XX, regNum, regData);
}

/*** Write a struct/union table to vram using address. Alighned to data size. ***/
int setTMS99XXvramTableData(struct s_tms99XX *p_tms99XX, uint16_t tableAddr, void *p_data, int startNum, int number, int size)
{
  int index = 0;
  
  /**** set starting vram address to write too ****/
  writeVDPvramAddr(p_tms99XX, tableAddr + (uint16_t)(size * startNum), 0); 
  
  return writeVDPvram(p_tms99XX, (uint8_t *)p_data, size * number, size * number);
}

/*** Set the start of the write VRAM address. After this is set writes will auto increment the address. ***/
void setTMS99XXvramWriteAddr(struct s_tms99XX *p_tms99XX, uint16_t vramAddr)
{
  writeVDPvramAddr(p_tms99XX, vramAddr, 0);
}

/*** Set the start of the read VRAM. After this is set read will auto increment the address. ***/
void setTMS99XXvramReadAddr(struct s_tms99XX *p_tms99XX, uint16_t vramAddr)
{
  writeVDPvramAddr(p_tms99XX, vramAddr, 1);
}

/*** Write array of byte data to VRAM. ***/
int setTMS99XXvramData(struct s_tms99XX *p_tms99XX, void *p_data, int size)
{
  return writeVDPvram(p_tms99XX, (uint8_t *)p_data, size, size);
}

/*** constant value to VRAM. ***/
int setTMS99XXvramConstData(struct s_tms99XX *p_tms99XX, uint8_t data, int size)
{
  return writeVDPvram(p_tms99XX, &data, size, 1);
}

/*** Read array of byte data to VRAM. ***/
int getTMS99XXvramData(struct s_tms99XX *p_tms99XX, void *p_data, int size)
{
  return readVDPvram(p_tms99XX, (uint8_t *)p_data, size, size);
}

/*** Read status register of VDP. ***/
uint8_t getTMS99XXstatus(struct s_tms99XX *p_tms99XX)
{
  return readVDPstatus(p_tms99XX);
}

/*** clear data from VRAM. ***/
void clearTMS99XXvramData(struct s_tms99XX *p_tms99XX)
{
  uint8_t  data = 0x00;
  uint16_t index = 0;
  uint16_t amtWrote = 0;
  
  /**** set start address to write 0x00 to all of the VRAM ****/
  writeVDPvramAddr(p_tms99XX, 0x0000, 0);
  
  for(index = 0; index < MEM_SIZE; index += amtWrote)
  {
    amtWrote = (uint16_t)writeVDPvram(p_tms99XX, &data, MEM_SIZE - index, 1);
  }
}

/*** check vram with read write check ***/
uint8_t checkTMS99XXvram(struct s_tms99XX *p_tms99XX)
{
  /**** future improvemtn, crc check of some sort ****/
  uint16_t index = 0;
  uint16_t bufIndex = 0;
  uint8_t  buffer[256] = {0};
  uint8_t  data = 0x55;
  uint16_t amtRead = 0;
  uint16_t amtWrote = 0;
  
  /**** set start address to write 0x55 to all of the VRAM ****/
  writeVDPvramAddr(p_tms99XX, 0x0000, 0);
  
  for(index = 0; index < MEM_SIZE; index += amtWrote)
  {
    amtWrote = (uint16_t)writeVDPvram(p_tms99XX, &data, MEM_SIZE - index, 1);
  }
  
  /**** reset address to 0 for read ****/
  writeVDPvramAddr(p_tms99XX, 0x0000, 1);
  
  /**** loop in chunks of 256 to read vram ****/
  for(index = 0; index < MEM_SIZE; index += amtRead)
  {
    
    /**** read 256 chunk ****/
    amtRead = (uint16_t)readVDPvram(p_tms99XX, buffer, sizeof(buffer), sizeof(buffer));
    
    /**** check all chunks against original, return 0 if it fails ****/
    for(bufIndex = 0; bufIndex < amtRead; bufIndex++)
    {
      if(buffer[bufIndex] != data) return 0;
    }
  }
  
  /**** return 1 on success ****/
  return 1;
}

/** SEE MY PRIVATES **/
/*** read VDP status register ***/
inline uint8_t readVDPstatus(struct s_tms99XX *p_tms99XX)
{
  uint8_t tempData;
  
  /**** NULL Check ****/
  if(!p_tms99XX) return 0;
 
  di();
  
  /**** no need to set mode to 1 for register mode ****/
  
  /**** no need to set data bus to input mode ****/
  
  /**** set active low chip select read to 0 ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSR);
  
  /**** read data ****/
  tempData = *p_tms99XX->p_dataPortR;
  
  /**** set active low chip select read back to 1 ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSR);
  
  ei();
  
  return tempData;
  
}

/*** read VDP vram ***/
inline int readVDPvram(struct s_tms99XX *p_tms99XX, uint8_t *p_data, int size, int modLen)
{
  int index = 0;
  
  /**** NULL Check ****/
  if(!p_tms99XX) return 0;
 
  if(!p_data) return 0;
  
  di();
  
  /**** set mode to 0 ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->mode);
  
  /**** no need to set data bus to input mode ****/
  
  /**** pole for interrupt ****/
  /**** only pole if IRQ bit set and screen is not blank ****/
  /**** for 4.3 miliseconds there is no access window waiting, total time is then 4 us ****/
  /***** approx 1000 bytes can be handled ****/
  if(((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && ((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01))
  {
    /**** nINT is a negative interrupt, while loop will exit on 0 ****/
    while(((*p_tms99XX->p_intPortR) >> p_tms99XX->nINT) & 0x01);
  }
  
  for(index = 0; index < size; index++)
  {
    
    /**** set active low chip select read to 0 ****/
    setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSR);
    
    /**** read data from port into array ****/
    p_data[index % modLen] = *p_tms99XX->p_dataPortR;
    
    /**** set active low chip select read to 1 ****/
    setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSR);
    
    /**** use worst case delay if IRQ is not set and we are not blanking the screen ****/
    if(!((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && !((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01))
    {
      __delay_us(8);
    }
    
    /**** if irq is enabled, and blank is disabled, and index is 1000 or ever, return index since blank has run out ****/
    if(((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && ((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01) && (index >= 1000))
    {
      break;
    }
  }
  
  /**** status read clears the interrupt, also screws up access if done before data transfer  ****/
  readVDPstatus(p_tms99XX);

  /**** set mode to 1 ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->mode);
  
  ei();
  
  return index;
}

/*** write VDP vram ***/
inline int writeVDPvram(struct s_tms99XX *p_tms99XX, uint8_t *p_data, int size, int modLen)
{
  int index = 0;
  
  /**** NULL Check ****/
  if(!p_tms99XX) return 0;
  
  if(!p_data) return 0;
  
  di();
  
  /**** set mode to 0 ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->mode);
  
  /**** set data bus to output ****/
  *p_tms99XX->p_dataTRIS = 0x00;
  
  /**** pole for interrupt ****/
  /**** only pole if IRQ bit set and screen is not blank ****/
  /**** for 4.3 miliseconds there is no access window waiting, total time is then 4 us ****/
  /***** approx 1000 bytes can be handled ****/
  if(((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && ((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01))
  {
    /**** nINT is a negative interrupt, while loop will exit on 0 ****/
    while(((*p_tms99XX->p_intPortR) >> p_tms99XX->nINT) & 0x01);
  }
  
  for(index = 0; index < size; index++)
  {
    
    /**** write data to port from array of data at index ****/
    *p_tms99XX->p_dataPortW = p_data[index % modLen];
    
    /**** set active low chip select write to 0 ****/
    setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSW);
    
    /**** set active low chip select write to 1 ****/
    setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);
    
    if(!((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && !((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01))
    {
      __delay_us(8);
    }
    
    /**** if irq is enabled, and blank is disabled, and index is 1000 or ever, return index since blank has run out ****/
    if(((p_tms99XX->register1 >> IRQ_BIT) & 0x01) && ((p_tms99XX->register1 >> BLK_SCRN_BIT) & 0x01) && (index >= 1000))
    {
      break;
    }
  }
  
  /**** set data bus to input ****/
  *p_tms99XX->p_dataTRIS = 0xFF;
  
  /**** status read clears the interrupt, also screws up access if done before data transfer ****/
  readVDPstatus(p_tms99XX);
    
  /**** set mode to 1 ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->mode);
  
  ei();
  
  return index;
}

/*** write VDP registers ***/
inline void writeVDPregister(struct s_tms99XX *p_tms99XX, uint8_t regNum, uint8_t data)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  di();
  
  /**** set data bus to output ****/
  *p_tms99XX->p_dataTRIS = 0x00;
  
  /**** no need to set mode to 1 for register mode ****/
  
  /**** output data over bus ****/
  *p_tms99XX->p_dataPortW = data;
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSW);
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);
  
  /**** write msb as 1 and reg num to lower 3 bits ****/
  *p_tms99XX->p_dataPortW = (unsigned char)(0x80 | regNum);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSW);
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);
  
  /**** set data bus to input ****/
  *p_tms99XX->p_dataTRIS = 0xFF;

  ei();
}

/*** set write or read VDP vram address ***/
inline void writeVDPvramAddr(struct s_tms99XX *p_tms99XX, uint16_t address, int rnw)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  di();
  
  /**** no need to set mode to 1 for register mode ****/
  
  /**** set data bus to output ****/
  *p_tms99XX->p_dataTRIS = 0x00;
  
  /**** output bottom 8 bits of 14 bit address ****/
  *p_tms99XX->p_dataPortW = (unsigned char)(0xFF & address);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSW);
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);
  
  /**** write bit 7 as 0, 6 as 1, and rest are top 6 bits of address ****/
  *p_tms99XX->p_dataPortW = (unsigned char)((rnw != 0 ? 0x00 : 0x40) | (unsigned char)(0x3F & (address >> 8)));
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nCSW);

  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nCSW);

  /**** set data bus to input ****/
  *p_tms99XX->p_dataTRIS = 0xFF;
  
  ei();
}

/*** set modes by setting vdpMode ***/
/*** Default method per TI-VDP-Programmers_Guide.pdf ***/
inline void initVDPmode(struct s_tms99XX *p_tms99XX)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  /**** only graphics mode II will set M3 (bit 0) to 1 ****/
  p_tms99XX->register0 = (uint8_t)(0x02 & (p_tms99XX->vdpMode << 1));
  
  /**** keep previous register 1 settings, only change VDP mode ****/
  p_tms99XX->register1 = (uint8_t)((p_tms99XX->register1 & 0xE3) | ((0x6 & p_tms99XX->vdpMode) << 2));
  
  /**** setup register 0 ****/
  writeVDPregister(p_tms99XX, REGISTER_0, p_tms99XX->register0);
  
  /**** setup regsiter 1 ****/
  writeVDPregister(p_tms99XX, REGISTER_1, p_tms99XX->register1);
  
  /**** setup register 2 for a name table address ****/
  writeVDPregister(p_tms99XX, REGISTER_2, p_tms99XX->nameTableAddr >> NAME_TABLE_ADDR_SCALE);
  
  if(p_tms99XX->vdpMode == GFXII_MODE)
  {
    /**** setup register 3 for a color table address GFX II has two fixed values for its only two addresses ****/
    writeVDPregister(p_tms99XX, REGISTER_3, (uint8_t)((p_tms99XX->colorTableAddr == 0x0000) ? 0x7F : 0xFF));
    
    /**** setup register 4 for pattern table address GFX II has two fixed values for its only two addresses  ****/
    writeVDPregister(p_tms99XX, REGISTER_4, (uint8_t)((p_tms99XX->patternTableAddr == 0x0000) ? 0x03 : 0x07));
  }
  else
  {
    if(p_tms99XX->vdpMode != TXT_MODE)
    {
      /**** setup register 3 for a color table address ****/
      writeVDPregister(p_tms99XX, REGISTER_3, p_tms99XX->colorTableAddr >> COLOR_TABLE_ADDR_SCALE);
    }
    
    /**** setup register 4 for pattern table address  ****/
    writeVDPregister(p_tms99XX, REGISTER_4, p_tms99XX->patternTableAddr >> PATTERN_TABLE_ADDR_SCALE);
  }
  
  
  if(p_tms99XX->vdpMode != TXT_MODE)
  {
    /**** setup register 5 for sprite attribute table address ****/
    writeVDPregister(p_tms99XX, REGISTER_5, p_tms99XX->spriteAttributeAddr >> SPRITE_ATTRIBUTE_TABLE_ADDR_SCALE);
    
    /**** setup register 6 for sprite pattern table address ****/
    writeVDPregister(p_tms99XX, REGISTER_6, p_tms99XX->spritePatternAddr >> SPRITE_PATTERN_TABLE_ADDR_SCALE);
  }
  
  /**** setup register 7 for backdrop color ****/
  writeVDPregister(p_tms99XX, REGISTER_7, p_tms99XX->colorReg);
}

/*** reset vdp ***/
inline void resetVDP(struct s_tms99XX *p_tms99XX)
{
  /**** NULL Check ****/
  if(!p_tms99XX) return;
  
  di();
  
  /**** set reset to 0 to put vdp into reset mode ****/
  setCtrlBitToZero(p_tms99XX, p_tms99XX->nreset);
  
  /**** delay the needed amount of time per the ti data sheet ****/
  __delay_us(3);
  
  /**** set reset to 1 to take vdp out of reset mode ****/
  setCtrlBitToOne(p_tms99XX, p_tms99XX->nreset);
  
  ei();
}

/*** set bit to one ***/
inline void setCtrlBitToOne(struct s_tms99XX *p_tms99XX, uint8_t bitNum)
{
  *p_tms99XX->p_ctrlPortW |= (unsigned char)(1 << bitNum);
}

/*** set bit to zero ***/
inline void setCtrlBitToZero(struct s_tms99XX *p_tms99XX, uint8_t bitNum)
{
  *p_tms99XX->p_ctrlPortW &= (unsigned char)~(1 << bitNum);
}
