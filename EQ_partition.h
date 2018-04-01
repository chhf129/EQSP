#pragma once
#include<iostream>
#include <opencv2/opencv.hpp>  '
#define matType CV_64F
#define _USE_MATH_DEFINES
#include <math.h>
const double pi = M_PI;
using namespace cv;


class EQSP
{
public:
	Mat eq_point_set_polar(int dim, int n);  //TODO: options
	EQSP(){};
	~EQSP(){};

//private:
	void eq_caps(int dim, int n, Mat& s_cap, Mat& n_regions);
	void printMat(Mat& temp);
	Mat polar_colat(int dim, int n);
	Mat area_of_ideal_region(int dim, const Mat& n);
	Mat area_of_sphere(const Mat& dim);
	Mat sradius_of_cap(int dim, const Mat& area);
	Mat createUnitMat(double input);
	Mat area_of_cap(int dim, const Mat& s_cap);
};
