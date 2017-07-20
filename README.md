# valerney
AVR RF remote emulator/spoofer

This program shifts out programmed sequence of bytes on one pin without a clock at a fixed bitrate.

## Building
```sh
# PREPARE
# change -mmcu flag in CMakeLists.txt to your MCU
# change register names in main.c if they differ from those on ATtiny85
# set your desired code and bitrate in main.c

# BUILD
mkdir build
cd build
cmake ../
make

# UPLOAD (example)
avrdude -c usbasp -p t85 -U flash:w:valerney:e
```
