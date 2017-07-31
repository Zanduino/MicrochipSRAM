/*******************************************************************************************************************
** MicrochipSRAM class method definitions. Most of the actual work is defined in templates found in the header,   **
** but there is one method, clearMemory(), which is defined in this file apart from the constuctor                **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
*******************************************************************************************************************/
#include "MicrochipSRAM.h"                                                    // Include the header definition    //
/*******************************************************************************************************************
** Class Constructor instantiates the class                                                                       **
*******************************************************************************************************************/
MicrochipSRAM::MicrochipSRAM(const uint8_t SSPin) : _SSPin(SSPin) {           // CONSTRUCTOR - Instantiate class  //
  pinMode(_SSPin,OUTPUT);                                                     // Define the CS/SS pin SPI I/O     //
  digitalWrite(_SSPin,HIGH);                                                  // Deselect by pulling CS pin high  //
  SPI.begin();                                                                // Start SPI                        //
  digitalWrite(_SSPin,LOW);                                                   // Select by pulling CS pin low     //
  SPI.transfer(SRAM_WRITE_MODE_REG);                                          // Next byte writes mode register   //
  SPI.transfer(SRAM_SEQ_MODE);                                                // Turn on sequential mode          //
  digitalWrite(_SSPin,HIGH);                                                  // Deselect by pulling CS pin high  //
  if (SRAMBytes == 0) {                                                       // Detect if the size wasn't given  //
    /***************************************************************************************************************
    ** Firstly set the first 0x4 memory positions to 0, this can be done without knowing the memory type. Then    **
    ** send 4 bytes: 0x0, 0x0, 0x1, 0xFF in write mode. If the chip uses 2 address bytes, then 0x1 is written to  **
    ** the first and 0xFF to the second memory position. If the chip uses 3 address bytes then 0xFF is written to **
    ** address 0x1 and the first memory position will be zero. If we assume a 3 address byte memory and read the  **
    ** first position and get a value of 0xFF then we've got a positive 1mBit id, otherwise we continue searching.**
    ***************************************************************************************************************/
    digitalWrite(_SSPin,LOW);                                                 // Select by pulling CS low         //
    SPI.transfer(SRAM_WRITE_CODE);                                            // Send the command for WRITE mode  //
    for (uint8_t i=0;i<4;i++) SPI.transfer(0x00);                             // Write zeros for address & data   //
    digitalWrite(_SSPin,HIGH);                                                // Deselect by pulling CS high      //
    digitalWrite(_SSPin,LOW);                                                 // Select by pulling CS low         //
    SPI.transfer(SRAM_WRITE_CODE);                                            // Send the command for WRITE mode  //
    SPI.transfer(0x00);                                                       // Send the 1st address byte        //
    SPI.transfer(0x00);                                                       // Send the 2nd address byte        //
    SPI.transfer(0x01);                                                       // LSB of address or 1st data byte  //
    SPI.transfer(0xFF);                                                       // 1st or 2nd data byte             //
    digitalWrite(_SSPin,HIGH);                                                // Deselect by pulling CS high      //
    digitalWrite(_SSPin,LOW);                                                 // Select by pulling CS low         //
    SPI.transfer(SRAM_READ_CODE);                                             // Send the command for WRITE mode  //
    SPI.transfer(0x00);                                                       // Send the 1st address byte        //
    SPI.transfer(0x00);                                                       // Send the 2nd address byte        //
    SPI.transfer(0x01);                                                       // 1st or 2nd data byte             //
    SRAMBytes = SPI.transfer(0x00);                                           // Read 1 byte from the memory      //
    digitalWrite(_SSPin,HIGH);                                                // Deselect by pulling CS high      //
    if (SRAMBytes==0xFF) SRAMBytes = SRAM_1024;                               // Set the memory size to 128KB     //
    else {                                                                    // Otherwise keep on identifying    //
      /*************************************************************************************************************
      ** Now that we know that we have a 2-byte addressable memory chip, write 2 bytes to the potentially last    **
      ** byte of the memory chip. Then read the first byte, if it contains the value we've just written then we   **
      ** know that on overflow has occurred and therefore know the chip size. If the first byte is still 0, go to **
      ** the next memory chip size until we've determined the chip; if we haven't gotten it then odds are that    **
      ** there's no memory chip attached or the CS/SS pin is incorrect - return a 0 to denote this problem        **
	  ** Note - at the time of writing there is no Microchip 128kbit chip, but the code is left in for future     **
	  ** compatibility.                                                                                           **
      *************************************************************************************************************/
      uint8_t i = 0;                                                          // Placeholder variable             //
      put(0,0x00);                                                            // Write zeros to bytes 1 & 2       //
      put(SRAM_64-1,0xFF);                                                    // Put 0xF at last & last+1 position//
      if (get(0,i)==0xF) SRAMBytes = SRAM_64;                                 // We've found a 64kbit memory chip //
      else {                                                                  // otherwise check next bigger chip //
        put(SRAM_128-1,0xFF);                                                 // Put 0xF at last & last+1 position//
        if (get(0,i)==0xF) SRAMBytes = SRAM_128;                              // We've found a 128kbit memory chip//
        else {                                                                // otherwise check next bigger size //
          put(SRAM_256-1,0xFF);                                               // Put 0xF at last & last+1 position//
          if (get(0,i)==0xF) SRAMBytes = SRAM_256;                            // We've found a 256kbit memory chip//
          else {                                                              // otherwise check next bigger size //
            put(SRAM_512-1,0xFF);                                             // Put 0xF at last & last+1 position//
            if (get(0,i)==0xF) SRAMBytes = SRAM_512;                          // We've found a 512kbit memory chip//
                          else SRAMBytes = 0;                                 // Otherwise no chip has been found //
          } // of if-then-else we don't have a 256kbit chip                   //                                  //
        } // of if-then else we don't have a 128kbit chip                     //                                  //
      } // of if-then else we don't have a 64kbit chip                        //                                  //
    } // of if-then-else we have a positive 1mbit ID                          //                                  //
  } // of if-then the size was specified by caller                            //                                  //
} // of class constructor                                                     //----------------------------------//
/*******************************************************************************************************************
** Class Destructor currently does nothing and is included for compatibility purposes                             **
*******************************************************************************************************************/
MicrochipSRAM::~MicrochipSRAM() {} // of unused class destructor              //                                  //
/*******************************************************************************************************************
** Method clearMemory to set all memory positions to the same value. Added v1.0.1.                                **
*******************************************************************************************************************/
void MicrochipSRAM::clearMemory(const uint8_t clearValue ) {                  // Clear all memory to one value    //
  digitalWrite(_SSPin,LOW);                                                   // Select by pulling CS low         //
  SPI.transfer(SRAM_WRITE_CODE);                                              // Send the command for WRITE mode  //
  if (SRAMBytes==SRAM_1024) SPI.transfer(0x00);                               // Send 3rd address when required   //
  SPI.transfer(0x00);                                                         // Send address data 0x00 value     //
  SPI.transfer(0x00);                                                         // Send address data 0x00 value     //
  for (uint32_t i=0;i<SRAMBytes;i++) SPI.transfer(clearValue);                // Fill memory with given value     //
  digitalWrite(_SSPin,HIGH);                                                  // Deselect by pulling CS high      //
} // of method ClearMemory                                                    //----------------------------------//
