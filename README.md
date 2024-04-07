# Operating System

## Build Requirements

- [CMake](https://cmake.org/) >= 3.27

Toolchain for target platform:
- [GCC](https://gcc.gnu.org/) >= 8.1.0
- [GNU Binutils](https://www.gnu.org/software/binutils/)

Bootable disk image for x86 systems:
- [GRUB 2](https://git.savannah.gnu.org/git/grub.git) command-line tools
  - Build dependencies: `autoconf` `automake` `gawk`
- [GNU xorriso](https://www.gnu.org/software/xorriso/)
- [GNU mtools](https://www.gnu.org/software/mtools/)

## Supported Platforms

| Platform   | Architecture | Toolchain                          |
|------------|--------------|------------------------------------|
| `i686-elf` | `i386`       | `i686-elf-gcc` `i686-elf-binutils` |

## Building

```shell
mkdir -p build && \
cd build && \
cmake .. --preset <PLATFORM> && \
cd default && \
cmake --build .
```

## Testing

Requires [QEMU](https://www.qemu.org/):

```shell
qemu-system-<ARCH> -cdrom system.iso
```

## License

Copyright (c) 2023 Natalie Wiggins. All rights reserved.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
