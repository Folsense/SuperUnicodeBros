# Super Unicode Bros
Mario in the command line

Please don't try to learn from this I don't know how to write code properly.
To use it, put your mario bros rom ("named mariobros.nes") into the roms folder and run make and then ./mario.
You can try a different rom, but there's a very high chance something won't work correctly.

To change the resolution, you can edit the values at the top of PPU2C02.h.

# This has only been tested on Linux
But I think the only non-standard library is for keyboard inputs, so if you want to make it work you should be able to just change the Controller class to use whatever library works on your system and then change the makefile flags.
