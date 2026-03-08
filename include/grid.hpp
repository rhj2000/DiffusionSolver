#pragma once

namespace grid_ns {

	class Grid {

	private:
		int nx_, ny_;
		double lx_, ly_, dx_, dy_;
		//nx_ number of grid points in x
		//ny_ number of grid points in y
		//lx_ physical length in x
		//ly_ physical length in y
		//dx_ calculated spacing in x
		//dy_ calculated spacing in y

	public:
		//First, initialize the grid object
		//Constructor in grid source will handle instance(s)
		Grid(int nx, int ny, double lx, double ly); //could declare empty?

		//we should be able to read back out some of these values
		int nx() const { return nx_; }
		int  ny() const { return ny_; }
		double lx() const { return lx_; }
		double ly() const { return ly_; }
		double dx() const { return dx_; }
		double dy() const { return dy_; }

		int size() const; //define the size variable which will return nx_ * ny_

		int index(int i, int j) const; //define the method that converts subscripts to linear indices

		struct Index2D { //struct for (x,y) -> (i,j) helper function
			int i;
			int j;
		};

		const Index2D cartesian_to_index2d(int x, int y); // (x,y) coordinate helper function

	};

}


