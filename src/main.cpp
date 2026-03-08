// main class of PoissonSolver
#include "grid.hpp"
#include "poissonsolver.hpp"
#include <iostream>

int main() {
	grid_ns::Grid grid(100,100, 1, 1); //first we create the grid object to map 2D to 1D
	//grid_ns::Grid::Index2D point {grid.cartesian_to_index2d(25,50)};
	//std::cout << "(" << point.i << ", " << point.j << ")\n";

	double dt{ 0.0001};
	double alpha{ 0.1};
	poisson_ns::PoissonSolver psolver(grid, dt, alpha);
	psolver.solve(1000);

	//psolver.solve(100); //advance the FTCS method 100 times
	//psolver.debug();
	return 0;


}
