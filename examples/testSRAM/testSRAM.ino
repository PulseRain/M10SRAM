/*
###############################################################################
# Copyright (c) 2016, PulseRain Technology LLC 
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

#include <M10SRAM.h>

//============================================================================
// Example:
//     simple memory r/w test
//============================================================================

void setup()
{
   delay(1000);
   
   Serial.begin(115200);
   SRAM.begin();
} // End of setup()


void loop()
{
   static uint32_t mem_addr = 0x10000;
   uint8_t t, i;
   uint8_t mismatch;


   for ( i = 0; i < 128; ++i) {
      SRAM.write (mem_addr + i, i + 2);
   } // End of for loop

  
   
   mismatch = 0;
   for ( i = 0; i < 128; ++i) {
      t = SRAM.read (mem_addr + i);
      if (t != (i + 2)) {
        mismatch = 1;
      }
   } // End of for loop

   Serial.write ("addr= 0x");
   Serial.print (mem_addr, HEX);
   if (mismatch) {
      Serial.write (" mismatch!!!!!!\n");
      while(1);
   } else {
      Serial.write (" match!\n");
   }
   
   if (mem_addr < ((uint32_t)128*1024 - 128)) {
      mem_addr += 128;
   } else {
      mem_addr = 0;
   }

   delay (500);
   
} // End of loop()
