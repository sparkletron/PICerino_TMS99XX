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

// __DELAY_READY define, MUST USE __XTAL_FREQ define as well in this header.
// #define __DELAY_READY
// #define __XTAL_FREQ

/**
 * @def __LOOP_READY
 * Use loop check of ready, default method. Its a bit slow, and has issues
 * with setting data multiple times.
 */
// #define __LOOP_READY
// DEFINE DATA ADDRESS LOCATIONS
// DEFINE DATA REGISTERS

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
 * @param   vpdMode select what mode the VDP is initialized to.
 * @param   p_dataPortW pointer to data output port.
 * @param   p_dataPortR pointer to data input port.
 * @param   p_ctrlPortW pointer to control output port.
 * @param   p_intPortR pointer to interrupt input port.
 ******************************************************************************/
void initTMS9928(struct s_tms9928 *p_tms9928, uint8_t vdpMode, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928mode(struct s_tms9928 *p_tms9928, uint8_t vdpMode);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928reg(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t regData);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928vramAddr(struct s_tms9928 *p_tms9928, uint16_t vramAddr);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928pattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928name(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928color(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928spritePattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928spriteAttribute(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
void setTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t *p_data, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
uint8_t *getTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t size);

/***************************************************************************//**
 * @brief
 * 
 * @param
 ******************************************************************************/
uint8_t *getTMS9928status(struct s_tms9928 *p_tms9928);

#endif
