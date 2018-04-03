#include "EQSP.h"


void EQSP::printMat(Mat& temp){
	/*
	MatIterator_<double> it = temp.begin<double>();
	MatIterator_<double> itend = temp.end<double>();
	while (it != itend){
		std::cout << *it<<std::endl;;
		++it;
	}
	*/
	std::cout << temp  << std::endl;
	std::system("pause");
}

void EQSP::matPow(Mat& base, double exp){
	MatIterator_<double> it = base.begin<double>();
	MatIterator_<double> itend = base.end<double>();

	while (it != itend){
		*it = pow(*it, exp);
		++it;
	}

}

std::pair<Mat,Mat> EQSP::eq_caps(int dim, int n){
	Mat s_cap, n_regions;

	if (dim == 1){
		Mat sector(Mat::zeros(1, n, matType));

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
	}

	else if (n == 1){
		s_cap = createUnitMat(pi);
		n_regions = createUnitMat(1);
	}

	else{
		Mat c_polarM(polar_colat(dim, n));
		double c_polar = c_polarM.at<double>(0, 0);
		int n_collars= num_collars(createUnitMat(n), c_polarM, ideal_collar_angle(dim, createUnitMat(n))).at<double>(0,0);
		Mat r_regions(ideal_region_list(dim, n, c_polar, n_collars));
		n_regions= round_to_naturals(r_regions);
		s_cap=cap_colats(dim, n, c_polar, n_regions);
	}

	return std::make_pair(s_cap,n_regions);

}

Mat EQSP::polar_colat(int dim, int n){
	Mat c_polar;

	if (n > 2){
		c_polar = sradius_of_cap(dim, area_of_ideal_region(dim, createUnitMat(n)));
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
				//CAUTION
				std::pair<double, double> result = boost::math::tools::bisect(
					[&](double s){ return area_of_cap(dim, createUnitMat(s)).at<double>(0, 0) - ak; }, 0.0, pi, boost::math::tools::eps_tolerance<double>());
				double sk = (result.first + result.second) / 2;
				
				if (flipped == true){
					s_cap.at<double>(0, k) = pi-sk;
				}
				else{
					s_cap.at<double>(0, k) = sk;
				}
			}
		}
	}
	return s_cap;
}
 
Mat EQSP::area_of_cap(int dim, const Mat& s_cap){
	Mat area(s_cap.size(), matType);
	MatIterator_<double> itA = area.begin<double>();
	MatIterator_<double> itend = area.end<double>();
	MatConstIterator_<double> itS = s_cap.begin<double>();
	double dim2 = (double)dim / 2;
	switch (dim){
	case 1:
		area = 2 * s_cap;
		break;
	case 2:
		while (itA != itend){
			*itA = 4 * pi*pow(sin(*itS / 2), 2);
			++itA;
			++itS;
		}
		break;
	case 3:
		bool pole;
		while (itA != itend){
			pole = *itS<pi / 6 || *itS>pi * 5 / 6;
			if (pole == true){
				*itA = area_of_sphere(createUnitMat(dim)).at<double>(0, 0)*boost::math::ibeta(dim2, dim2, pow(sin(*itS / 2), 2));
			}
			else{
				*itA = (*itS*2 - sin(*itS*2))*pi;
			}
			//std::cout << *itS;
			++itA;
			++itS;
		}
		break;
	default:
		while (itA != itend){
			*itA = area_of_sphere(createUnitMat(dim)).at<double>(0, 0)*boost::math::ibeta(dim2, dim2, pow(sin(*itS / 2), 2));
			++itA;
			++itS;
		}
	}

	return area;
}

Mat EQSP::ideal_collar_angle(int dim, const Mat& n){
	Mat angle(area_of_ideal_region(dim, n));
	matPow(angle, 1 / (double)dim);
	return angle;
}

Mat EQSP::num_collars(const Mat& n, Mat& c_polar, const Mat& a_ideal){
	//TODO: length check
	Mat n_collars(Mat::zeros(n.size(), matType));
	auto itN = n.begin<double>();
	auto itC = c_polar.begin<double>();
	auto itA = a_ideal.begin<double>();
	auto itNcollar = n_collars.begin<double>();
	auto itend = n_collars.end<double>();

	while (itNcollar != itend){
		if (*itN > 2 && *itA > 0){
			*itNcollar = std::max(1.0, round((pi - *itC *2) / *itA));
		}
		++itN;
		++itC;
		++itA;
		++itNcollar;
	}
	return n_collars;

}

Mat EQSP::ideal_region_list(int dim, int n, double c_polar, int n_collars){
	Mat r_regions(Mat::zeros(1, 2 + n_collars,matType));
	r_regions.at<double>(0, 0) = 1;
	if (n_collars > 0){
		double a_fitting = (pi - 2 * c_polar) / (double)n_collars;
		double ideal_region_area = area_of_ideal_region(dim, createUnitMat(n)).at<double>(0, 0);
		for (int i = 1; i <= n_collars; i++){
			double ideal_collar_area = area_of_collar(dim, createUnitMat(c_polar + (i - 1)*a_fitting), createUnitMat(c_polar + i*a_fitting)).at<double>(0,0);
			r_regions.at<double>(0, i) = ideal_collar_area / ideal_region_area;
		}
	}
	r_regions.at<double>(0, 1 + n_collars) = 1;

	return r_regions;
}

Mat EQSP::area_of_collar(int dim, const Mat& a_top, const Mat& a_bot){
	return area_of_cap(dim, a_bot) - area_of_cap(dim, a_top);
}

Mat EQSP::round_to_naturals(const Mat& r_regions){
	Mat n_regions(r_regions);
	double discrepancy = 0;
	MatIterator_<double> itN = n_regions.begin<double>();
	MatIterator_<double> itend = n_regions.end<double>();
	MatConstIterator_<double> itR = r_regions.begin<double>();

	while (itN != itend){
		*itN = round(*itR + discrepancy);
		discrepancy = discrepancy + *itR - *itN;
		++itN;
		++itR;
	}

	return n_regions;
}

Mat EQSP::cap_colats(int dim, int n, double c_polar, const Mat& n_regions){
	Mat c_caps(n_regions.size(), matType);
	c_caps.at<double>(0, 0) = c_polar;
	c_caps.at<double>(0, c_caps.cols-1) = pi;
	double ideal_region_area = area_of_ideal_region(dim, createUnitMat(n)).at<double>(0, 0);
	double subtotal_n_regions = 1;
	for (int i = 1; i < c_caps.cols - 1; ++i){
		subtotal_n_regions += n_regions.at<double>(0, i);
		c_caps.at<double>(0, i) = sradius_of_cap(dim, createUnitMat(subtotal_n_regions*ideal_region_area)).at<double>(0, 0);
	}
	return c_caps;
}