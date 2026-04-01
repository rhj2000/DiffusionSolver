#pragma once
#include<vector>

namespace io_ns {

	class ConsoleWriter {

	public:

		static void print_ascii(const std::vector<double>& vect, int nx, int ny);
		static void print_ascii(const std::vector<double>& vect, int nx, int ny, int nz, int t, int k);
		//void print_heatmap
		//void print_color

	private:


	};
}