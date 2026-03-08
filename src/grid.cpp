#include "grid.hpp"
#include <iostream>

namespace grid_ns {

	//Grid constructor: initialization list assigns nx,ny,lx,ly to nx_,ny_,lx_,ly_ respectively
	Grid::Grid(int nx, int ny, double lx, double ly) : nx_(nx), ny_(ny), lx_(lx), ly_(ly)
	{
		if (nx_ < 1 || ny_ < 1 || lx_ <= 0 || ly_ <= 0) {
			throw std::invalid_argument("Grid parameters invalid");
		}

		dx_ = lx / (nx - 1); //no need to declare type in constructor. header defines the type
		dy_ = ly / (ny - 1);
	}


	int Grid::size() const
	{
		return nx_ * ny_;
	}

	int Grid::index(int i, int j) const
	{
		// (i,j) -> (row, column) -> (y, x)
		return i * nx_ + j;
	}

	const Grid::Index2D Grid::cartesian_to_index2d(int x, int y) {
		return { nx_ - y, x };
	}
}
