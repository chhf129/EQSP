#pragma once
#define _USE_MATH_DEFINES
#define matType CV_64F

#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>  
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/tools/roots.hpp>

const double pi = M_PI;



using namespace cv;
using namespace std;


class EQSP
{
public:
	EQSP(){};
	~EQSP(){};

	Mat eq_point_set_polar(int dim, int n);
	Mat eq_point_set_polar(int dim, int n, bool use_offset, double offset);  //TODO: options


	//private:
	pair<Mat, Mat> eq_caps(int dim, int n);
	void matPow(Mat& base, double exp);
	void printMat(Mat& temp);
	Mat polar_colat(int dim, int n);
	Mat area_of_ideal_region(int dim, const Mat& n);
	Mat area_of_sphere(const Mat& dim);
	Mat sradius_of_cap(int dim, const Mat& area);
	Mat createUnitMat(double input);
	Mat area_of_cap(int dim, const Mat& s_cap);
	Mat ideal_collar_angle(int dim, const Mat& n);
	Mat num_collars(const Mat& n, Mat& c_polar, const Mat& a_ideal);
	Mat ideal_region_list(int dim, int n, double c_polar, int n_collars);
	Mat area_of_collar(int dim, const Mat& a_top, const Mat& a_bot);
	Mat round_to_naturals(const Mat& r_regions);
	Mat cap_colats(int dim, int n, double c_polar, const Mat& n_regions);
	Mat s2_offset(const Mat& points_1);
};