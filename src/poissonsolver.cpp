#include "poissonsolver.hpp"
#include "grid.hpp"
#include <iostream>
#include <fstream>

namespace poisson_ns {

//This class knows about the Grid class. It will use Grid to implement a stencil.

PoissonSolver::PoissonSolver(const grid_ns::Grid &g, double dt, double alpha) : grid_(g), dt_(dt), alpha_(alpha)
{
	double stability = grid_.dx() * grid_.dx() / (4*alpha);
	std::cout << "timestep: " << dt << '\n';
	std::cout << "(1/4)*dx^2 / D = " << stability << '\n';
	std::cout << "timestep must be leq to stability criterion." << '\n';

	int N = grid_.size();
	u_.resize(N);
	u_new_.resize(N);
	int nx = grid_.nx();
	int ny = grid_.ny();

	//initialize u with zeros
	for (int k{ 0 }; k < N; k++) {
		u_[k] = 0.0;
	}

	setBoundaryConditions();

}

void PoissonSolver::setBoundaryConditions() {
	int nx = grid_.nx();
	int ny = grid_.ny();
	//initialize with dirichlet boundary conditions (won't change at any point in the simulation)
	/*
	for (int i{ 0 }; i < nx; i++) {
		u_[grid_.index(i, 0)] = 1.0; //left boundary
		u_[grid_.index(i, nx - 1)] = 1.0; //right boundary
	}

	for (int j{ 0 }; j < ny; j++) {
		u_[grid_.index(0, j)] = 1.0; //top boundary
		u_[grid_.index(ny - 1, j)] = 1.0; //bottom boundary
	}
	*/

}

void PoissonSolver::solve(int steps){
	int nx = grid_.nx();
	int ny = grid_.ny();
	double dx = grid_.dx();
	double dy = grid_.dy();

	//implement the stencil here (maybe later it can be put into another source file and namespace (stencil.ns?))
	//implement FTCS as the solver method
	//recall that (i,j) -> (row, column)
	//this will have to be transposed for mapping to (x,y)
	//as right now, (i,j) -> (row, column) -> (y, x)
	for (int t{ 0 }; t < steps; t++) {
		for (int i{ 1 }; i < nx - 1; i++) {
			for (int j{ 1 }; j < ny - 1; j++) {
				//can try to build a tensor object from scratch later
				//for now, let's just generate u_ and u_new 
				int k = grid_.index(i, j); //the 2D->1D mapping at the core of the grid class
				int k_up = grid_.index(i, j - 1);
				int k_right = grid_.index(i + 1, j);
				int k_down = grid_.index(i, j + 1);
				int k_left = grid_.index(i - 1, j);

				double s = 0.0;
				if (i == nx/4) {
					if (j == ny / 2) {
						s = 10.0;
					}
				}
				if (i == nx / 2) {
					if (j == ny / 4) {
						s = -10.0;
					}
				}
				if (i == nx / 2) {
					if (j == 3*ny / 4) {
						s = -10.0;
					}
				}	

				if (i == 3*nx / 4) {
					if (j == ny / 2) {
						s = 10.0;
					}
				}

				//test charge
				if (i == nx / 2) {
					if (j == ny / 2) {
						s = 0;
					}
				}
				

				//std::cout << k << " " << k_up << " " << k_right << " " << k_down << " " << k_left << '\n';
				u_new_[k] = u_[k] + s * dt_ + alpha_ * dt_ * ((u_[k_right] + u_[k_left] - 2 * u_[k]) / (dx * dx)
					+ (u_[k_up] + u_[k_down] - 2 * u_[k]) / (dy * dy));
			}
			
		}
		u_.swap(u_new_); //replaces u_ with its values at the next timestep, then we loop again
		setBoundaryConditions();
		//debug();
	}
	//output must be transposed since index (i,j) -> (y,x) when we plot

	std::vector<double> u_T(nx * ny);

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {

			int k = grid_.index(i, j);
			int kT = j*ny + i;  // transposed index

			u_T[kT] = u_[k];
		}
	}

	u_.swap(u_T);

	std::ofstream outputFile("u.csv");
	for (int i{ 0 }; i < nx; i++) {
		for (int j{ 0 }; j < ny; j++) {
			int k = grid_.index(i, j);
			outputFile << u_[k];
			// Add a comma if it's not the last element in the row
			if (j < nx) {
				outputFile << ",";
			}
		}
		// Add a newline character at the end of each row
		outputFile << "\n";
	}
	

}

void PoissonSolver::debug(){
	//write the values in u_ in the form of a matrix to the console
	for (int i{ 0 }; i < grid_.nx(); ++i) {
		for (int j{ 0 }; j < grid_.ny(); ++j) {
			int k = grid_.index(i, j);
			std::cout << u_[k] << ' ';
		}
		std::cout << '\n'; //move to next row
	}
	std::cout << '\n';
}

}
