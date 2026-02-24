cmake_minimum_required(VERSION 3.10)
project(PoissonSolver)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include your own headers
include_directories(include)

# Find Eigen (must be installed in WSL)
find_package(Eigen3 REQUIRED)

# Create executable
add_executable(poisson_solver
    src/main.cpp
    src/Grid.cpp
    src/PoissonSolver.cpp
)

# Link Eigen (header-only, modern way)
target_link_libraries(poisson_solver Eigen3::Eigen)
