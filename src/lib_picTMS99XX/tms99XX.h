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
#include <tms99XXdefines.h>
#include <tms99XXdatatypes.h>

/** METHODS **/

/***************************************************************************//**
 * @brief   Initialize TMS99XX ports for correct I/O and set pin numbers
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   p_dataTRIS pointer to data direction register.
 * @param   p_ctrlTRIS pointer to control direction register.
 * @param   p_intTRIS pointer to interrupt direction register.
 * @param   nCSR is the pin number(bit) nCSR is connected to on control port.
 * @param   nCSW is the pin number(bit) nCSW is connected to on control port.
 * @param   mode is the pin number(bit) mode is connected to on control port.
 * @param   nreset is the pin number(bit) nreset is connected to on the control port.
 * @param   nINT is the pin number(bit) interrupt output is connected to on the control port.
 ******************************************************************************/
void initTMS99XXport(struct s_tms99XX *p_tms99XX, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT);

/***************************************************************************//**
 * @brief   Initialize TMS99XX struct with ports to use for input output, must match
 * direction registers above. Register 1 has VRAM set to 16k, VDP mode set,
 * the blank enabled(0), and all other bits in there disabled state. Memory
 * addresses will match defines. These could be changed latter and then the
 * setTMS99XXmode run for custom settings on the fly. Better option is to change
 * the defines in this headed to your use case.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   vdpMode set or change the mode, 0 = Graphics I, 1 = Graphics II, 
 *          2 = bitmap, 4 = Text.
 * @param   backColor set background color to a 4 bit value.
 * @param   p_dataPortW pointer to data output port.
 * @param   p_dataPortR pointer to data input port.
 * @param   p_ctrlPortW pointer to control output port.
 * @param   p_intPortR pointer to interrupt input port.
 ******************************************************************************/
void initTMS99XX(struct s_tms99XX *p_tms99XX, uint8_t vdpMode, uint8_t backColor, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR);

/***************************************************************************//**
 * @brief   Set the TMS99XX mode to one of 4. Text, Graphics I, Graphics II,
 * and bitmap. This will also reset all addresses, and will set register 1 to
 * new specified values.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   vdpMode set or change the mode, 0 = Graphics I, 1 = Graphics II, 
 *          2 = bitmap, 4 = Text.
 * @param   register1 change contents of register one (M1/M2 will be overwritten
 *          by vdpMode). 7 = MEM, 6 = BLK DISABLE, 5 = IRQ, 1 = SPRITE SIZE, 0 = SPRITE
 *          MAGNIFICATION
 ******************************************************************************/
void setTMS99XXmode(struct s_tms99XX *p_tms99XX, uint8_t vdpMode, uint8_t register1);

/***************************************************************************//**
 * @brief   Set the TMS99XX to blank the current sprite and pattern planes.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   mode 1 is blank on, 0 is blank off
 ******************************************************************************/
void setTMS99XXblank(struct s_tms99XX *p_tms99XX, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to irq to enabled or disabled.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   mode 0 is off, anything else is on.
 ******************************************************************************/
void setTMS99XXirq(struct s_tms99XX *p_tms99XX, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to sprite size to 8x8 or 16x16.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   mode 0 is 8x8, anything else is 16x16.
 ******************************************************************************/
void setTMS99XXspriteSize(struct s_tms99XX *p_tms99XX, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX to sprite magnify to on or off (double set size).
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   mode 0 is off, anything else is double sprite size.
 ******************************************************************************/
void setTMS99XXspriteMagnify(struct s_tms99XX *p_tms99XX, uint8_t mode);

/***************************************************************************//**
 * @brief   Set the TMS99XX text color in text mode.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   color 4 bit color value.
 ******************************************************************************/
void setTMS99XXtxtColor(struct s_tms99XX *p_tms99XX, uint8_t color);

/***************************************************************************//**
 * @brief   Set the TMS99XX background color.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   color 4 bit color value.
 ******************************************************************************/
void setTMS99XXbackgroundColor(struct s_tms99XX *p_tms99XX, uint8_t color);

/***************************************************************************//**
 * @brief   Set a register with a 8 bit value.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   regNum which register to write to. 0 to 7.
 * @param   regData data to write to register.
 ******************************************************************************/
void setTMS99XXreg(struct s_tms99XX *p_tms99XX, uint8_t regNum, uint8_t regData);

/***************************************************************************//**
 * @brief   Write a pattern or patterns into vram pattern table. Alighned to 
 * pattern data size.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   tableAddr table start address, exe p_tms99XX->spriteAttributeAddr
 * @param   p_data void pointer data array that contains pattern data objects.
 * @param   startNum adds a offset to the base vram address.
 * @param   number quantity of patterns to write linearly.
 * @param   size of the data members in the table (all tables of member data, sizeof(data))
 ******************************************************************************/
void setTMS99XXvramTableData(struct s_tms99XX *p_tms99XX, uint16_t tableAddr, void *p_data, int startNum, int number, int size);

/***************************************************************************//**
 * @brief   Set the start of the VRAM address to write to. After this
 * is set writes will auto increment the address.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   vramAddr 14 bit address into the vram.   
 ******************************************************************************/
void setTMS99XXvramWriteAddr(struct s_tms99XX *p_tms99XX, uint16_t vramAddr);

/***************************************************************************//**
 * @brief   Set the start of the VRAM address to read to. After this
 * is set read will auto increment the address.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   vramAddr 14 bit address into the vram.   
 ******************************************************************************/
void setTMS99XXvramReadAddr(struct s_tms99XX *p_tms99XX, uint16_t vramAddr);

/***************************************************************************//**
 * @brief   Write array of byte data to VRAM.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   p_data pointer to data to write to vdp.
 * @param   size number of bytes to write to VRAM.
 ******************************************************************************/
void setTMS99XXvramData(struct s_tms99XX *p_tms99XX, void *p_data, int size);

/***************************************************************************//**
 * @brief   Set all data in VRAM to a constant value of some size.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   data the constant to write.
 * @param   size number of bytes to set.
 ******************************************************************************/
void setTMS99XXvramConstData(struct s_tms99XX *p_tms99XX, uint8_t data, int size);

/***************************************************************************//**
 * @brief   Read array of byte data to VRAM.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @param   p_data pointer to data to store read data.
 * @param   size number of bytes to read from vram.
 ******************************************************************************/
void getTMS99XXvramData(struct s_tms99XX *p_tms99XX, void *p_data, int size);

/***************************************************************************//**
 * @brief   Read status register of VDP.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @return  Status register data byte.
 ******************************************************************************/
uint8_t getTMS99XXstatus(struct s_tms99XX *p_tms99XX);

/***************************************************************************//**
 * @brief   Clear all data from VRAM from 0x0000 to 0x3FFF.
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 ******************************************************************************/
void clearTMS99XXvramData(struct s_tms99XX *p_tms99XX);

/***************************************************************************//**
 * @brief   Test all VRAM
 * 
 * @param   p_tms99XX pointer to struct to contain port data.
 * @return  0 for error, 1 for pass.
 ******************************************************************************/
uint8_t checkTMS99XXvram(struct s_tms99XX *p_tms99XX);

#endif
