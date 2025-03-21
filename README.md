# Obelisk Search (WIP)

This program searches for high period oscillators in foam rules.

Obelisk is a term coined by NimbleRogue on the conwaylife.com forums.
Some obelisks have periods in the billions. In this program it might take a while though.

## Building and running

To build, you use `g++ obelisk.cpp -O3 -o obelisk`.

(If you get a "no such file or directory" error, try running `git submodule update --init --recursive`)

Then, to run it, use the command `./obelisk` and watch the oscillators fly.

## Settings

Settings are found in the file `obelisk.h`. (Yes, it's a header file.)

The settings should be self-explanatory. If you lose the names to the settings, I'll have this here for quick access.
```
#define RULE "b2n3aijkq4q5ciqy6-ik7cs2-ck3ejky4-anqty5cenry6-e7" // Rule
#define MAXPOP 200 // Maximum population
#define SYMMETRY "C1" // Symmetry (C1, D2-, D2|, D4+)
#define PATTERN "BAAAB$BA.AB$BAAAB!" // 3-state pattern (State 3 is a random cell between 0 and 1)
#define DENSITY 0.3 // Density (0.0 to 1.0)
#define TILE {0, 2, 5} // Pattern tile rate (dx, dy, repeat)
#define MAXBBOX {100, 100} // Maximum bounding box during search (prevents explosions)
#define PERIOD {1, 100000} // Minimum and maximum period (min, max)
#define STABS {100, 10} // Period stab rate (prevents explosions)
```

If your program doesn't work past "Instruction .... detected", then run `add_rule.py RULE` where RULE is the one in your settings file.# obelisksearch
