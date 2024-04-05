# Operating System

## Build Requirements

- CMake >= 2.27

Toolchain for target platform:
- GCC >= 8.1.0
- Binutils

Bootable disk image for x86 systems:
- GRUB 2
- xorriso

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

Requires `qemu`:

```shell
qemu-system-<ARCH> -cdrom system.iso
```

## License

Copyright (c) 2023 Natalie Wiggins.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
