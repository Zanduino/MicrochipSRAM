# MicrochipSRAM library [![Build Status](https://travis-ci.org/SV-Zanshin/MicrochipSRAM.svg?branch=master)](https://travis-ci.org/SV-Zanshin/MicrochipSRAM) [![DOI](https://www.zenodo.org/badge/74214598.svg)](https://www.zenodo.org/badge/latestdoi/74214598)
<img src="https://github.com/SV-Zanshin/MicrochipSRAM/blob/master/Images/Microchip23LCV1024.jpg" width="175" align="right"/> *Arduino* library which defines methods for accessing any the Microchip SRAM and SNVRAM SPI family memory chips. [Microchip](http://www.microchip.com/design-centers/memory/serial-sram-serial-nvsram/overview) offers a number of volatile and nonvolatile memory chips that use the SPI protocol. One thing that differentiates these chips from others on the market is that they have an unlimited number of write cycles, so the programmer doesn't have to worry about load leveling and writing only pages/blocks at a time to avoid memory hardware degradation or failure. The memory is also fast enough so that no delays need be introduced when using SPI.

This _Arduino_ library offers a number of methods that allow easy reading and writing to/from the memory as well as a method for detecting exactly which one of the supported memory chips is installed.

The following Microchip **SRAM** and **SNVRAM** chips can be accessed using this library:

<table>
  <tr>
    <td><b>Memory Type</b></td>
    <td><b>Storage Bits</b></td>
    <td><b>Datasheets</b></td>
  </tr>
  <tr>
    <td>23x640</td>
    <td>64 kbit</td>
    <td><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/22126D.pdf">23x640 Datasheet</a></td>
  </tr>
  <tr>
    <td>23x256</td>
    <td>256 kbit</td>
    <td><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/22100E.pdf">23x256 Datasheet</a></td>
  </tr>
  <tr>
    <td>23x512<br>23LCV512</td>
    <td>512 kbit</td>
    <td><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/20005155B.pdf">23x512 Datasheet<br><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/25157A.pdf">23LCV512 Datasheet</a></td>
  </tr>
  <tr>
    <td>23x1024<br>23LCV1024</td>
    <td>1024 kbit</td>
    <td><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/25142A.pdf">23x1024 Datasheet</a><br><a href="http://ww1.microchip.com/downloads/en/DeviceDoc/25156A.pdf">23LCV1024 Datasheet</a></td>
  </tr>
</table>

See the [Wiki pages](https://github.com/SV-Zanshin/MicrochipSRAM/wiki) for details of the class and the variables / functions accessible in it. The doxygen documentation can be found at [Doxygen Documentation](https://sv-zanshin.github.io/MicrochipSRAM/html/index.html)  

![Zanshin Logo](https://www.sv-zanshin.com/r/images/site/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/r/images/site/gif/zanshintext.gif" width="75"/>
