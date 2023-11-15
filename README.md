# BSQ

Find the largest square in a map composed of '.' and 'o'

Example of a map file :

```
9
...........................
....o......................
............o..............
...........................
....o......................
..............o............
...........................
......o..............o.....
..o.......o................
```

The first line of the map file is the number of lines in the map.
Then the map is composed of '.' and 'o' characters. And you have to find the largest square composed of '.'.

Example of a map with the largest square surrounded by 'x' characters :

```
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx..o............
.....xxxxxxx...............
......o..............o.....
..o.......o................
```

This is the intended output of the program.

## Use the BSQ program

Get the project on your machine.

### Prerequisites

What you need to install the software and how to install it:

```
gcc
make
```

And, if you want to run the tests, you will need to install `criterion`.

### Usage

Compile the project

```
make re
```

Run the project

```
./bsq <your_map.txt>
```