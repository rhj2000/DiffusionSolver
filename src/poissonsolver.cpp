#include "poissonsolver.hpp"
#include "grid.hpp"
#include <iostream>

namespace poisson_ns {

//This class knows about the Grid class. It will use Grid to implement a stencil.

PoissonSolver::PoissonSolver(const grid_ns::Grid &g, double dt, double alpha) : grid_(g), dt_(dt), alpha_(alpha)
{
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
	//initialize with dirichlet boundary conditions
	for (int i{ 0 }; i < nx; i++) {
		u_[grid_.index(i, 0)] = 1.0; //left boundary
		u_[grid_.index(i, nx - 1)] = 1.0; //right boundary
	}

	for (int j{ 0 }; j < ny; j++) {
		u_[grid_.index(0, j)] = 1.0; //top boundary
		u_[grid_.index(ny - 1, j)] = 1.0; //bottom boundary
	}

}

void PoissonSolver::solve(int steps){
	int nx = grid_.nx();
	int ny = grid_.ny();
	double dx = grid_.dx();
	double dy = grid_.dy();

	//implement the stencil here (maybe later it can be put into another source file and namespace (stencil.ns?))
	//implement FTCS as the solver method
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

				//std::cout << k << " " << k_up << " " << k_right << " " << k_down << " " << k_left << '\n';
				u_new_[k] = u_[k] * dt_ + alpha_ * dt_ * ((u_[k_right] + u_[k_left] - 2 * u_[k]) / (dx * dx)
					+ (u_[k_up] + u_[k_down] - 2 * u_[k]) / (dy * dy));
			}
			
		}
		u_.swap(u_new_); //replaces u_ with its values at the next timestep, then we loop again
		setBoundaryConditions();
		debug();
	}
	

}

void PoissonSolver::debug(){
	//write the values in u_ in the form of a matrix to the console
	for (int i{ 0 }; i < grid_.nx(); ++i) {
		for (int j{ 0 }; j < grid_.ny(); ++j) {
			int k = grid_.index(i, j);
			std::cout << u_[k] << " ";
		}
		std::cout << '\n'; //move to next row
	}
	std::cout << '\n';
}

}
