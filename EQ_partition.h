#pragma once
#include<iostream>
#include <opencv2/opencv.hpp>  '
#define matType CV_32FC1
using namespace cv;
class EQSP
{
public:
	Mat eq_point_set_polar(int dim, int n);  //TODO: options
	EQSP(){};
	~EQSP(){};

private:
	void eq_caps(int dim, int n, Mat& s_cap, Mat& n_regions);
};
