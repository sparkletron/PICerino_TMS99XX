/*******************************************************************************
 * @file    tms99XX.h
 * @brief   Library for TI TMS9918/28/29 video display processor.
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
 * @version 0.0.1
 * 
 * @TODO
 *  - EVERYTHING
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

#ifndef __LIB_TMS99XX
#define __LIB_TMS99XX

#include <xc.h>
#include <stdint.h>

/** DEFINES **/
/** VDP MODE DEFINES **/
/**
 * @def GFXI_MODE
 * mode bit for graphics I mode
 */
#define GFXI_MODE 0
/**
 * @def GFXII_MODE
 * mode bit for graphics II mode
 */
#define GFXII_MODE 1
/**
 * @def BMP_MODE
 * mode bit for bitmap(multicolor) mode
 */
#define BMP_MODE 2
/**
 * @def TXT_MODE
 * mode bit for text mode
 */
#define TXT_MODE 4

/** register 1 bit defines **/
/**
 * @def MEM_AMT_BIT
 * amount of memory bit
 */
#define MEM_AMT_BIT 7
/**
 * @def BLK_SCRN_BIT
 * blank screen bit
 */
#define BLK_SCRN_BIT 6
/**
 * @def IRQ_BIT
 * IRQ bit number
 */
#define IRQ_BIT 5
/**
 * @def SPRITE_SIZE_BIT
 * sprite size bit
 */
#define SPRITE_SIZE_BIT 1
/**
 * @def SPRITE_MAG_BIT
 * sprite magnification bit
 */
#define SPRITE_MAG_BIT 0

/** REGISTER DEFINES **/
/**
 * @def REGISTER_0
 * mode and external video bits
 */
#define REGISTER_0 0
/**
 * @def REGISTER_1
 * mode, sprite, interrupt, blank, and memory bits.
 */
#define REGISTER_1 1
/**
 * @def REGISTER_2
 * name table address
 */
#define REGISTER_2 2
/**
 * @def REGISTER_3
 * color table address
 */
#define REGISTER_3 3
/**
 * @def REGISTER_4
 * pattern table address
 */
#define REGISTER_4 4
/**
 * @def REGISTER_5
 * sprite attribute address
 */
#define REGISTER_5 5
/**
 * @def REGISTER_6
 * sprite pattern address
 */
#define REGISTER_6 6
/**
 * @def REGISTER_7
 * background, text color
 */
#define REGISTER_7 7

/** VRAM ADDRESS DEFINES **/
/**
 * @def NAME_TABLE_ADDR
 * default address for name table (R2 * 0x400[2^10])
 * 0x3800 address is set when R2 is 0x0E
 */
#define NAME_TABLE_ADDR 0x3800
/**
 * @def NAME_TABLE_ADDR_SCALE
 * value to scale the name table address
 */
#define NAME_TABLE_ADDR_SCALE 10
/**
 * @def COLOR_TABLE_ADDR
 * default address for color table (R3 * 0x40[2^6])
 * 0x2000 address is set when R3 is 0x80 (GFXII constrains this to FF!!)
 */
#define COLOR_TABLE_ADDR 0x2000
/**
 * @def COLOR_TABLE_ADDR_SCALE
 * value to scale the color table address
 */
#define COLOR_TABLE_ADDR_SCALE 6
/**
 * @def PATTERN_TABLE_ADDR
 * default address for pattern table (R4 * 0x800[2^11])
 * 0x0000 address is set when R4 is 0x00 (GFX constrains this to 0x03)
 */
#define PATTERN_TABLE_ADDR 0x0000
/**
 * @def PATTERN_TABLE_ADDR_SCALE
 * value to scale the pattern table address
 */
#define PATTERN_TABLE_ADDR_SCALE 11
/**
 * @def SPRITE_ATTRIBUTE_TABLE_ADDR
 * default address for sprite attribute table (R5 * 0x80[2^7])
 * 0x3B00 address is set when R5 is 0x76
 */
#define SPRITE_ATTRIBUTE_TABLE_ADDR 0x3B00
/**
 * @def SPRITE_ATTRIBUTE_TABLE_ADDR_SCALE
 * value to scale the sprite attribute address
 */
#define SPRITE_ATTRIBUTE_TABLE_ADDR_SCALE 7
/**
 * @def SPRITE_PATTERN_TABLE_ADDR
 * default address for sprite pattern table (R6 * 0x800[2^11])
 * 0x1800 address is set when R6 is 0x03
 */
#define SPRITE_PATTERN_TABLE_ADDR 0x1800
/**
 * @def SPRITE_PATTERN_TABLE_ADDR_SCALE
 * value to scale the sprite attribute address
 */
#define SPRITE_PATTERN_TABLE_ADDR_SCALE 11

/** COLOR DEFINES **/
/**
 * @def TMS_TRANSPARENT
 * transparent for all plans/sprites
 */
#define TMS_TRANSPARENT 0x0
/**
 * @def TMS_BLACK
 * color black
 */
#define TMS_BLACK 0x1
/**
 * @def TMS_MEDIUM_GREEN
 * color medium green
 */
#define TMS_MEDIUM_GREEN 0x2
/**
 * @def TMS_LIGHT_GREEN
 * color light green
 */
#define TMS_LIGHT_GREEN 0x3
/**
 * @def TMS_DARK_BLUE
 * color dark blue
 */
#define TMS_DARK_BLUE 0x4
/**
 * @def TMS_LIGHT_BLUE
 * color light blue
 */
#define TMS_LIGHT_BLUE 0x5
/**
 * @def TMS_DARK_RED
 * color dark red
 */
#define TMS_DARK_RED 0x6
/**
 * @def TMS_CYAN
 * color cyan
 */
#define TMS_CYAN 7
/**
 * @def TMS_MEDIUM_RED
 * color medium red
 */
#define TMS_MEDIUM_RED 0x8
/**
 * @def TMS_LIGHT_RED
 * register
 */
#define TMS_LIGHT_RED 0x9
/**
 * @def TMS_DARK_YELLOW 
 * register
 */
#define TMS_DARK_YELLOW 0xA
/**
 * @def TMS_LIGHT_YELLOW
 * register
 */
#define TMS_LIGHT_YELLOW 0xB
/**
 * @def TMS_DARK_GREEN
 * register
 */
#define TMS_DARK_GREEN 0xC
/**
 * @def TMS_MAGENTA
 * register
 */
#define TMS_MAGENTA 0xD
/**
 * @def TMS_GREY
 * register
 */
#define TMS_GREY 0xE
/**
 * @def TMS_WHITE
 * register
 */
#define TMS_WHITE 0xF

/** MISC DEFINES **/
/**
 * @def MEM_SIZE
 * 16K of memory 
 */
#define MEM_SIZE (1 << 14)

/** DATA STRUCTURES **/
/**
 * @struct s_tms99XX
 * @brief Struct for containing TMS99XX instances 
 */
struct s_tms99XX
{
  /**
   * @var s_tms99XX::p_dataTRIS
   * data direction port to use for changing I/O read/write setting.
   */
  volatile unsigned char *p_dataTRIS;
  /**
   * @var s_tms99XX::p_dataPortW
   * data port to use for writing output data
   */
  volatile unsigned char *p_dataPortW;
  /**
   * @var s_tms99XX::p_dataPortR
   * data port to use for reading input data
   */
  volatile unsigned char *p_dataPortR;
  /**
   * @var s_tms99XX::p_ctrlPortW
   * port to use for control lines nCSR, nCSW, mode, nreset. Will not change other port pins.
   */
  volatile unsigned char *p_ctrlPortW;
  /**
   * @var s_tms99XX::p_intPortR
   * port to use to monitor for interrupt pin
   */
  volatile unsigned char *p_intPortR;
  /**
   * @var s_tms99XX::spritePatternAddr
   * sprite pattern table address in VRAM
   */
  uint16_t spritePatternAddr;
  /**
   * @var s_tms99XX::spriteAttributeAddr
   * sprite attribute table address in VRAM
   */
  uint16_t spriteAttributeAddr;
  /**
   * @var s_tms99XX::patternTableAddr
   * pattern table address in VRAM
   */
  uint16_t patternTableAddr;
  /**
   * @var s_tms99XX::nameTableAddr
   * name table address in VRAM
   */
  uint16_t nameTableAddr;
  /**
   * @var s_tms99XX::colorTableAddr
   * color table address in VRAM
   */
  uint16_t colorTableAddr;
    /**
   * @var s_tms99XX::vdpMode
   * contains current mode of the VDP
   */
  uint8_t vdpMode;
  /**
   * @var s_tms99XX::register0
   * register 0 contents
   */
  uint8_t register0;
  /**
   * @var s_tms99XX::register1
   * register 1 contents
   */
  uint8_t register1;
  /**
   * @var s_tms99XX::colorReg
   * color sent to register 7, background/text color.
   */
  uint8_t colorReg;
  /**
   * @var s_tms99XX::nCSR
   * active low read enable pin number
   */
  uint8_t nCSR;
  /**
   * @var s_tms99XX::nCSW
   * active low write enable pin number
   */
  uint8_t nCSW;
  /**
   * @var s_tms99XX::mode
   * active high chip mode pin number
   */
  uint8_t mode;
  /**
   * @var s_tms99XX::nreset
   * active low chip reset pin number
   */
  uint8_t nreset;
  /**
   * @var s_tms99XX::nINT
   * active low interrupt pin number
   */
  uint8_t nINT;
};

/**
 * @union u_tms99XX_patternTable8x8
 * @brief Struct for containing a 8x8 pattern table
 */
union u_tms99XX_patternTable8x8
{
  /**
  * @struct u_tms99XX_patternTable8x8::s_pDataNibbles
  * contains color fields for bitmap mode. see page 2-22 of TMS9918 data manual.
  */
  struct s_pDataNibbles
  {
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorA
    * color
    */
    uint8_t colorA:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorB
    * color
    */
    uint8_t colorB:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorC
    * color
    */
    uint8_t colorC:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorD
    * color
    */
    uint8_t colorD:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorE
    * color
    */
    uint8_t colorE:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorF
    * color
    */
    uint8_t colorF:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorG
    * color
    */
    uint8_t colorG:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorH
    * color
    */
    uint8_t colorH:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorI
    * color
    */
    uint8_t colorI:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorJ
    * color
    */
    uint8_t colorJ:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorK
    * color
    */
    uint8_t colorK:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorL
    * color
    */
    uint8_t colorL:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorM
    * color
    */
    uint8_t colorM:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorN
    * color
    */
    uint8_t colorN:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorO
    * color
    */
    uint8_t colorO:4;
    /**
    * @var  u_tms99XX_patternTable8x8::s_pDataNibbles::colorP
    * color
    */
    uint8_t colorP:4;
  } dataNibbles;
  
  /**
   * @var u_tms99XX_patternTable8x8::data
   * array of 8 bytes for a 8x8 matrix.
   */
  uint8_t data[8];
};

/**
 * @struct s_tms99XX_patternTable6x8
 * @brief Struct for containing a 6x8 pattern table
 */
struct s_tms99XX_patternTable6x8
{
  /**
   * @var s_tms99XX_patternTable6x8::data
   * array of 8 bytes for a 6x8 matrix. (2 bits ignored)
   */
  uint8_t data[8];
};

/**
 * @struct s_tms99XX_nameTable
 * @brief Struct for containing TMS99XX instances 
 */
struct s_tms99XX_nameTable
{
  /**
   * @var s_tms99XX_nameTable::data
   * byte for storing name table data.
   */
  uint8_t data;
};

/**
 * @union u_tms99XX_colorTable
 * @brief Union for containing TMS99XX color table data. 
 */
union u_tms99XX_colorTable
{
  /**
  * @struct u_tms99XX_colorTable::s_cDataNibbles
  * contains color fields
  */
  struct s_cDataNibbles
  {
    /**
    * @var u_tms99XX_colorTable::s_cDataNibbles::color1
    * top nibble, color 1
    */
    uint8_t color1:4;
    /**
    * @var u_tms99XX_colorTable::s_cDataNibbles::color2
    * bottom nibble, color 2
    */
    uint8_t color2:4;
  } dataNibbles;
  
  /**
  * @var u_tms99XX_colorTable::data
  * contains color data byte
  */
  uint8_t data;
};

/**
 * @struct s_tms99XX_spritePatternTable8x8
 * @brief Struct for containing a 8x8 sprite pattern
 */
struct s_tms99XX_spritePatternTable8x8
{
  /**
  * @var s_tms99XX_spritePatternTable8x8::data
  * contains 8x8 matrix of sprite pattern data
  */
  uint8_t data[8];
};

/**
 * @struct s_tms99XX_spritePatternTable16x16
 * @brief Struct for containing a 16x16 sprite pattern
 */
struct s_tms99XX_spritePatternTable16x16
{
  /**
  * @var s_tms99XX_spritePatternTable16x16::data
  * contains 16x16 matrix of sprite pattern data
  */
  uint16_t data[16];
};

/**
 * @union u_tms99XX_spriteAttributeTable
 * @brief union for containing sprite attribute data.
 */
union u_tms99XX_spriteAttributeTable
{
  /**
  * @struct u_tms99XX_spriteAttributeTable::s_dataNibbles
  * contains sprite attribute fields
  */
  struct s_dataNibbles
  {
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::verticalPos
    * vertical position of sprite on screen.
    */
    uint8_t verticalPos;
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::horizontalPos
    * horizontal position of sprite on screen.
    */
    uint8_t horizontalPos;
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::name
    * name of sprite on screen (pointer to pattern table object).
    */
    uint8_t name;
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::earlyClockBit
    * feature for slow movement of sprites off screen.
    */
    uint8_t earlyClockBit:1;
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::na
    * nothing, always set to 0.
    */
    uint8_t na:3;
    /**
    * @var u_tms99XX_spriteAttributeTable::s_dataNibbles::colorCode
    * color to set sprite pixels.
    */
    uint8_t colorCode:4;
  } dataNibbles;
  
  /**
  * @var u_tms99XX_spriteAttributeTable::data
  * array of sprite attribute data
  */
  uint8_t data[4];
};

/** METHODS **/

/***************************************************************************//**
 * @brief   Initialize TMS99XX ports for correct I/O and set pin numbers
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   p_dataTRIS pointer to data direction register.
 * @param   p_ctrlTRIS pointer to control direction register.
 * @param   p_intTRIS pointer to interrupt direction register.
 * @param   nCSR is the pin number(bit) nCSR is connected to on control port.
 * @param   nCSW is the pin number(bit) nCSW is connected to on control port.
 * @param   mode is the pin number(bit) mode is connected to on control port.
 * @param   nreset is the pin number(bit) nreset is connected to on the control port.
 * @param   nINT is the pin number(bit) interrupt output is connected to on the control port.
 ******************************************************************************/
void initTMS99XXport(struct s_tms99XX *p_tms9928, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT);

/***************************************************************************//**
 * @brief   Initialize TMS99XX struct with ports to use for input output, must match
 * direction registers above. Register 1 can be set to any default values. Memory
 * addresses will match defines. These could be changed latter and then the
 * setTMS99XXmode run for custom settings on the fly. Better option is to change
 * the defines in this headed to your use case.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vdpMode set or change the mode, 0 = Graphics I, 1 = Graphics II, 
 *          2 = bitmap, 4 = Text.
 * @param   register1 change contents of register one (M1/M2 will be overwritten
 *          by vdpMode). 7 = MEM, 6 = BLK DISABLE, 5 = IRQ, 1 = SPRITE SIZE, 0 = SPRITE
 *          MAGNIFICATION
 * @param   txtColor set text color to a 4 bit value.
 * @param   backColor set background color to a 4 bit value.
 * @param   p_dataPortW pointer to data output port.
 * @param   p_dataPortR pointer to data input port.
 * @param   p_ctrlPortW pointer to control output port.
 * @param   p_intPortR pointer to interrupt input port.
 ******************************************************************************/
void initTMS99XX(struct s_tms99XX *p_tms9928, uint8_t vdpMode, uint8_t register1, uint8_t txtColor, uint8_t backColor, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR);

/***************************************************************************//**
 * @brief   Set the TMS99XX mode to one of 4. Text, Graphics I, Graphics II,
 * and bitmap. This will also reset all addresses, and will set register 1 to
 * new specified values.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vdpMode set or change the mode, 0 = Graphics I, 1 = Graphics II, 
 *          2 = bitmap, 4 = Text.
 * @param   register1 change contents of register one (M1/M2 will be overwritten
 *          by vdpMode). 7 = MEM, 6 = BLK DISABLE, 5 = IRQ, 1 = SPRITE SIZE, 0 = SPRITE
 *          MAGNIFICATION
 ******************************************************************************/
void setTMS99XXmode(struct s_tms99XX *p_tms9928, uint8_t vdpMode, uint8_t register1);

/***************************************************************************//**
 * @brief   Set the TMS99XX to blank the current sprite and pattern planes.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   mode 1 is blank on, 0 is blank off
 ******************************************************************************/
void setTMS99XXblank(struct s_tms99XX *p_tms9928, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to irq to enabled or disabled.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   mode 0 is off, anything else is on.
 ******************************************************************************/
void setTMS99XXirq(struct s_tms99XX *p_tms9928, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to sprite size to 8x8 or 16x16.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   mode 0 is 8x8, anything else is 16x16.
 ******************************************************************************/
void setTMS99XXspriteSize(struct s_tms99XX *p_tms9928, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to sprite magnify to on or off (double set size).
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   mode 0 is off, anything else is double sprite size.
 ******************************************************************************/
void setTMS99XXspriteMagnify(struct s_tms99XX *p_tms9928, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX text color in text mode.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   color 4 bit color value.
 ******************************************************************************/
void setTMS99XXtxtColor(struct s_tms99XX *p_tms9928, uint8_t color);

/***************************************************************************//**
 * @brief   Set the TMS99XX background color.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   color 4 bit color value.
 ******************************************************************************/
void setTMS99XXbackgroundColor(struct s_tms99XX *p_tms9928, uint8_t color);

/***************************************************************************//**
 * @brief   Set a register with a 8 bit value.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   regNum which register to write to. 0 to 7.
 * @param   regData data to write to register.
 ******************************************************************************/
void setTMS99XXreg(struct s_tms99XX *p_tms9928, uint8_t regNum, uint8_t regData);

/***************************************************************************//**
 * @brief   Write a pattern or patterns into vram pattern table. Alighned to 
 * pattern data size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   tableAddr table start address, exe p_tms9928->spriteAttributeAddr
 * @param   p_data void pointer data array that contains pattern data objects.
 * @param   startNum adds a offset to the base vram address.
 * @param   number quantity of patterns to write linearly.
 * @param   size of the data members in the table (all tables of member data, sizeof(data))
 ******************************************************************************/
void setTMS99XXvramTableData(struct s_tms99XX *p_tms9928, uint16_t tableAddr, void *p_data, uint8_t startNum, uint8_t number, uint8_t size);

/***************************************************************************//**
 * @brief   Set the start of the VRAM address to read or write to. After this
 * is set read or writes will auto increment the address.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vramAddr 14 bit address into the vram.   
 ******************************************************************************/
void setTMS99XXvramAddr(struct s_tms99XX *p_tms9928, uint16_t vramAddr);

/***************************************************************************//**
 * @brief   Write array of byte data to VRAM.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   p_data pointer to data to write to vdp.
 * @param   size number of bytes to write to VRAM.
 ******************************************************************************/
void setTMS99XXvramData(struct s_tms99XX *p_tms9928, void *p_data, int size);

/***************************************************************************//**
 * @brief   Read array of byte data to VRAM.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   p_data pointer to data to store read data.
 * @param   size number of bytes to read from vram.
 ******************************************************************************/
void getTMS99XXvramData(struct s_tms99XX *p_tms9928, void *p_data, int size);

/***************************************************************************//**
 * @brief   Read status register of VDP.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @return  Status register data byte.
 ******************************************************************************/
uint8_t getTMS99XXstatus(struct s_tms99XX *p_tms9928);

/***************************************************************************//**
 * @brief   Clear all data from VRAM from current address to size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   size number of bytes to clear.
 ******************************************************************************/
void clearTMS99XXvramData(struct s_tms99XX *p_tms9928, int size);

#endif
