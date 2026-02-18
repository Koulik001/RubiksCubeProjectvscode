# Rubik's Cube Solver

A high-performance Rubik's Cube solver implemented in C++ using the **IDA\*** (Iterative Deepening A\*) search algorithm guided by a **Corner Pattern Database** heuristic. The solver finds optimal or near-optimal solutions efficiently by combining classical AI search with memory-efficient data structures.

---

## Features

- **Multiple cube representations** — 3D array, 1D array both interchangeable via polymorphism
- **Pattern Database heuristic** — precomputed corner pattern database stored as a binary file for fast lookup
- **Memory-efficient storage** — nibble array packs two 4-bit values per byte, halving memory usage for the 100M+ entry database
- **IDA\* solver** — recursive depth-first search with iterative deepening, admissible heuristic guarantees optimal solutions
- **BFS-based DB builder** — builds the corner pattern database offline via BFS up to depth 8, with remaining states assigned a safe lower-bound value of 9

---

## How It Works

### 1. Cube Representations

Three internal representations of the cube are supported, all inheriting from a common `RubiksCube` base class:

| Class | Description |
|---|---|
| `RubiksCube3dArray` | Intuitive 6×3×3 face representation |
| `RubiksCube1dArray` | Flattened 1D array for cache efficiency |

All representations implement the same move, invert, and corner query interface, making them interchangeable with the solver and database.

### 2. Corner Pattern Database

The Rubik's Cube has 8 corners. Each corner has a **position** (0–7) and an **orientation** (0–2). The total number of unique corner states is:

```
8! × 3^7 = 40320 × 2187 = 88,179,840 ... padded to 100,179,840
```

Each state is mapped to a unique index via:

```
index = rank(corner_permutation) × 2187 + orientation_number
```

where `rank()` uses a Lehmer code / factoradic permutation indexer. The value stored at each index is the **minimum number of moves** needed to solve all 8 corners from that state.

### 3. Nibble Array

The database stores values 0–11 (4 bits each). Instead of using a full byte per entry, a custom `NibbleArray` packs two entries per byte:

```
Byte layout: [entry at even index (4 bits)] [entry at odd index (4 bits)]
```

This halves the database size from ~100MB to ~50MB.

### 4. Database Construction (BFS)

The `CornerDBMaker` builds the database offline using BFS from the solved state:

- BFS runs level by level up to depth 8 (~35 minutes on a standard PC)
- All states reachable within 8 moves are stored with their exact distance
- States not reached by BFS (requiring 9–11 moves) are assigned the value `9` — a valid lower bound since BFS exhausted everything reachable in ≤8 moves
- The final database is serialized to a binary file for reuse

### 5. IDA\* Solver

The solver uses recursive IDA\* — iterative deepening over the f = depth + h(cube) cost function:

```
dfs(cube, depth, bound):
    f = depth + h(cube)
    if f > bound → update next_bound, return false
    if cube.isSolved() → return true
    for each of 18 moves:
        apply move
        recurse
        undo move
```

Each iteration increases the bound to the minimum exceeded f-value from the previous iteration. The heuristic `h(cube) = cornerDB.getNumMoves(cube)` is **admissible** (never overestimates), guaranteeing the solver finds an optimal solution.

---

## Project Structure

```
├── Model/
│   ├── RubiksCube.h               # Abstract base class
│   ├── RubiksCube3dArray.cpp/.h   # 3D array representation
│   ├── RubiksCube1dArray.cpp/.h   # 1D array representation
│
├── PatternDatabases/
│   ├── NibbleArray.cpp/.h         # 4-bit packed array
│   ├── PatternDatabase.cpp/.h     # Abstract DB base class
│   ├── CornerPatternDatabase.cpp/.h # Corner-specific DB + indexing
│   ├── CornerDBMaker.cpp/.h       # BFS builder for corner DB
│   ├── PermutationIndexer.h       # Lehmer code ranker
│   └── math.cpp/.h                # Factorial / nCr / nPr utilities
│
├── Solver/
│   └── IDAstarSolver.h            # Templated IDA* solver
│
└── main.cpp
```

---

## Getting Started

### Prerequisites

- C++17 or later
- ~50MB disk space for the pattern database

### Build

```bash
mkdir build && cd build
cmake ..
make
```

### Run

**Step 1 — Build the corner pattern database (one-time, ~35 mins):**

```cpp
// In main.cpp
CornerDBMaker dbMaker("corner_db.bin", 0xFF);
dbMaker.bfsAndStore();
```

**Step 2 — Solve a scrambled cube:**

```cpp
RubiksCube3dArray cube;
// Apply scramble moves
cube.move(RubiksCube::MOVE::U);
cube.move(RubiksCube::MOVE::R);
// ... more moves

IDAstarSolver<RubiksCube3dArray, Hash3d> solver(cube, "corner_db.bin");
auto solution = solver.solve();

for (auto move : solution)
    cout << cube.moveToString(move) << " ";
```

---

## Algorithm Complexity

| Phase | Time | Space |
|---|---|---|
| DB construction (BFS to depth 8) | ~35 min (one-time) | ~50MB on disk |
| DB lookup | O(1) | ~50MB in RAM |
| IDA\* solve (≤15 move scramble) | < 1 second | O(depth) stack only |

IDA\* uses O(depth) memory — just the current DFS path — unlike A\* which must hold all frontier nodes simultaneously.

---

## Key Design Decisions

**Why nibble array?** The database has ~100M entries each needing only 4 bits (values 0–11). A byte array would waste 50MB unnecessarily.

**Why stop BFS at depth 8?** Going to depth 11 (the true maximum for corners) would take several hours. Depth 8 covers the vast majority of states, and assigning `9` to unreached states keeps the heuristic admissible while still being informative.

**Why IDA\* over A\*?** A\* would need to store all explored states in memory — tens of millions of nodes for a 20-move scramble. IDA\* uses only stack space proportional to the current search depth, making it practical on standard hardware.

**Why polymorphism for cube representations?** The pattern database's `getDatabaseIndex` accepts a `const RubiksCube&` base reference, so any representation can query the DB without rebuilding it. The solver is separately templated to allow type-specific hashing and copying.

---

## License

MIT License — feel free to use, modify, and distribute.