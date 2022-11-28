# Zff-Reload

This is a reloaded version of Zff.

**Notice: Developing now!**

# Getting started

## Windows

Get the `Zff-Windows.exe` from [action builds](https://github.com/ohzff/Zff-Reload/actions).

## MacOS & Linux

> Required `g++`.

Download the source and type:

```bash
g++ ./main.cpp -o zff -pthread -std=c++11
```

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

# Usage

First, make sure `usr/` folder is there with your executable file.

Second, run the executable file.

Use `Left` `Right` arrow to move the people and `Up` arrow or `SPACE bar` to jump up to reach the exit place `#`.

# FAQ

## `usr/` folder cannot found

1. Go [here](https://github.com/ohzff/Zff-Reload/releases) to get an zip file `data.zip`.
2. Unzip it and put `usr/` with your executable file.

# More...

...
