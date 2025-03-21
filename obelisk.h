#define RULE "b2n3aijkq4q5ciqy6-ik7cs2-ck3ejky4-anqty5cenry6-e7" // Rule
#define MAXPOP 200 // Maximum population
#define SYMMETRY "D2|" // Symmetry (C1, D2-, D2|, D4+)
#define PATTERN "BAAAB$BA.AB$BAAAB!" // 3-state pattern (State 3 is a random cell between 0 and 1)
#define DENSITY 0.3 // Density (0.0 to 1.0)
#define TILE {0, 2, 8} // Pattern tile rate (dx, dy, repeat)
#define CENTER {4, 0} // Center of pattern (for symmetry)
#define MAXBBOX {100, 100} // Maximum bounding box during search (prevents explosions)
#define PERIOD {1, 100000} // Minimum and maximum period (min, max)
#define STABS {100, 10} // Period stab rate (prevents explosions)