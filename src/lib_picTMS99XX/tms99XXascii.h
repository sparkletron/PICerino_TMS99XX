/*******************************************************************************
 * @file    tms99XXascii.h
 * @brief   ASCII for TI TMS9918/28/29 video display processor library.
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2022.04.24
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

#ifndef __LIB_TMS99XX_ASCII
#define __LIB_TMS99XX_ASCII

#include <tms99XXdatatypes.h>

/** From TMS9918 datasheet **/
/** Fixed a few bugs, duplicate > and bad lower case letters **/
/** Added nulls for first 32 to pad out struct, easier to just create strings and go. **/
const union u_tms99XX_patternTable8x8 c_tms99XX_ascii[] = 
{
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, // null
  { .data = {0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00}}, // !
  { .data = {0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}}, // "
  { .data = {0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00}}, // #
  { .data = {0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, 0x00}}, // $
  { .data = {0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18, 0x00}}, // %
  { .data = {0x40, 0xA0, 0xA0, 0x40, 0xA8, 0x90, 0x68, 0x00}}, // &
  { .data = {0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00}}, // '
  { .data = {0x20, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, 0x00}}, // (
  { .data = {0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00}}, // )
  { .data = {0x20, 0xA8, 0x70, 0x20, 0x70, 0xA8, 0x20, 0x00}}, // *
  { .data = {0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00}}, // +
  { .data = {0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00}}, // ,
  { .data = {0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00}}, // -
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00}}, // .
  { .data = {0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00}}, // /
  { .data = {0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, 0x00}}, // 0
  { .data = {0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}}, // 1
  { .data = {0x70, 0x88, 0x08, 0x30, 0x40, 0x80, 0xF8, 0x00}}, // 2
  { .data = {0xF8, 0x08, 0x10, 0x30, 0x08, 0x88, 0x70, 0x00}}, // 3
  { .data = {0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, 0x00}}, // 4
  { .data = {0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, 0x00}}, // 5
  { .data = {0x38, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, 0x00}}, // 6
  { .data = {0xF8, 0x80, 0x10, 0x20, 0x40, 0x40, 0x40, 0x00}}, // 7
  { .data = {0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00}}, // 8
  { .data = {0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0xE0, 0x00}}, // 9
  { .data = {0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00}}, // :
  { .data = {0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x40, 0x00}}, // ;
  { .data = {0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00}}, // <
  { .data = {0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00}}, // =
  { .data = {0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x00}}, // >
  { .data = {0x70, 0x88, 0x10, 0x20, 0x20, 0x00, 0x20, 0x00}}, // ?
  { .data = {0x70, 0x88, 0xA8, 0xB8, 0x80, 0x80, 0x78, 0x00}}, // @
  { .data = {0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00}}, // A
  { .data = {0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00}}, // B
  { .data = {0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00}}, // C
  { .data = {0xF0, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF0, 0x00}}, // D
  { .data = {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00}}, // E
  { .data = {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x00}}, // F
  { .data = {0x78, 0x80, 0x80, 0x80, 0x98, 0x88, 0x78, 0x00}}, // G
  { .data = {0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00}}, // H
  { .data = {0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}}, // I
  { .data = {0x08, 0x08, 0x08, 0x08, 0x08, 0x88, 0x70, 0x00}}, // J
  { .data = {0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00}}, // K
  { .data = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00}}, // L
  { .data = {0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88, 0x00}}, // M
  { .data = {0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00}}, // N
  { .data = {0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00}}, // O
  { .data = {0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00}}, // P
  { .data = {0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, 0x00}}, // Q
  { .data = {0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00}}, // R
  { .data = {0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00}}, // S
  { .data = {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}}, // T
  { .data = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00}}, // U
  { .data = {0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00}}, // V
  { .data = {0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88, 0x00}}, // W
  { .data = {0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00}}, // X
  { .data = {0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00}}, // Y
  { .data = {0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00}}, // Z
  { .data = {0xF8, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xF8, 0x00}}, // [
  { .data = {0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00}}, // backslash
  { .data = {0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0x00}}, // ]
  { .data = {0x00, 0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00}}, // ^
  { .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8}}, // _
  { .data = {0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00}}, // `
  { .data = {0x00, 0x00, 0x70, 0x88, 0xF8, 0x88, 0x88, 0x00}}, // a
  { .data = {0x00, 0x00, 0xF0, 0x48, 0x70, 0x48, 0xF0, 0x00}}, // b
  { .data = {0x00, 0x00, 0x78, 0x80, 0x80, 0x80, 0x78, 0x00}}, // c
  { .data = {0x00, 0x00, 0xF0, 0x48, 0x48, 0x48, 0xF0, 0x00}}, // d
  { .data = {0x00, 0x00, 0xF0, 0x80, 0xE0, 0x80, 0xF0, 0x00}}, // e
  { .data = {0x00, 0x00, 0xF0, 0x80, 0xE0, 0x80, 0x80, 0x00}}, // f
  { .data = {0x00, 0x00, 0x78, 0x80, 0xB8, 0x88, 0x70, 0x00}}, // g
  { .data = {0x00, 0x00, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00}}, // h
  { .data = {0x00, 0x00, 0xF8, 0x20, 0x20, 0x20, 0xF8, 0x00}}, // i
  { .data = {0x00, 0x00, 0x70, 0x20, 0x20, 0xA0, 0xE0, 0x00}}, // j
  { .data = {0x00, 0x00, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x00}}, // k
  { .data = {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00}}, // l
  { .data = {0x00, 0x00, 0x88, 0xD8, 0xA8, 0x88, 0x88, 0x00}}, // m
  { .data = {0x00, 0x00, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x00}}, // n
  { .data = {0x00, 0x00, 0xF8, 0x88, 0x88, 0x88, 0xF8, 0x00}}, // o
  { .data = {0x00, 0x00, 0xF0, 0x88, 0xF0, 0x80, 0x80, 0x00}}, // p
  { .data = {0x00, 0x00, 0xF8, 0x88, 0xA8, 0x90, 0xE8, 0x00}}, // q
  { .data = {0x00, 0x00, 0xF8, 0x88, 0xF8, 0xA0, 0x90, 0x00}}, // r
  { .data = {0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00}}, // s
  { .data = {0x00, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00}}, // t
  { .data = {0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00}}, // u
  { .data = {0x00, 0x00, 0x88, 0x88, 0x90, 0xA0, 0x40, 0x00}}, // v
  { .data = {0x00, 0x00, 0x88, 0x88, 0xA8, 0xD8, 0x88, 0x00}}, // w
  { .data = {0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00}}, // x
  { .data = {0x00, 0x00, 0x88, 0x50, 0x20, 0x20, 0x20, 0x00}}, // y
  { .data = {0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00}}, // z
  { .data = {0x38, 0x40, 0x20, 0xC0, 0x20, 0x40, 0x38, 0x00}}, // {
  { .data = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}}, // |
  { .data = {0xE0, 0x10, 0x20, 0x18, 0x20, 0x10, 0xE0, 0x00}}, // }
  { .data = {0x40, 0xA8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00}}, // ~
  { .data = {0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x00}}  // DEL
};

#endif
