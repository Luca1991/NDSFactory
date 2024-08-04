# NDSFactory
[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)
[![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.png?v=103)](https://opensource.org/licenses/GPL-3.0/)


A tool to unpack &amp; repack Nintendo DS ROMs (.nds)

If you find this software useful, please consider supporting it: 
[![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Z8Z511SOI)

![screenshot](https://raw.githubusercontent.com/Luca1991/NDSFactory/master/screenshot.png)

**!!!ROMS WITH OVERLAY ARE CURRENTLY NOT SUPPORTED!!!**

# Description

NDSFactory helps you easily unpack and repack Nintendo DS ROMs, but **some technical knowledge is required.**

A typical NDS ROM consists of the following sections:
* Header
* ARM9 Binary
* ARM7 Binary
* FNT (Filename Table)
* FAT (File Allocation Table)
* ARM9/ARM7 Overlay (Optional)
* ARM9/ARM7 Overlay Files (Optional)
* Icon/Title Logo
* FAT Files (The actual files used by the software, like Graphics, Music etc.)

NDSFactory allows you to extract these sections, modify them as needed, and rebuild the ROM with your edited sections. If modified sections are larger than the original, you must specify their new physical address and size in the header. **Ensure that sections do not overlap and remember to patch the FAT.BIN if necessary.**

This tool is particularly useful for modding games or writing trainers.

# How to use

## Unpacker Tab
In the Unpacker Tab, you can load your Nintendo DS software (.nds) and extract the ROM sections, including individual FAT files. Take note of the original address of the FAT files, as you will need this value if you alter the addresses and sizes of the sections.

**You can then do what you want with these sections (inject code, apply patches etc.)**

## Packer Tab
In the Packer Tab, you can recreate a .nds file using your edited sections. If your sections are larger than the originals, you must update their addresses and sizes in the header. Ensure that the addresses do not overlap, or the final ROM will be broken. If you repack edited sections and the FAT files' address is different from the original, you must patch the FAT (fat.bin). The FAT contains absolute addresses representing each file's start and end addresses, so you need to update them accordingly (use the FAT Patching Tab for this).

## Fat Tools Tab
In this tab, you can patch the FAT section (fat.bin). This is only necessary if the FAT files' final address (fat_data.bin) differs from the original. Patching the FAT is straightforward: load your fat.bin, and fill in the original and new addresses of fat_data.bin. This will produce a patched fat.bin for use in the packing process.

# Known Limitations/Possible Future Features/Bugs

* Add support for ROMs with overlays.
* Add support to rebuild a new fat_data.bin and fat.bin from a set of files inside a directory.

If you find a bug, feel free to open an issue or submit a pull request :)

### Developed with ❤ by Luca D'Amico
### Special thanks to Antonio Barba & Davide Trogu
