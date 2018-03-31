#include "EQ_partition.h"
#include <vector>

void EQSP::eq_caps(int dim, int n, Mat& s_cap, Mat& n_regions){
	
	
	if (dim == 1){
	//	Mat sector(1, n, CV_8UC1);
	//	uchar* pointer = sector.ptr<uchar>(0);
	//	for (int i = 0; i < sector.cols; i++)
	//		pointer[i] = i+1;
		std::vector<int> sector(n);
		for (int i = 0; i < n; i++)
			sector.push_back(i);
		s_cap
	}
}