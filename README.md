# Super Unicode Bros
Mario in the command line

Please don't try to learn from this I don't know how to write code properly.
To use it, put your mario bros rom ("named mariobros.nes") into the roms folder and run make and then ./mario. I assume you'll also need to install the library for keyboard inputs (X11) if your machine supports it. You can try a different rom, but there's a very high chance something won't work correctly. Only the earliest games should work (like Golf, Donkey Kong, and Balloon Fight), and even some of those don't work because there's a bug or I didn't implement something they use.

To change the resolution, you can edit the values at the top of PPU2C02.h.

# This has only been tested on Linux
But I think the only non-standard library I used is for keyboard inputs, so if you want to make it work you should be able to just change the Controller class to use whatever library works on your system and then change the makefile flags.
Also you might need to change the slashes in the file paths.
