/*******************************************************************************
 * @file    tms9928.h
 * @brief   Library for TI video display processor.
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2022.02.12
 * @details OH SO MANY
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

#ifndef __LIB_TMS9928
#define __LIB_TMS9928

#include <xc.h>
#include <stdint.h>

/**
 * @def PATTERN_TABLE
 * pattern table start address
 */
#define PATTERN_TABLE           0x00
/**
 * @def NAME_TABLE
 * name table start address
 */
#define NAME_TABLE              0x00
/**
 * @def COLOR_TABLE
 * color table start address
 */
#define COLOR_TABLE             0x00
/**
 * @def SPRITE_ATTRIBUTE_TABLE
 * sprite attribute table start address
 */
#define SPRITE_ATTRIBUTE_TABLE  0x00
/**
 * @def SPRITE_PATTERN_TABLE
 * sprite pattern table start address
 */
#define SPRITE_PATTERN_TABLE    0x00

/**
 * @def REGISTER_0
 * register
 */
#define REGISTER_0 0
/**
 * @def REGISTER_1
 * register
 */
#define REGISTER_1 1
/**
 * @def REGISTER_2
 * register
 */
#define REGISTER_2 2
/**
 * @def REGISTER_3
 * register
 */
#define REGISTER_3 3
/**
 * @def REGISTER_4
 * register
 */
#define REGISTER_4 4
/**
 * @def REGISTER_5
 * register
 */
#define REGISTER_5 5
/**
 * @def REGISTER_6
 * register
 */
#define REGISTER_6 6
/**
 * @def REGISTER_7
 * register
 */
#define REGISTER_7 7

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

/**
 * @struct s_tms9928
 * @brief Struct for containing TMS9928 instances 
 */
struct s_tms9928
{
  /**
   * @var s_tms9928::p_dataTRIS
   * data direction port to use for changing I/O read/write setting.
   */
  volatile unsigned char *p_dataTRIS;
  /**
   * @var s_tms9928::p_dataPortW
   * data port to use for writing output data
   */
  volatile unsigned char *p_dataPortW;
  /**
   * @var s_tms9928::p_dataPortR
   * data port to use for reading input data
   */
  volatile unsigned char *p_dataPortR;
  /**
   * @var s_tms9928::p_ctrlPortW
   * port to use for control lines nCSR, nCSW, mode, nreset. Will not change other port pins.
   */
  volatile unsigned char *p_ctrlPortW;
  /**
   * @var s_tms9928::p_intPortR
   * port to use to monitor for interrupt pin
   */
  volatile unsigned char *p_intPortR;
  /**
   * @var s_tms9928::spritePatternAddr
   * sprite pattern table address in VRAM
   */
  uint16_t spritePatternAddr;
  /**
   * @var s_tms9928::spriteAttributeAddr
   * sprite attribute table address in VRAM
   */
  uint16_t spriteAttributeAddr;
  /**
   * @var s_tms9928::patternTableAddr
   * pattern table address in VRAM
   */
  uint16_t patternTableAddr;
  /**
   * @var s_tms9928::nameTableAddr
   * name table address in VRAM
   */
  uint16_t nameTableAddr;
  /**
   * @var s_tms9928::colorTableAddr
   * color table address in VRAM
   */
  uint16_t colorTableAddr;
  /**
   * @var s_tms9928::nCSR
   * active low read enable pin number
   */
  uint8_t nCSR;
  /**
   * @var s_tms9928::nCSW
   * active low write enable pin number
   */
  uint8_t nCSW;
  /**
   * @var s_tms9928::mode
   * active high chip mode pin number
   */
  uint8_t mode;
  /**
   * @var s_tms9928::nreset
   * active low chip reset pin number
   */
  uint8_t nreset;
  /**
   * @var s_tms9928::nINT
   * active low interrupt pin number
   */
  uint8_t nINT;
};

/**
 * @union u_tms9928_patternTable8x8
 * @brief Struct for containing a 8x8 pattern table
 */
union u_tms9928_patternTable8x8
{
  /**
  * @struct u_tms9928_patternTable8x8::s_pDataNibbles
  * contains color fields for bitmap mode. see page 2-22 of TMS9918 data manual.
  */
  struct s_pDataNibbles
  {
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorA
    * color
    */
    uint8_t colorA:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorB
    * color
    */
    uint8_t colorB:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorC
    * color
    */
    uint8_t colorC:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorD
    * color
    */
    uint8_t colorD:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorE
    * color
    */
    uint8_t colorE:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorF
    * color
    */
    uint8_t colorF:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorG
    * color
    */
    uint8_t colorG:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorH
    * color
    */
    uint8_t colorH:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorI
    * color
    */
    uint8_t colorI:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorJ
    * color
    */
    uint8_t colorJ:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorK
    * color
    */
    uint8_t colorK:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorL
    * color
    */
    uint8_t colorL:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorM
    * color
    */
    uint8_t colorM:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorN
    * color
    */
    uint8_t colorN:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorO
    * color
    */
    uint8_t colorO:4;
    /**
    * @var  u_tms9928_patternTable8x8::s_pDataNibbles::colorP
    * color
    */
    uint8_t colorP:4;
  } dataNibbles;
  
  /**
   * @var u_tms9928_patternTable8x8::data
   * array of 8 bytes for a 8x8 matrix.
   */
  uint8_t data[8];
};

/**
 * @struct s_tms9928_patternTable6x8
 * @brief Struct for containing a 6x8 pattern table
 */
struct s_tms9928_patternTable6x8
{
  /**
   * @var s_tms9928_patternTable6x8::data
   * array of 6 bytes for a 6x8 matrix.
   */
  uint8_t data[6];
};

/**
 * @struct s_tms9928_nameTable
 * @brief Struct for containing TMS9928 instances 
 */
struct s_tms9928_nameTable
{
  /**
   * @var s_tms9928_nameTable::data
   * byte for storing name table data.
   */
  uint8_t data;
};

/**
 * @union u_tms9928_colorTable
 * @brief Union for containing TMS9928 color table data. 
 */
union u_tms9928_colorTable
{
  /**
  * @struct u_tms9928_colorTable::s_cDataNibbles
  * contains color fields
  */
  struct s_cDataNibbles
  {
    /**
    * @var u_tms9928_colorTable::s_cDataNibbles::color1
    * top nibble, color 1
    */
    uint8_t color1:4;
    /**
    * @var u_tms9928_colorTable::s_cDataNibbles::color2
    * bottom nibble, color 2
    */
    uint8_t color2:4;
  } dataNibbles;
  
  /**
  * @var u_tms9928_colorTable::data
  * contains color data byte
  */
  uint8_t data;
};

/**
 * @struct s_tms9928_spritePatternTable8x8
 * @brief Struct for containing a 8x8 sprite pattern
 */
struct s_tms9928_spritePatternTable8x8
{
  /**
  * @var s_tms9928_spritePatternTable8x8::data
  * contains 8x8 matrix of sprite pattern data
  */
  uint8_t data[8];
};

/**
 * @struct s_tms9928_spritePatternTable16x16
 * @brief Struct for containing a 16x16 sprite pattern
 */
struct s_tms9928_spritePatternTable16x16
{
  /**
  * @var s_tms9928_spritePatternTable16x16::data
  * contains 16x16 matrix of sprite pattern data
  */
  uint16_t data[16];
};

/**
 * @union u_tms9928_spriteAttributeTable
 * @brief union for containing sprite attribute data.
 */
union u_tms9928_spriteAttributeTable
{
  /**
  * @struct u_tms9928_spriteAttributeTable::s_dataNibbles
  * contains sprite attribute fields
  */
  struct s_dataNibbles
  {
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::verticalPos
    * vertical position of sprite on screen.
    */
    uint8_t verticalPos;
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::horizontalPos
    * horizontal position of sprite on screen.
    */
    uint8_t horizontalPos;
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::name
    * name of sprite on screen (pointer to pattern table object).
    */
    uint8_t name;
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::earlyClockBit
    * feature for slow movement of sprites off screen.
    */
    uint8_t earlyClockBit:1;
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::na
    * nothing, always set to 0.
    */
    uint8_t na:3;
    /**
    * @var u_tms9928_spriteAttributeTable::s_dataNibbles::colorCode
    * color to set sprite pixels.
    */
    uint8_t colorCode:4;
  } dataNibbles;
  
  /**
  * @var u_tms9928_spriteAttributeTable::data
  * array of sprite attribute data
  */
  uint8_t data[4];
};

/***************************************************************************//**
 * @brief   Initialize TMS9928 ports for correct I/O and set pin numbers
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
void initTMS9928port(struct s_tms9928 *p_tms9928, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT);

/***************************************************************************//**
 * @brief   Initialize TMS9928 struct with ports to use for input output, must match
 * direction registers above.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vdpMode select what mode the VDP is initialized to.
 * @param   p_dataPortW pointer to data output port.
 * @param   p_dataPortR pointer to data input port.
 * @param   p_ctrlPortW pointer to control output port.
 * @param   p_intPortR pointer to interrupt input port.
 ******************************************************************************/
void initTMS9928(struct s_tms9928 *p_tms9928, uint8_t vdpMode, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR);

/***************************************************************************//**
 * @brief   Set the TMS9928 mode to one of 4. Text, Graphics I, Graphics II,
 * and bitmap.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vdpMode set or change the mode, 0 = Graphics I, 1 = Graphics II, 
 *          2 = bitmap, 3 = Text.
 ******************************************************************************/
void setTMS9928mode(struct s_tms9928 *p_tms9928, uint8_t vdpMode);

/***************************************************************************//**
 * @brief   Set a register with a 8 bit value.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   regNum which register to write to. 0 to 7.
 * @param   regData data to write to register.
 ******************************************************************************/
void setTMS9928reg(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t regData);

/***************************************************************************//**
 * @brief   Set the start of the VRAM address to read or write to. After this
 * is set read or writes will auto increment the address.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   vramAddr 14 bit address into the vram.   
 ******************************************************************************/
void setTMS9928vramAddr(struct s_tms9928 *p_tms9928, uint16_t vramAddr);

/***************************************************************************//**
 * @brief   Write a pattern or patterns into vram pattern table. Alighned to 
 * pattern data size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   startNum adds a offset to the base vram address.
 * @param   p_data data array that contains pattern data objects.
 * @param   number quantity of patterns to write linearly.
 ******************************************************************************/
void setTMS9928pattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t number);

/***************************************************************************//**
 * @brief   Write a name or names into vram name table. Aligned to name table
 * size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   startNum adds a offset to the base vram address. 
 * @param   p_data data array that contains name data objects.
 * @param   number quantity of name data to write linearly.
 ******************************************************************************/
void setTMS9928name(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t number);

/***************************************************************************//**
 * @brief   Write a color or colors into vram color table. Aligned to color table
 * size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   startNum adds a offset to the base vram address. 
 * @param   p_data data array that contains color data objects.
 * @param   number quantity of color data to write linearly.
 ******************************************************************************/
void setTMS9928color(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t number);

/***************************************************************************//**
 * @brief   Write a sprite pattern or sprite patterns into vram color table.
 * Aligned to sprite pattern table size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   startNum adds a offset to the base vram address. 
 * @param   p_data data array that contains sprite pattern data objects.
 * @param   number quantity of sprite pattern data to write linearly.
 ******************************************************************************/
void setTMS9928spritePattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t number);

/***************************************************************************//**
 * @brief   Write a sprite attribute or sprite attributes into vram color table.
 * Aligned to sprite attribute table size.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   startNum adds a offset to the base vram address. 
 * @param   p_data data array that contains sprite attribute data objects.
 * @param   number quantity of sprite attribute data to write linearly.
 ******************************************************************************/
void setTMS9928spriteAttribute(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t number);

/***************************************************************************//**
 * @brief   Write array of byte data to VRAM.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   p_data pointer to data struct contains bytes.
 * @param   size number of bytes to write to VRAM.
 ******************************************************************************/
void setTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief   Read array of byte data to VRAM.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @param   size number of bytes to read from vram.
 * @return  Array of bytes from VRAM
 ******************************************************************************/
uint8_t *getTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t size);

/***************************************************************************//**
 * @brief   Read status register of VDP.
 * 
 * @param   p_tms9928 pointer to struct to contain port data.
 * @return  Status register data byte.
 ******************************************************************************/
uint8_t *getTMS9928status(struct s_tms9928 *p_tms9928);

#endif
