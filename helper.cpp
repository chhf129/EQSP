#include "EQ_partition.h"
#include <vector>


void EQSP::printMat(Mat& temp){
	MatIterator_<double> it = temp.begin<double>();
	MatIterator_<double> itend = temp.end<double>();
	while (it != itend){
		std::cout << *it<<std::endl;;
		++it;
	}
	std::system("pause");
}



void EQSP::eq_caps(int dim, int n, Mat& s_cap, Mat& n_regions){
	
	
	if (dim == 1){
		Mat sector = Mat::zeros(1, n, matType);

		MatIterator_<double> it = sector.begin<double>();
		MatIterator_<double> itend = sector.end<double>();
		int i = 1;
		while (it != itend){
			*it = i;
			++it;
			++i;
		}

		s_cap = sector * 2 * pi / n;
		n_regions = Mat::ones(sector.size(), matType);

	//	Mat temp(sector * 2 * pi / n);
	//	Mat temp2 = Mat::ones(sector.size(), CV_8U);
	//	temp.copyTo(s_cap);
	//	temp2.copyTo(n_regions);
	}

	else if (n == 1){
		createUnitMat(pi).copyTo(s_cap);
		createUnitMat(1).copyTo(n_regions);
	}

	else{
		//TODO
	}

	
	
}



Mat EQSP::polar_colat(int dim, int n){
	Mat c_polar;

	if (n > 3){
		//TOD
	}
	else{
		c_polar.create(1, 1, matType);
		if (n == 1){
			c_polar.at <double>(0, 0) = pi;
		}
		else if (n == 2){
			c_polar.at <double>(0, 0) = pi / 2;
		}
	}
	return c_polar;
}


Mat EQSP::area_of_ideal_region(int dim, const Mat& n){
	Mat area(n.size(), matType);
	MatIterator_<double> it = area.begin<double>();
	MatIterator_<double> itend = area.end<double>();
	MatConstIterator_<double> itN = n.begin<double>();
	
	double aOfSphere = area_of_sphere(createUnitMat(dim)).at<double>(0, 0);

	while (it != itend){
		*it = aOfSphere / *itN;
		++it;
		++itN;
	}
	//double area = area_of_sphere(dim) / n;
	return area;
}

Mat EQSP::createUnitMat(double input){
	Mat temp(1, 1, matType);
	temp.at < double >(0, 0) = input;
	return temp;
}


Mat EQSP::area_of_sphere(const Mat& dim){
	Mat area(dim.size(),matType);
	MatConstIterator_<double> it = dim.begin<double>();
	MatConstIterator_<double> itend = dim.end<double>();
	MatIterator_<double> itA = area.begin<double>();
	
	double power;
	while (it != itend){
		power=(*it+1)/2;
		*itA = 2 * pow(pi, power) / tgamma(power);
		++it;
		++itA;
	}
	return area;
}

Mat EQSP::sradius_of_cap(int dim, const Mat& area){
	Mat s_cap(area.size(), matType);

	MatConstIterator_<double> it = area.begin<double>();
	MatConstIterator_<double> itend = area.end<double>();

	
	if (dim == 1){
		s_cap=area/2;
	}
	else if (dim == 2){
		MatIterator_<double> itS = s_cap.begin<double>();
		while (it != itend){
			*itS = (2 * asin(sqrt(*it/ pi) / 2));
			++it;
			++itS;
		}
	}
	else{
		double as = area_of_sphere(createUnitMat(dim)).at<double>(0, 0);
		double ak;
		bool flipped;
		for (int k = 0; k < area.cols; k++){
			ak = area.at<double>(0, k);
			if (ak >= as){
				s_cap.at<double>(0, k) = pi;
			}
			else{
				if (2 * ak>as){
					ak = as - ak;
					flipped = true;
				}
				else flipped = false;

				//double sk = area_of_cap(dim, ak);

			}
		}
	}
	return s_cap;
}

Mat area_of_cap(int dim, const Mat& s_cap){
	Mat area(s_cap.size(), matType);
	switch (dim){
	case 1:
		area = 2 * s_cap;
		break;
	case 2:
		MatIterator_<double> itA = area.begin<double>();
		MatIterator_<double> itend = area.end<double>();
		MatConstIterator_<double> itS = s_cap.begin<double>();
		while (itA != itend){
			*itA = 4 * pi*pow(sin(*itS / 2), 2);
			++itA;
			++itS;
		}
	case 3:


	}

}