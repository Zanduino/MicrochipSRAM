# MicrochipSRAM library
*Arduino* library which defines methods for accessing any the Microchip SRAM and SNVRAM SPI family memory chips. The get() and put() methods allow any data type to be written with one call and the library automagically detects which of the possible memory chips is in use. 
The following Microchip **SRAM** and **SNVRAM** chips can be accessed using this library:

<table>
  <tr>
  <td><b>Memory Type</b></td>
  <td><b>Storage Bits</b></td>
  </tr>
  <tr>
    <td>23x640</td>
    <td>64 kbit</td>
  </tr>
  <tr>
    <td>23x256</td>
    <td>256 kbit</td>
  </tr>
  <tr>
    <td>23x512<br>23LCV512</td>
    <td>512 kbit</td>
  </tr>
  <tr>
    <td>23x1024<br>23LCV1024</td>
    <td>1024 kbit</td>
  </tr>
</table>

See the [Wiki](https://github.com/SV-Zanshin/MicrochipSRAM/wiki) pages for details of the class and the variables / functions accessible in it.

![Zanshin Logo](https://www.sv-zanshin.com/images/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/images/gif/zanshintext.gif" width="75"/>
