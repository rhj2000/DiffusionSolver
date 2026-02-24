#include "PoissonSolver.hpp"
#include "Grid.hpp"

namespace poisson_ns {

//This class knows about the Grid class. It will use Grid to implement a stencil.

PoissonSolver::PoissonSolver(const grid_ns::Grid &g) : grid_(g) {}

void PoissonSolver::solve()
{
	//create local variables storing grid data
	double dx = grid_.dx();
{

}
