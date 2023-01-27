# Zff-Reload

This is a reloaded version of Zff.

![GitHub repo size](https://img.shields.io/github/repo-size/ohzff/Zff-Reload?label=size&logo=github)  ![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/ohzff/Zff-Reload)  ![GitHub top language](https://img.shields.io/github/languages/top/ohzff/Zff-Reload)

**Notice: Developing now!**

https://user-images.githubusercontent.com/59787082/207616790-4089fd40-3a93-4bc8-96ef-af630abb0d3d.mov

# Getting started

## Windows

Get the `Zff-Windows.exe` from [releases page](https://github.com/ohzff/Zff-Reload/releases).

## macOS & Linux

Download `linux.sh` from folder `zff-reload/`.

```bash
curl https://raw.githubusercontent.com/ohzff/install/main/zff-reload/linux.sh > linux.sh
```

Change file modes to `execute bits`.

```bash
chmod +x ./linux.sh
```

Then, run it.

```bash
./linux.sh
```

[Get more information from here](https://github.com/ohzff/install/blob/main/README.md#zff-reload).

# Usage

> **Notice for Windows Users:** You may need to make the terminal smmaller than 80x80.

First, make sure `usr/` folder is there with your executable file.

Second, run the executable file.

> Double click it in Windows

> Run `./Zff` **in terminal** in macOS and Linux

Use `Left` `Right` arrow to move the people and `Up` arrow or `SPACE bar` to jump up to reach the exit place `#`.

## Advanced usages

**Args**

- Get version info: `./Zff version`

**In Level Selection**

- Press `l` to load custom world.

**In game**

- Move forcely: type `/pos X Y` to move to `(X, Y)`

# Development

## App developing

If you have any idea, please create a pull requst to tell us.

**Windows compile flags**

```bash
g++ ./main.cpp -o zff -std=c++11 -static-libgcc -static-libstdc++ -L.
```

**Mac&Linux compile flags**

```bash
g++ ./main.cpp -o zff -std=c++11 -pthread
```

## World data developing

A world includes `main`, `world`, `trigger` three files in an ID folder.

```bash
usr
└── world
    ├── 1                   # ID folder
    │   ├── main            # main info
    │   ├── trigger         # Trigger settings
    │   └── world           # Full world information
    └── 2
        ├── main
        ├── trigger
        └── world
```

**`main` file**

6 integers: `n, m, Sx, Sy, Ex, Ey`

- `n` for the number of rows.
- `m` for the number of columns.
- `(Sx, Sy)` for the starting position.
- `(Ex, Ey)` for the ending position.

**`world` file**

A `n*m` matrix, saved the world information.

> **Notice: Please fill the `n*m` frame with SPACE or symbol `@`!**

**`trigger` file**

One integers `n` in the first line, refering to the number of triggers.

The following `n` rows with 6 integers `Tx, Ty, Cx, Cy, To, d` in each row.

- `(Tx, Ty)` for the position of trigger.
- `(Cx, Cy)` for the position that trigger controled.
- `To` for the ID that trigger changes to.
- `d` for the delay time of disappear (ms).

# FAQ

## `usr/` folder cannot found

1. Go [here](https://github.com/ohzff/Zff-Reload/releases) to get an zip file `data.zip`.
2. Unzip it and put `usr/` with your executable file.

# License

This project is under MIT-License.

```
MIT License

Copyright (c) 2022 LanGong Zff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

# More...

...
