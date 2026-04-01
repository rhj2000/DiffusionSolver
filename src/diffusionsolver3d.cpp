#define DEBUG
#include "diffusionsolver3d.hpp"
#include "grid3d.hpp"
#include "io.hpp"
#include <iostream>
#include <fstream>



namespace diffusion_ns {

	DiffusionSolver3D::DiffusionSolver3D(const grid_ns::Grid3D& g, double dt, double alpha) : grid_(g), dt_(dt), alpha_(alpha)
	{

		double stability = grid_.dx() * grid_.dy() / (4 * alpha_);

		std::cout << "timestep: " << dt_ << '\n';
		std::cout << "(1/4)*dx^2 / D = " << stability << '\n';
		std::cout << "timestep must be leq to stability criterion." << '\n';

		int N = grid_.size();
		u_.resize(N);
		u_new_.resize(N);
		

		//initialize u with zeros
		for (int idx{ 0 }; idx < N; ++idx) {
			u_[idx] = 0.0;
		}

		setBoundaryConditions3D();
	}

	void DiffusionSolver3D::setBoundaryConditions3D() {
		int nx = grid_.nx();
		int ny = grid_.ny();
		int nz = grid_.nz();
		//initialize with dirichlet boundary conditions (won't change at any point in the simulation)
		for (int i{ 0 }; i < ny; ++i) {
			for (int j{ 0 }; j < nx; ++j) {
				u_[grid_.index(i, j, 0)] = 0; //front boundary
				u_[grid_.index(i, j, nz - 1)] = 0; //back boundary
			}
			
		}

		for (int j{ 0 }; j < nx; ++j) {
			for (int k{ 0 }; k < nz; ++k) {
				u_[grid_.index(0, j, k)] = 0; //top boundary
				u_[grid_.index(ny - 1, j, k)] = 0; //bottom boundary
			}

		}

		for (int i{ 0 }; i < ny; ++i) {
			for (int k{ 0 }; k < nz; ++k) {
				u_[grid_.index(i, 0, k)] = 0; //left boundary
				u_[grid_.index(i, nx - 1, k)] = 0; //right boundary
			}

		}

	}

	double DiffusionSolver3D::laplacian3D(int i, int j, int k) const {
		int idx = grid_.index(i, j, k); //the 2D->1D mapping at the core of the grid class
		int k_up = grid_.index(i, j - 1, k);
		int k_right = grid_.index(i + 1, j, k);
		int k_down = grid_.index(i, j + 1, k);
		int k_left = grid_.index(i - 1, j, k);
		int k_in = grid_.index(i, j, k + 1);
		int k_out = grid_.index(i, j, k - 1);


		double dx = grid_.dx();
		double dy = grid_.dy();
		double dz = grid_.dz();

		return ( (u_[k_right] + u_[k_left] - 2 * u_[idx]) / (dx * dx)
			+ (u_[k_up] + u_[k_down] - 2 * u_[idx]) / (dy * dy)
			+ (u_[k_in] + u_[k_out] - 2 * u_[idx]) / (dz * dz) );
	}

	double DiffusionSolver3D::source3D(int i, int j, int k) const {
		int nx = grid_.nx();
		int ny = grid_.ny();
		int nz = grid_.nz();
		grid_ns::Grid3D::Index3D point1 = grid_.cartesian_to_index3d(nx / 2, ny / 2, nz / 2);
		//grid_ns::Grid3D::Index3D point2 = grid_.cartesian_to_index3d(nx / 2, ny / 2);
		//grid_ns::Grid3D::Index3D point3 = grid_.cartesian_to_index3d(3 * nx / 4, ny / 4);

		if (i == point1.i && j == point1.j && k == point1.k) {
			return double{ 10000.0 };
		}
		else
			return double{ 0.0 };
	}

	void DiffusionSolver3D::solve3D(int steps) {
		int nx = grid_.nx();
		int ny = grid_.ny();
		int nz = grid_.nz();
		double dx = grid_.dx();
		double dy = grid_.dy();
		double dz = grid_.dz();

		for (int t{ 0 }; t < steps; t++) {
			for (int k{ 1 }; k < nz - 1; ++k){
				for (int i{ 1 }; i < ny - 1; ++i) {
					for (int j{ 1 }; j < nx - 1; ++j) 
					{
						int idx = grid_.index(i, j, k);
						u_new_[idx] = u_[idx] + source3D(i, j, k) * dt_ + alpha_ * dt_ * laplacian3D(i, j, k);
					}
				}

			}
			u_.swap(u_new_);
			setBoundaryConditions3D();
			std::cout << "t: " << t << "/" << steps << '\n';
		}

		for (int i{ 0 }; i < grid_.ny(); ++i) {
			for (int j{ 0 }; j < grid_.nz(); ++j) {
				int idx = grid_.index(i, j, 12);
				std::cout << u_[idx] << ' ';
			}
			std::cout << '\n'; //move to next row
		}
		std::cout << '\n';

		io_ns::CSVWriter3D csv_writer("sample3D.csv");
		csv_writer.vector_to_csv3d(u_, grid_.nx(), grid_.ny(), grid_.nz());

		io_ns::VTKWriter vtk_writer("sample3D.vtk");
		vtk_writer.write_vtk(u_, grid_.nx(), grid_.ny(), grid_.nz(), grid_.dx(), grid_.dy(), grid_.dz());
	}
}