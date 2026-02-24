#pragma once

namespace grid_ns {
	class Grid; //forward declaration of Grid tells the compiler that Grid exists 
}

namespace poisson_ns {

class PoissonSolver {

public:

	//PoissonSolver(const grid_ns::Grid &g) : grid_(g) {}
	//PoissonSolver(const grid_ns::Grid &g);
	PoissonSolver(const grid_ns::Grid &g);
	void solve();

private:
	const grid_ns::Grid &grid_;

};

}
