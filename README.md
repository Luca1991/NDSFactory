# NDSFactory
[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)
[![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.png?v=103)](https://opensource.org/licenses/GPL-3.0/)


A tool to unpack &amp; repack Nintendo DS ROMs (.nds)

If you find this software useful, please [![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Z8Z511SOI)

![screenshot](https://raw.githubusercontent.com/Luca1991/NDSFactory/master/screenshot.png)

**!!!ROMS WITH OVERLAY ARE CURRENTLY NOT SUPPORTED!!!**

# Description

This software will help you to easily unpack and repack Nintendo DS roms, but **IT REQUIRES SOME KNOWLEDGE!**

Basically an NDS software is composed of the following sections:
* Header
* ARM9 Binary
* ARM7 Binary
* FNT (Filename Table)
* FAT (File Allocation Table)
* ARM9/ARM7 Overlay (Optional)
* ARM9/ARM7 Overlay Files (Optional)
* Icon/Title Logo
* FAT Files (The actual files used by the software, like Graphics, Music etc.)

With NDSFactory you can extract these sections, modify them using your preferred way and the rebuild the rom with your edited sections.
If the modified sections are bigger than the original ones, you can specify their new physical address and size in the header: if so, **make
sure that they DON'T OVERLAP, and remember to PATCH THE FAT.BIN** (more on this later).

**This software will be particularly useful if you want to mod your games or write a trainer for them.**

# How to use it

## Unpacker Tab
In the unpacker tab you can load your Nintendo DS software (.nds) and then you can extract the ROM sections, including the individual FAT files.
Please note the Original Address of the FAT Files, you will need this value later if you are going to alter the addresses and size of the sections.

**You can then do what you want with these sections (inject code, apply patches etc.)**

## Packer Tab
In the packer tab you can re-create an .nds file using your edited sections. If your sections are bigger than the originals, you have to edit their addresses and size (in the header). **Make sure that the addresses don't overlap, or the final rom will be broken**. If you are repacking edited sections, and the FAT Files Address is different than the original one, **make sure to patch the FAT (fat.bin)**: the FAT is a list of absolute addresses (representing each file start address and end address), so you need to update them (you can easily do this using the FAT Patching Tab).

## Fat Patching Tab
In this tab you can easily patch the FAT section (fat.bin). You have to do this only if the FAT Files (fat_data.bin) final address is different than the original one.
Patching the FAT is easy, all you have to do is load your fat.bin, and fill the original address and the new address of fat_data.bin. This will produce a patched fat.bin that
you can use in the packing process.

# Known Limitations/Possible Future Features/Bugs

* Add support for roms with OVERLAY
* Add support to rebuild a new fat_data.bin and fat.bin from a set of files inside a directory

If you found a bug, feel free to open an issue or send a PR :)

### Developed with ❤ by Luca D'Amico
### Special thanks to Antonio Barba & Davide Trogu
