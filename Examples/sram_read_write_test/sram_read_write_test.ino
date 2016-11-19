/*******************************************************************************************************************
** Example showing various read and write methods using the MicrochipSRAM library                                 **
**                                                                                                                **
** The library uses the standard SPI library and assumes that the default hardware SPI is being utilized.         **
**                                                                                                                **
** The library contains the constructor, which requires the CS/SS pin number as input and returns the size, in    **
** bytes, of the specific Microchip SPI SRAM chip detected. If a zero is returned it means that no chip was       **
** detected which could be caused by either an incorrect CS/SS pin number, or incorrect wiring or no chip.        **
**                                                                                                                **
** There are only 3 methods in the library:                                                                       **
**                                                                                                                **
** [optional uint32 return address] put ( address, {variable} )                                                   **
** [optional uint32 return address] put ( address, {variable} )                                                   **
**                           fillMemory ( address, {variable} )                                                   **
** If the address is higher than the actual amount of memory bytes availabe it automatically overflows and starts **
** back at the beginning of memory, i.e. a 256kbit chip (23x256) stores 32768 bytes. If one puts 2 bytes starting **
** at 32767 then byte 0 of the array is overwritten. Get and Put will word wrap from the end to the beginning.    **
**                                                                                                                **
** fillMemory will place identical copies of the {variable} starting at the memory position specified to the end  **
** of memory. Any partial entry at the end of memory will not be filled.                                          **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
*******************************************************************************************************************/
#include <MicrochipSRAM.h>                                                    // Include the library              //
#define SRAM_SS_PIN 2                                                         // Pin 2 for SPI.Change if necessary//
uint32_t memorySize = 0;                                                      // Holds the computed memory size   //
static MicrochipSRAM memory(SRAM_SS_PIN,memorySize);                          // Instantiate the memory class     //
                                                                              //----------------------------------//
uint32_t address;
char testArray[12] = "Hello World";
struct testStructType{
  float   pi;
  char    textarray[12];
};
testStructType testStruct = {3.14159, "Hello World" };
  
void setup() {                                                                // Arduino standard setup method    //
  Serial.begin(9600);                                                         // Start serial comms at 9600 Baud  //
  delay(3000);                                                                // Some Atmels need time to start   //
  Serial.println("Starting Microchip SRAM test program");                     //                                  //
  if (memorySize==0) {
    Serial.print("- Error detecting SPI memory.\n");
    Serial.print(" - Either an incorrect SPI pin was specified,\n- or the ");
    Serial.print("Microchip memory has been wired incorrectly,\n- or it is");
    Serial.print("not a Microchip memory.\nSupported memories are:\n23x640");
    Serial.print(", 23x256, 23x512, 23xx1024, 23LCV512 & 23LCV1024");
  } else {
    Serial.print("- A Microchip with ");Serial.print(memorySize);
    Serial.print(" Bytes of memory has been detected.\n\n");
    Serial.print("Writing 4 consecutive arrays starting at 100:\n");
    address = 100;
    for (uint8_t i=0;i<4;i++) address = memory.put(address,testArray);
    Serial.print("Next address to write to is ");Serial.println(address);
    Serial.print("Reading text array at location 112:\n");
    memset(testArray,0,sizeof(testArray)); // move zeroes to array
    memory.get(112,testArray);
    Serial.print("Text array read is \"");Serial.print(testArray);
    Serial.print("\"\nFilling memory with copies of a structure\n");
    memory.fillMemory(0,testStruct); // fill memory starting at 0with structure
    Serial.print("Reading 10th copy of the structure back from memory.\n");
    testStruct.pi = 0;
    testStruct.textarray[0] = "X"; // overwrite first character in array
    memory.get(sizeof(testStruct)*10,testStruct);
    Serial.print("Text array in structure is \"");
    Serial.print(testStruct.textarray);
    Serial.print("\"\npi in structure is \"");
    Serial.print(testStruct.pi,5);Serial.print("\"\n");
  } // of if-then-else a chip was detected
} // of method setup()

void loop() { while(1); } // do nothing in the main loop
