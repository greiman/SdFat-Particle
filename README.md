About
===
SdFat-Particle is a port of the SdFat library for [Particle](https://www.particle.io/) development boards.

The SdFat library provides read/write access to FAT16/FAT32 file systems on SD/SDHC flash cards.

SdFat for Particle supports fast DMA access for all SPI interfaces on Particle devices.

SdFat supports long filenames.


## Documentation

Download the SdFat-Particle-doc repository from GitHub.

https://github.com/greiman/SdFat-Particle-doc

Please read the html documentation in the html folder by opening SdFat.html.

Look at the classes tab for details about class member functions.


## Examples

Please try the examples in the firmware/examples folder.

Start with the TryMeFirst example.

You can check the performance of your SD card with the bench example.

Here is a list of example files I have tested on P1/photon.

bench.cpp - Benchmark SD read/write speed.

DirectoryFunctions.cpp - Demonstrate chdir(), ls(), mkdir(), and  rmdir().

LowLatencyLogger.cpp - High speed binary data logger.

OpenNext.cpp - Open all files in a directory.

ReadCsvArray.cpp - Function to read an array from a csv file.

ReadCsvFields.cpp - Function to read csv fields.

SdFormatter.cpp - Format an SD card according to the SD standard.

SdInfo.cpp - Display information about an SD card.

Timestamp.cpp - Shows how to time-stamp files.

TryMeFirst.cpp - A simple read/write example.

VolumeFreeSpace.cpp - Determine free space in a volume.

