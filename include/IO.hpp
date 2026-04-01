    #pragma once
#include <vector>
#include <string>
#include <string_view>

namespace io_ns {

	class CSVWriter {
			
	public: 
		CSVWriter(std::string_view filename); //csvwriter initialized with reference to filename

		void vector_to_csv(const std::vector<double>& vect, int dim_x, int dim_y);

	private:
		std::string file_;

	};

	class CSVWriter3D {
	
	public:
		CSVWriter3D(std::string_view filename);

		void vector_to_csv3d(const std::vector<double>& vect, int dim_x, int dim_y, int dim_z);

	private:
		std::string file_;


	};

	class VTKWriter {

	public:

		VTKWriter(std::string_view filename);

		void write_vtk(
			const std::vector<double>& vect,
			int dim_x, int dim_y, int dim_z,
			double dx, double dy, double dz);

	private:
		std::string file_;

	};
}