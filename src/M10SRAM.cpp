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

#include "Arduino.h"
#include "M10SRAM.h"


//----------------------------------------------------------------------------
// SRAM_init()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      Function to initialize the onboard SRAM
//----------------------------------------------------------------------------
static void SRAM_init()
{
    uint8_t x = 1;
    
    SRAM_CSR = 1;

    single_nop_delay();

    SRAM_DATA = M23XX1024_BYTE_MODE;
    SRAM_INSTRUCTION = M23XX1024_CMD_WRMR;

    single_nop_delay();

    do {
        x = SRAM_CSR;
    } while (x & M23XX1024_BUSY_FLAG);
    
} // End of SRAM_init()

//----------------------------------------------------------------------------
// SRAM_write_byte()
//
// Parameters:
//      addr : write address
//      data : byte data to write
//
// Return Value:
//      None
//
// Remarks:
//      Function to write one byte to onboard SRAM
//----------------------------------------------------------------------------

static void SRAM_write_byte (uint32_t addr, uint8_t data) __reentrant 
{
    volatile uint8_t x;


    do {
        x = SRAM_CSR;
    } while (x & M23XX1024_BUSY_FLAG);


    SRAM_DATA = data;
    
    x = addr & 0xFF;
    SRAM_ADDRESS0 = x;

    x = (addr >> 8) & 0xFF;
    SRAM_ADDRESS1 = x;

    x = (addr >> 16) & 0xFF;
    SRAM_ADDRESS2 = x;
    
    SRAM_INSTRUCTION = M23XX1024_CMD_WRITE;

    single_nop_delay();

    
} // End of SRAM_write_byte()

//----------------------------------------------------------------------------
// SRAM_read_byte()
//
// Parameters:
//      addr : read address
//
// Return Value:
//      byte data from the onboard RAM
//
// Remarks:
//      Function to read one byte to onboard SRAM
//----------------------------------------------------------------------------

static uint8_t SRAM_read_byte (uint32_t addr)
{
    volatile uint8_t x;

    do {
        x = SRAM_CSR;
    } while (x & M23XX1024_BUSY_FLAG);
    
    x = addr & 0xFF;
    SRAM_ADDRESS0 = x;

    x = (addr >> 8) & 0xFF;
    SRAM_ADDRESS1 = x;

    x = (addr >> 16) & 0xFF;
    SRAM_ADDRESS2 = x;
    
    SRAM_INSTRUCTION = M23XX1024_CMD_READ;

    single_nop_delay();
    
    do {
        x = SRAM_CSR;
    } while (x & M23XX1024_BUSY_FLAG);
    
    single_nop_delay();
    single_nop_delay();
    single_nop_delay();
    
    x = SRAM_DATA;
    return x;
} // End of SRAM_read_byte()



//----------------------------------------------------------------------------
// constant initialization
//----------------------------------------------------------------------------

const M10SRAM_STRUCT SRAM = {SRAM_init,            // begin
                            SRAM_write_byte,      // write,
                            SRAM_read_byte        // read
};
