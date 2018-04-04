#include "EQSP.h"

Mat EQSP::eq_point_set_polar(int dim, int n){
	return eq_point_set_polar(dim,n,false, 0);
}

Mat EQSP::eq_point_set_polar(int dim, int n, bool use_offset, double offset){


	if (dim<1 || dim>3 || n < 1){
		cout << "1<=dim<=3,n>=1" << endl;
	}
	Mat points_s;
	if (n == 1){
		points_s = Mat::zeros(dim, 1, matType);
		return points_s;
	}
	pair<Mat, Mat> result = eq_caps(dim, n);
	Mat a_cap = result.first;
	Mat n_regions = result.second;

	if (dim == 1){
		points_s = a_cap - pi / n;
		return points_s;
	}

	int n_collars = n_regions.cols - 2;
	points_s = Mat::zeros(dim, n, matType);

	Mat r;
	if (use_offset && dim == 3){
		r = Mat::eye(3, 3, matType);
	}
	if (dim == 2){
		offset = 0;
	}
//	int cache_size = floor(n_collars / 2.0);
	int cache_size = n_collars;              
	bool use_cache = dim >= 2;
	//use_cache = false;
	vector<Mat> cache;
	Mat points_1;
	int point_n = 2;
	for (int collar_n = 1; collar_n <= n_collars; collar_n++){
		double a_top = a_cap.at<double>(0, collar_n-1);
		double a_bot = a_cap.at<double>(0, collar_n);
		double n_in_collar = n_regions.at<double>(0, collar_n);
		cache.assign(cache_size, Mat(0, 0, matType));

		if (use_cache && !cache.empty()){
			int twin_collar_n = n_collars - collar_n+1;

			if (twin_collar_n <= cache_size &&
				cache[twin_collar_n-1].cols == n_in_collar){
				points_1 = cache[twin_collar_n-1];
			}
			else{
				points_1 = eq_point_set_polar(dim - 1, n_in_collar, use_offset, offset);
				cache.insert(cache.begin() + collar_n - 1, points_1);
				cache.erase(cache.begin() + cache.size()-1);//
			}
		}
		else{
			points_1 = eq_point_set_polar(dim - 1, n_in_collar, use_offset, offset);
		}

		if (use_offset && dim == 3 && collar_n > 1){
			r = s2_offset(points_1)*r;
			//TODO
		}
		double a_point = (a_top + a_bot) / 2;
		int point_1_n = points_1.cols;
		int k = 0;
		for (int i = 1; i <= dim - 1; i++){
			for (int j = point_n; j <= point_1_n + point_n - 1; j++){
				if (dim == 2){
					points_s.at<double>(i - 1, j - 1) = fmod(points_1.at<double>(i - 1, j - point_n) + 2 * pi*offset, pi * 2);
				}
				else{
					points_s.at<double>(i - 1, j - 1) = points_1.at<double>(i - 1, j - point_n);
				}
				points_s.at<double>(dim - 1, j-1) = a_point;
			}
		}
		offset += circle_offset(n_in_collar, n_regions.at<double>(0, 1 + collar_n), use_offset);
		offset -= floor(offset);
		point_n += points_1.cols;

	}
	points_s.col(point_n - 1) = 0;
	points_s.at<double>(dim - 1, point_n - 1) = pi;

	return points_s;
}

pair<Mat, vector<Mat>> EQSP::eq_regions(int dim, int n, bool use_offset, double offset){
	return eq_regions(dim, n, false, 0);
}


pair<Mat, vector<Mat>> EQSP::eq_regions(int dim, int n, bool use_offset, double offset){
	if (dim<1 || dim>3 || n < 1){
		cout << "1<=dim<=3,n>=1" << endl;
	}
	vector<Mat> dim_1_rot(n);
	Mat regions;
	if (n == 1){
		
	}

}


