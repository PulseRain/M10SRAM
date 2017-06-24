/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#ifndef M10SRAM_H

#include "Arduino.h"

//=======================================================================
// M23XX1024 Library
//=======================================================================
#define M23XX1024_BYTE_MODE  0x0
#define M23XX1024_PAGE_MODE  0x80
#define M23XX1024_SEQ_MODE   0x40


#define M23XX1024_CMD_READ   0x03
#define M23XX1024_CMD_WRITE  0x02
#define M23XX1024_CMD_RDMR   0x05
#define M23XX1024_CMD_WRMR   0x01

#define M23XX1024_WR_BUSY_FLAG       0x2
#define M23XX1024_RD_DATA_AVAIL_FLAG 0x4
#define M23XX1024_BUSY_FLAG          0x8

#define M23XX1024_MEM_SIZE           (131072)


typedef struct {
  void (*begin)();
  void (*_write)(uint32_t addr, uint8_t data) __reentrant;
  uint8_t (*read) (uint32_t addr);
} M10SRAM_STRUCT;

extern const M10SRAM_STRUCT SRAM;

#endif
