# Operating System

![CMake](https://github.com/lunar-natalie/os/actions/workflows/cmake.yml/badge.svg)
![Linter](https://github.com/lunar-natalie/os/actions/workflows/linter.yml/badge.svg)

## Build Requirements

- [CMake](https://cmake.org/) >= 3.27

Toolchain with a cross-compiler built for the target platform:

- [GCC](https://gcc.gnu.org/) >= 8.1.0
- [Binutils](https://www.gnu.org/software/binutils/) >= 2.41

Boot media creation:

- [GRUB 2](https://git.savannah.gnu.org/git/grub.git) command-line tools
  - Runtime dependencies: `xorriso`
  - Build dependencies: `autoconf` `automake` `gawk`

Development tools:

- [ClangFormat](https://releases.llvm.org/11.0.0/tools/clang/docs/ClangFormat.html) >= 11
- [Clang-Tidy](https://releases.llvm.org/11.0.0/tools/clang/tools/extra/docs/clang-tidy/index.html) >= 11

## Supported Targets

| Platform   | Architecture | Toolchain                          |
|------------|--------------|------------------------------------|
| `i686-elf` | `i386`       | `i686-elf-gcc` `i686-elf-binutils` |

A [Docker image](https://github.com/lunar-natalie/os-build) is also provided with a toolchain for `i686-elf` builds.

## Building

Configure the project, specifying `<PLATFORM>`:

```shell
mkdir -p build
cmake -B build --preset <PLATFORM>
```

Build all targets:

```shell
cmake --build build
```

Run tests:

```shell
ctest --test-dir build
```

## Virtualization

To virtualize the system with [QEMU](https://www.qemu.org/), run the following command, specifying `<ARCH>`:

```shell
qemu-system-<ARCH> -cdrom build/system.iso
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
