// main class of PoissonSolver
#include "Grid.hpp"
#include <iostream>

int main() {
	std::cout << "Hello PDE" << std::endl;
	grid_ns::Grid grid(5,5,1.0,1.0); //first we create the grid object on which to solve the problem

	int s = grid.size();
	int k = grid.index(3,5);
	std::cout << "Grid size: " << grid.size() << std::endl;
	std::cout << "Grid index (3,5) is index " << k << " in 1D" << std::endl;
	return 0;


}
