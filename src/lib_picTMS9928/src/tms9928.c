/*******************************************************************************
 * @file    tms9928.c
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2022.02.12
 * @brief   Library for tms9928 sound chip.
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

/** DEFINES **/
#define VOICE1_FREQ 0
#define VOICE2_FREQ 2
#define VOICE3_FREQ 1
#define VOICE1_ATTN 4
#define VOICE2_ATTN 6
#define VOICE3_ATTN 5
#define NOISE_CTRL  3
#define NOISE_ATTN  7
#define FIRST_BYTE  0x01
#define SECOND_BYTE 0x00
#define REG_SHIFT   1

/** SEE MY PRIVATES **/
uint8_t readVDPstatus(struct s_tms9928 *p_tms9928);
uint8_t readVDPvram(struct s_tms9928 *p_tms9928);
void writeVDPvram(struct s_tms9928 *p_tms9928, uint8_t data);
void writeVDPregister(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t data);
void initVDPgfxI(struct s_tms9928 *p_tms9928);
void initVDPgfxII(struct s_tms9928 *p_tms9928);
void initVDPbmp(struct s_tms9928 *p_tms9928);
void initVDPtxt(struct s_tms9928 *p_tms9928);
void resetVDP(struct s_tms9928 *p_tms9928);

/** INITIALIZE AND FREE MY STRUCTS **/

/*** Initialize TMS9928 ports for correct I/O and set pin numbers ***/
void initTMS9928port(struct s_tms9928 *p_tms9928, volatile unsigned char *p_dataTRIS, volatile unsigned char *p_ctrlTRIS, volatile unsigned char *p_intTRIS, uint8_t nCSR, uint8_t nCSW, uint8_t mode, uint8_t nreset, uint8_t nINT)
{
}

/*** Initialize TMS9928 struct with ports to use for input output, must match direction registers above. ***/
void initTMS9928(struct s_tms9928 *p_tms9928, uint8_t vdpMode, volatile unsigned char *p_dataPortW, volatile unsigned char *p_dataPortR, volatile unsigned char *p_ctrlPortW, volatile unsigned char *p_intPortR)
{
}

void setTMS9928mode(struct s_tms9928 *p_tms9928, uint8_t vdpMode)
{
}

void setTMS9928reg(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t regData)
{
}

void setTMS9928vramAddr(struct s_tms9928 *p_tms9928, uint16_t vramAddr)
{
}

void setTMS9928pattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size)
{
}

void setTMS9928name(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size)
{
}

void setTMS9928color(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size)
{
}

void setTMS9928spritePattern(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size)
{
}

void setTMS9928spriteAttribute(struct s_tms9928 *p_tms9928, uint8_t startNum, uint8_t *p_data, uint8_t size)
{
}

void setTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t *p_data, uint8_t size)
{
}

uint8_t *getTMS9928vramData(struct s_tms9928 *p_tms9928, uint8_t size)
{
}

uint8_t *getTMS9928status(struct s_tms9928 *p_tms9928)
{
}

/** SEE MY PRIVATES **/
uint8_t readVDPstatus(struct s_tms9928 *p_tms9928)
{
}


uint8_t readVDPvram(struct s_tms9928 *p_tms9928)
{
}

void writeVDPvram(struct s_tms9928 *p_tms9928, uint8_t data)
{
}

void writeVDPregister(struct s_tms9928 *p_tms9928, uint8_t regNum, uint8_t data)
{
}

void initVDPgfxI(struct s_tms9928 *p_tms9928)
{
}

void initVDPgfxII(struct s_tms9928 *p_tms9928)
{
}

void initVDPbmp(struct s_tms9928 *p_tms9928)
{
}

void initVDPtxt(struct s_tms9928 *p_tms9928)
{
}

void resetVDP(struct s_tms9928 *p_tms9928)
{
}
