# MicrochipSRAM library
*Arduino* library which defines methods for accessing any the Microchip SRAM and SNVRAM SPI family memory chips. The get() and put() methods allow any data type to be written with one call and the library automagically detects which of the possible memory chips is in use. 
The following Microchip **SRAM** and **SNVRAM** chips can be accessed using this library:

* 23x640		(64kbit)
* 23x256		(256kbit)
* 23x512		(512kbit)
* 23x1024		(1024kbit)
* 23LCV512	(512kbit)
* 23LCV1024	(1024kbit)


## Public methods and variables
The following public variables and methods/functions are included in the library:
###Class Constructor
`MicrochipSRAM sram(SS_PIN)`. The class is instantiated by the constructor passing in the SS_PIN parameter, which is the Arduino CS/SS Pin that is used by SPI to address the chip.
###Class Destructor
Unused
###Variable `SRAMBytes`
This is set to the actual amount of memory in Bytes available in the Microchip memory and is filled during class instantiation. Values returned are currently 8192, 32768, 65536 or 131072 bytes.
###Function `NewAddress = get(Address,{Variable});`
The `Address` is the memory address, starting at 0. The `{Variable}` can be a standard data type, structure or array and the structure's size is automatically determined. If the read goes past the end of memory it loops around again at the beginning. The function returns the pointer to the next memory location after the read.
###Function `NewAddress = put(Address,{Variable});`
The `Address` is the memory address, starting at 0. The `{Variable}` can be a standard data type, structure or array and the structure's size is automatically determined. If the write goes past the end of memory it loops around again at the beginning. The function returns the pointer to the next memory location after the write.
###Function `clearMemory([Value]);`
This function sets all memory bytes to 0 when the optional parameter is omitted, otherwise it writes the parameter value to all memory bytes
###Function `fillMemory(Address,{Variable});`
This function writes copies of {Variable} to memory starting at location `Address` until the end of memory. The `{Variable}` can be a standard data type, structure or array and the structure's size is automatically determined. 

![Zanshin Logo](https://www.sv-zanshin.com/images/gif/zanshincalligraphy.gif)
