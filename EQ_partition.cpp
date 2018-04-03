#include "EQSP.h"

Mat EQSP::eq_point_set_polar(int dim, int n){
	return eq_point_set_polar(false, 0);
}

Mat EQSP::eq_point_set_polar(int dim, int n, bool use_offset, double offset){
	Mat points_s;
	if (dim<1 || dim>3 || n < 1){
		cout << "1<=dim<=3,n>=1" << endl;
	}

	if (n == 1){
		points_s = Mat::zeros(dim, 1, matType);
		return points_s;
	}
	pair<Mat, Mat> result = eq_caps(dim, n);
	Mat a_cap = result.first;
	Mat n_regions = result.second;

	if (dim == 1){
		points_s = a_cap - pi / n;
	}
	else{
		int n_collars = n_regions.cols - 2;
		points_s = Mat::zeros(dim, n, matType);
		int point_n = 2;
		Mat r;
		if (use_offset && dim == 3){
			r = Mat::eye(3, 3, matType);
		}
		if (dim == 2){
			offset = 0;
		}



		double cache_size;
		bool use_cache = dim >= 2;
		vector<Mat> cache;
		if (use_cache){
			cache_size = floor(n_collars / 2.0);
			cache.resize(cache_size);
		}
		Mat points_1;
		for (int collar_n = 0; collar_n < n_collars; collar_n++){
			double a_top = a_cap.at<double>(0, collar_n);
			double a_bot = a_cap.at<double>(0, collar_n + 1);
			double n_in_collar = n_regions.at<double>(0, collar_n + 1);
			if (use_cache){
				int twin_collar_n = n_collars - collar_n - 1;
				if (twin_collar_n < cache_size &&
					cache[twin_collar_n].cols == n_in_collar){
					points_1 = cache[twin_collar_n];
				}
				else{
					points_1 = eq_point_set_polar(dim - 1, n_in_collar, use_offset, offset);
					cache[collar_n] = points_1;
				}
			}
			else{
				points_1 = eq_point_set_polar(dim - 1, n_in_collar, use_offset, offset);
			}

			if (use_offset && dim == 3 && collar_n > 1){
				
			}
		}
	}


	return points_s;
}




