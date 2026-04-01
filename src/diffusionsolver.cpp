#define DEBUG //Comment in when debugging
#include "diffusionsolver.hpp"
#include "grid.hpp"
#include "io.hpp"
#include "consolewriter.hpp"
#include <iostream>
#include <fstream>

namespace diffusion_ns {

	//This class knows about the Grid class. It will use Grid to implement a stencil.

	DiffusionSolver::DiffusionSolver(const grid_ns::Grid& g, double dt, double alpha) : grid_(g), dt_(dt), alpha_(alpha)
	{
		double stability = grid_.dx() * grid_.dy() / (4 * alpha_);

		std::cout << "timestep: " << dt_ << '\n';
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

	void DiffusionSolver::setBoundaryConditions() {
		int nx = grid_.nx();
		int ny = grid_.ny();
		//initialize with dirichlet boundary conditions (won't change at any point in the simulation)

		for (int i{ 0 }; i < nx; i++) {
			u_[grid_.index(i, 0)] = 0; //left boundary
			u_[grid_.index(i, nx - 1)] = 0; //right boundary
		}

		for (int j{ 0 }; j < ny; j++) {
			u_[grid_.index(0, j)] = 0; //top boundary
			u_[grid_.index(ny - 1, j)] = 0; //bottom boundary
		}


	}

	double DiffusionSolver::laplacian(int i, int j) const {
		int k = grid_.index(i, j); //the 2D->1D mapping at the core of the grid class
		int k_up = grid_.index(i, j - 1);
		int k_right = grid_.index(i + 1, j);
		int k_down = grid_.index(i, j + 1);
		int k_left = grid_.index(i - 1, j);
		double dx = grid_.dx();
		double dy = grid_.dy();

		return ((u_[k_right] + u_[k_left] - 2 * u_[k]) / (dx * dx)
			+ (u_[k_up] + u_[k_down] - 2 * u_[k]) / (dy * dy));

	}

	double DiffusionSolver::source(int i, int j) const {
		int nx = grid_.nx();
		int ny = grid_.ny();
		grid_ns::Grid::Index2D point1 = grid_.cartesian_to_index2d(nx / 4,  ny / 2);
		grid_ns::Grid::Index2D point2 = grid_.cartesian_to_index2d(nx / 2, ny / 4);
		grid_ns::Grid::Index2D point3 = grid_.cartesian_to_index2d(nx / 2, 3 * ny / 4);
		grid_ns::Grid::Index2D point4 = grid_.cartesian_to_index2d(5 * nx / 8, ny / 2);
		grid_ns::Grid::Index2D point5 = grid_.cartesian_to_index2d(7 * nx / 8, 3 * ny / 4);

		if (i == point1.i && j == point1.j) {
			return double{ 10.0 };
		}
		else if (i == point2.i && j == point2.j) {
			return double{ -10.0 };
		}
		else if (i == point3.i && j == point3.j) {
			return double{ -10.0 };
		}
		else if (i == point4.i && j == point4.j) {
			return double{ -25.0 };
		}
		else if (i == point5.i && j == point5.j) {
			return double{ 25.0 };
		}
		else
			return double{ 0.0 };
	}

	void DiffusionSolver::solve(int steps) {
		int nx = grid_.nx();
		int ny = grid_.ny();
		double dx = grid_.dx();
		double dy = grid_.dy();

		for (int t{ 0 }; t < steps; t++) {
			for (int i{ 1 }; i < ny - 1; i++) {
				for (int j{ 1 }; j < nx - 1; j++) {
					int k = grid_.index(i, j);
					u_new_[k] = u_[k] + source(i, j) * dt_ + alpha_ * dt_ * laplacian(i, j);

				}

			}
			u_.swap(u_new_);
			setBoundaryConditions();

		}
#ifdef DEBUG
		//debug();
		io_ns::CSVWriter csvwriter("Sample.csv");
		csvwriter.vector_to_csv(u_, nx, ny);
#endif
	    io_ns::ConsoleWriter::print_ascii(u_, grid_.nx(), grid_.ny());


	}

	void DiffusionSolver::debug() {
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
