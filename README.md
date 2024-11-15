
# RobotWriter

**RobotWriter** is a software project designed to control a robotic writing machine. This project interfaces with the hardware over serial communication, enabling control commands for the robotic machine.

## Documentation:

Documentation is generated by doxygen and can be viewed at:
https://georgedowning20.github.io/MMME3085-RobotWriter/

## Features

- Serial communication with hardware
- Configurable control commands
- Cross-platform support via POSIX libraries

## Requirements

- **MSYS2**: Provides a Unix-like environment for Windows, including essential tools such as `gcc` and `make`.

## Installation and Setup (MSYS2)

Follow these steps to set up the project on Windows using MSYS2.

### 1. Install Tools for Compilation

#### Windows

In the MSYS2 terminal, install `gcc` and `make` with the following command:

```bash
pacman -S make gcc
```

#### LINUX

In the MSYS2 terminal, install `gcc` and `make` with the following command:

```bash
sudo apt install gcc make
```

#### MAC

In the MSYS2 terminal, install `gcc` and `make` with the following command:

```bash
brew install gcc make
```



### 2. Download the Code

To download the code, clone this repository using `git` (which is pre-installed in MSYS2):

```bash
git clone git@github.com:GeorgeDowning20/MMME3085-RobotWriter.git
```

### 3. Navigate to the Project Directory

Change to the project directory:

```bash
cd RobotWriter
```

### 4. Build the Project

Use `make` to build the project:

```bash
make
```

This command compiles the code and creates an executable in the `build` directory.

## Running the Program

After building the project, you can run the executable from the `build` directory:

```bash
./build/RobotWriter
```

or 

```bash
make run
```

## Troubleshooting

If you encounter any issues related to undefined symbols (like `CRTSCTS` for hardware flow control), ensure the `_DEFAULT_SOURCE` macro is defined when compiling. This should already be handled in the `Makefile`, but you can also define it manually if needed:

```bash
gcc -D_DEFAULT_SOURCE ...
```

## License

This project is licensed under the terms of the GNU General Public License v3.0. See `LICENSE` for more details.
