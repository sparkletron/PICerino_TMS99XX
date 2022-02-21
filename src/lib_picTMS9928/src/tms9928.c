/*******************************************************************************
 * @file    tms9928.c
 * @brief   Library for TI video display processor.
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2022.02.12
 * @details VDP default is:
 *          1 = nCSR
 *          1 = nCSW
 *          0 = MODE
 *          0 = dataTRIS (all data lines are output).
 *          This allows for mode setting and data direction setting to be
 *          skipped.
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

#include <tms9928.h>

/** SEE MY PRIVATES **/
/*** read VDP status register ***/
inline uint8_t readVDPstatus(struct s_tms9928 *p_tms9928);
/*** read VDP vram ***/
inline void readVDPvram(struct s_tms9928 *p_tms9928, uint8_t *p_data, int size);
/*** write VDP vram ***/
inline void writeVDPvram(struct s_tms9928 *p_tms9928, uint8_t *p_data, int size);
/*** write VDP vram address ***/
inline void writeVDPvramAddr(struct s_tms9928 *p_tms9928, uint16_t address);
/*** write VDP registers ***/
inline void writeVDPregister(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t data);
/*** graphics mode I ***/
inline void initVDPmode(struct s_tms9928 *p_tms9928);
/*** reset vdp ***/
inline void resetVDP(struct s_tms9928 *p_tms9928);
/** bit setters **/
/*** NO NULL CHECK, USED INSIDE FUNCTIONS THAT DO THAT FIRST ***/
inline void setCtrlBitToOne(struct s_tms9928 *p_tms9928, uint8_t bitNum);
inline void setCtrlBitToZero(struct s_tms9928 *p_tms9928, uint8_t bitNum);

/** INITIALIZE AND FREE MY STRUCTS **/

/*** Initialize TMS9928 ports for correct I/O and set pin numbers ***/
void initTMS9928port(struct s_tms9928 *p_tms9928, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(!p_dataTRIS) return;
  
  if(!p_ctrlTRIS) return;
  
  if(!p_intTRIS) return;
  
  /**** populate TMS9928 structure ****/
  
  p_tms9928->p_dataTRIS = p_dataTRIS;
  
  p_tms9928->nCSR = nCSR;
  
  p_tms9928->nCSW = nCSW;
  
  p_tms9928->mode = mode;
  
  p_tms9928->nreset = nreset;
  
  p_tms9928->nINT = nINT;
  
  /**** setup ports to default state ****/
  
  *p_tms9928->p_dataTRIS = 0x00;
  
  *p_ctrlTRIS &= (unsigned char)~((1 << nCSR) | (1 << nCSW) | (1 << mode) | (1 << nreset));
  
  *p_intTRIS |= (unsigned char)(1 << nINT);
}

/*** Initialize TMS9928 struct with ports to use for input output, must match direction registers above. ***/
void initTMS9928(struct s_tms9928 *p_tms9928, uint8_t vdpMode, uint8_t register1, uint8_t txtColor, uint8_t backColor, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(!p_dataPortW) return;
  
  if(!p_dataPortR) return;
  
  if(!p_ctrlPortW) return;
  
  if(!p_intPortR) return;
  
  //disable interrupt
  
  /**** setup vdp struct ****/
  p_tms9928->vdpMode = vdpMode;

  /**** clear register 0 ****/
  p_tms9928->register0 = 0;
  
  /**** setup register 1 ****/
  p_tms9928->register1 = register1;
  
  p_tms9928->colorReg = (uint8_t)((txtColor << 4) | backColor);
  
  /**** set vdp addresses ****/
  p_tms9928->nameTableAddr = NAME_TABEL_ADDR;
  
  p_tms9928->colorTableAddr = COLOR_TABEL_ADDR;
  
  p_tms9928->patternTableAddr = PATTERN_TABEL_ADDR;
  
  p_tms9928->spriteAttributeAddr = SPRITE_ATTRIBUTE_TABEL_ADDR;
  
  p_tms9928->spritePatternAddr = SPRITE_PATTERN_TABEL_ADDR;
  
  /**** set VDP ports ****/
  p_tms9928->p_dataPortW = p_dataPortW;
  
  p_tms9928->p_dataPortR = p_dataPortR;
  
  p_tms9928->p_ctrlPortW = p_ctrlPortW;
  
  p_tms9928->p_intPortR = p_intPortR;
  
  /**** init vdp with defaults ****/
  initVDPmode(p_tms9928);
}

/*** Set the TMS9928 mode to one of 4. Text, Graphics I, Graphics II, and bitmap. ***/
void setTMS9928mode(struct s_tms9928 *p_tms9928, uint8_t vdpMode, uint8_t register1)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  p_tms9928->vdpMode = vdpMode;
  
  p_tms9928->register1 = register1;
  
  initVDPmode(p_tms9928);
}

/*** Set the TMS9928 to blank the current sprite and pattern planes. ***/
void setTMS9928blank(struct s_tms9928 *p_tms9928, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(mode)
  {
    p_tms9928->register1 |= (uint8_t)(1 << BLK_SCRN_BIT);
  }
  else
  {
    p_tms9928->register1 &= (uint8_t)~(1 << BLK_SCRN_BIT);
  }
  
  writeVDPregister(p_tms9928, REGISTER_1, p_tms9928->register1);
}

/*** Set the TMS9928 to irq to enabled or disabled. ***/
void setTMS9928irq(struct s_tms9928 *p_tms9928, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(mode)
  {
    p_tms9928->register1 |= (uint8_t)(1 << IRQ_BIT);
  }
  else
  {
    p_tms9928->register1 &= (uint8_t)~(1 << IRQ_BIT);
  }
  
  writeVDPregister(p_tms9928, REGISTER_1, p_tms9928->register1);
}

/*** Set the TMS9928 to sprite size to 8x8 or 16x16. ***/
void setTMS9928spriteSize(struct s_tms9928 *p_tms9928, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(mode)
  {
    p_tms9928->register1 |= (uint8_t)(1 << SPRITE_SIZE_BIT);
  }
  else
  {
    p_tms9928->register1 &= (uint8_t)~(1 << SPRITE_SIZE_BIT);
  }
  
  writeVDPregister(p_tms9928, REGISTER_1, p_tms9928->register1);
}

/*** Set the TMS9928 to sprite magnify to on or off (double set size). ***/
void setTMS9928spriteMagnify(struct s_tms9928 *p_tms9928, uint8_t mode)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(mode)
  {
    p_tms9928->register1 |= (uint8_t)(1 << SPRITE_MAG_BIT);
  }
  else
  {
    p_tms9928->register1 &= (uint8_t)~(1 << SPRITE_MAG_BIT);
  }
  
  writeVDPregister(p_tms9928, REGISTER_1, p_tms9928->register1);
}

/*** Set the TMS9928 text color in text mode. ***/
void setTMS9928txtColor(struct s_tms9928 *p_tms9928, uint8_t color)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  p_tms9928->colorReg = (uint8_t)((p_tms9928->colorReg & 0x0F) | ((color & 0x0F) << 4));
  writeVDPregister(p_tms9928, REGISTER_7, p_tms9928->colorReg);
}

/*** Set the TMS9928 background color. ***/
void setTMS9928backgroundColor(struct s_tms9928 *p_tms9928, uint8_t color)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  p_tms9928->colorReg = (uint8_t)((p_tms9928->colorReg & 0xF0) | (color & 0x0F));
  writeVDPregister(p_tms9928, REGISTER_7, p_tms9928->colorReg);
}

/*** Set a register with a 8 bit value. ***/
void setTMS9928reg(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t regData)
{
  writeVDPregister(p_tms9928, regNum, regData);
}

/*** Write a struct/union table to vram using address. Alighned to data size. ***/
void setTMS9928vramTableData(struct s_tms9928 *p_tms9928, uint16_t tableAddr, void *p_data, uint8_t startNum, uint8_t number, uint8_t size)
{
  int index = 0;
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(!p_data) return;
  
  //disable interrupt
  
  /**** set starting vram address to write too ****/
  writeVDPvramAddr(p_tms9928, tableAddr + (size * startNum));
  
  writeVDPvram(p_tms9928, (uint8_t *)p_data, size * number);
  
  //enable interrupt
}

/*** Set the start of the VRAM address to read or write to. After this is set read or writes will auto increment the address. ***/
void setTMS9928vramAddr(struct s_tms9928 *p_tms9928, uint16_t vramAddr)
{
  writeVDPvramAddr(p_tms9928, vramAddr);
}

/*** Write array of byte data to VRAM. ***/
void setTMS9928vramData(struct s_tms9928 *p_tms9928, void *p_data, int size)
{
  writeVDPvram(p_tms9928, (uint8_t *)p_data, size);
}

/*** Read array of byte data to VRAM. ***/
void getTMS9928vramData(struct s_tms9928 *p_tms9928, void *p_data, int size)
{
  readVDPvram(p_tms9928, (uint8_t *)p_data, size);
}

/*** Read status register of VDP. ***/
uint8_t getTMS9928status(struct s_tms9928 *p_tms9928)
{
  return readVDPstatus(p_tms9928);
}

/** SEE MY PRIVATES **/
/*** read VDP status register ***/
inline uint8_t readVDPstatus(struct s_tms9928 *p_tms9928)
{
  uint8_t tempData;
  
  /**** NULL Check ****/
  if(!p_tms9928) return 0;
 
  //disable interrupt
  
  /**** set mode to 1 for register mode ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->mode);
  
  /**** set data bus to input mode ****/
  *p_tms9928->p_dataTRIS = 0xFF;
  
  /**** set active low chip select read to 0 ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nCSR);
  
  /**** read data ****/
  tempData = *p_tms9928->p_dataPortR;
  
  /**** set active low chip select read back to 1 ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nCSR);
  
  /**** set mode back to 0, normal vram read/write ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->mode);
  
  /**** set data bus to output mode ****/
  *p_tms9928->p_dataTRIS = 0x00;
  
  //enable interrupt
  
  return tempData;
  
}

/*** read VDP vram ***/
inline void readVDPvram(struct s_tms9928 *p_tms9928, uint8_t *p_data, int size)
{
  int index = 0;
  
  /**** NULL Check ****/
  if(!p_tms9928) return;
 
  if(!p_data) return;
  
  //disable interrupt
  
  /**** no need to set mode, vram mode 0, is the default ****/
  
  /**** set data bus to input mode ****/
  *p_tms9928->p_dataTRIS = 0xFF;
  
  for(index = 0; index < size; index++)
  {
    /**** set active low chip select read to 0 ****/
    setCtrlBitToZero(p_tms9928, p_tms9928->nCSR);
    
    /**** read data from port into array ****/
    p_data[index] = *p_tms9928->p_dataPortR;
    
    /**** set active low chip select read to 1 ****/
    setCtrlBitToOne(p_tms9928, p_tms9928->nCSR);
  }
  
  /**** set data bus to output mode ****/
  *p_tms9928->p_dataTRIS = 0x00;

  //enable interrupt
}

/*** write VDP vram ***/
inline void writeVDPvram(struct s_tms9928 *p_tms9928, uint8_t *p_data, int size)
{
  int index = 0;
  
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  if(!p_data) return;
  
  //disable interrupt
  
  /**** no need to set mode, vram mode 0, is the default ****/
  
  /**** no need to set data bus, output is default ****/
  
  for(index = 0; index < size; index++)
  {
    /**** set active low chip select write to 0 ****/
    setCtrlBitToZero(p_tms9928, p_tms9928->nCSW);
    
    //may need to be last, seems like rising edge is when data is latched.
    /**** write data to port from array of data at index ****/
    *p_tms9928->p_dataPortW = p_data[index];
    
    /**** set active low chip select write to 1 ****/
    setCtrlBitToOne(p_tms9928, p_tms9928->nCSW);
  }
  
  //enable interrupt
}

/*** write VDP registers ***/
inline void writeVDPregister(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t data)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  //disable interrupt
  
  /**** no need to set data bus, output is default ****/
  
  /**** set mode to one ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->mode);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nCSW);
  
  /**** output data over bus ****/
  *p_tms9928->p_dataPortW = data;
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nCSW);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nCSW);
  
  /**** write msb as 1 and reg num to lower 3 bits ****/
  *p_tms9928->p_dataPortW = (unsigned char)(0x80 | regNum);
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nCSW);
  
  /**** set mode back to 0 ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->mode);

  //enable interrupt
}

/*** write VDP vram address ***/
inline void writeVDPvramAddr(struct s_tms9928 *p_tms9928, uint16_t address)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  //disable interrupt
  
  /**** no need to set data bus, output is default ****/
  
  /**** set mode to one ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->mode);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nCSW);
  
  /**** output top 8 bits of 14 bit address ****/
  *p_tms9928->p_dataPortW = (unsigned char)(0xFF & (address >> 6));
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nCSW);
  
  /**** set chip select write to low ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nCSW);
  
  /**** write bit 7 as 0, 6 as 1, and rest are low 6 bits of address ****/
  *p_tms9928->p_dataPortW = (unsigned char)(0x40 | (0x3F & address));
  
  /**** set chip select write to high ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nCSW);
  
  /**** set mode back to 0 ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->mode);

  //enable interrupt
}

/*** set modes by setting vdpMode ***/
/*** Default method per TI-VDP-Programmers_Guide.pdf ***/
inline void initVDPmode(struct s_tms9928 *p_tms9928)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  p_tms9928->register0 = (uint8_t)(0x02 & (p_tms9928->vdpMode << 1));
  
  /**** keep previous register 1 settings, only change VDP mode ****/
  p_tms9928->register1 = (uint8_t)((p_tms9928->register1 & 0xE3) | ((0x6 & p_tms9928->vdpMode) << 2));
  
  /**** setup register 0 for graphics mode I (m0 to 3 are 0) ****/
  writeVDPregister(p_tms9928, REGISTER_0, p_tms9928->register0);
  
  /**** setup regsiter 1 for graphics mode I with 8x8 sprites, irq, blank, and no magnification ****/
  writeVDPregister(p_tms9928, REGISTER_1, p_tms9928->register1);
  
  /**** setup register 2 for a name table address ****/
  writeVDPregister(p_tms9928, REGISTER_2, p_tms9928->nameTableAddr >> NAME_TABEL_ADDR_SCALE);
  
  if(p_tms9928->vdpMode == GFXII_MODE)
  {
    /**** setup register 3 for a color table address GFX II has two fixed values for its only two addresses ****/
    writeVDPregister(p_tms9928, REGISTER_3, (uint8_t)((p_tms9928->colorTableAddr == 0x0000) ? 0x7F : 0xFF));
    
    /**** setup register 4 for pattern table address GFX II has two fixed values for its only two addresses  ****/
    writeVDPregister(p_tms9928, REGISTER_4, (uint8_t)((p_tms9928->patternTableAddr == 0x0000) ? 0x03 : 0x07));
  }
  else
  {
    /**** setup register 3 for a color table address ****/
    writeVDPregister(p_tms9928, REGISTER_3, p_tms9928->colorTableAddr >> COLOR_TABEL_ADDR_SCALE);
    
    /**** setup register 4 for pattern table address  ****/
    writeVDPregister(p_tms9928, REGISTER_4, p_tms9928->patternTableAddr >> PATTERN_TABEL_ADDR_SCALE);
  }
  
  /**** setup register 5 for sprite attribute table address ****/
  writeVDPregister(p_tms9928, REGISTER_5, p_tms9928->spriteAttributeAddr >> SPRITE_ATTRIBUTE_TABEL_ADDR_SCALE);
  
  /**** setup register 6 for sprite pattern table address ****/
  writeVDPregister(p_tms9928, REGISTER_6, p_tms9928->spritePatternAddr >> SPRITE_PATTERN_TABEL_ADDR_SCALE);
  
  /**** setup register 7 for backdrop color ****/
  writeVDPregister(p_tms9928, REGISTER_7, p_tms9928->colorReg);
}

/*** reset vdp ***/
inline void resetVDP(struct s_tms9928 *p_tms9928)
{
  /**** NULL Check ****/
  if(!p_tms9928) return;
  
  //disable interrupt
  
  /**** set reset to 0 to put vdp into reset mode ****/
  setCtrlBitToZero(p_tms9928, p_tms9928->nreset);
  
  /**** delay the needed amount of time per the ti data sheet ****/
  //__delay_us(3);
  
  /**** set reset to 1 to take vdp out of reset mode ****/
  setCtrlBitToOne(p_tms9928, p_tms9928->nreset);
}

/*** set bit to one ***/
inline void setCtrlBitToOne(struct s_tms9928 *p_tms9928, uint8_t bitNum)
{
  *p_tms9928->p_ctrlPortW |= (unsigned char)(1 << bitNum);
}

/*** set bit to zero ***/
inline void setCtrlBitToZero(struct s_tms9928 *p_tms9928, uint8_t bitNum)
{
  *p_tms9928->p_ctrlPortW &= (unsigned char)~(1 << bitNum);
}
