# 2D Poisson Solver

A finite-difference solver for the 2D Poisson equation written in C++20.
The solver uses a structured grid and explicit FTCS iteration with Dirichlet boundary conditions.

This is mostly a practical exercise, but I intend for it to evolve over time! (20260228 RH)

Quadrupole Equipotential Contours |  Quadrupole Potential Surface
:-------------------------:|:-------------------------:
![](https://github.com/rhj2000/PoissonSolver/blob/main/poisson_contours.png)  |  ![](https://github.com/rhj2000/PoissonSolver/blob/main/poisson_surface.png)

## Problem

This code solves the 2D Poisson equation:

∇²u = f(x,y)

on a square domain with Dirichlet boundary conditions.

The equation is discretized using a second-order finite-difference stencil.

## Project Structure

```
poisson-solver/
│── include/
│   ├── grid.hpp
│   └── poissonsolver.hpp
│
│── src/
│   ├── grid.cpp
│   ├── poissonsolver.cpp
│   └── main.cpp
│
│── CMakeLists.txt
│── README.md
```

## Build

Requires:

- C++20 (but probably runs fine on older versions)
- CMake

Build with:

```
mkdir build
cd build
cmake ..
make
```

### Run Instructions

From the build directory:

```
./poisson_solver
```

### Example Output

Example solution for a 5×5 grid with boundary value u=1:

```
1 1 1 1 1
1 0.03 0.016 0.03 1
1 0.016 0.001 0.016 1
1 0.03 0.016 0.03 1
1 1 1 1 1
```


