#include "EQSP.h"

int main(){
	
	EQSP eqsp;
	Mat n_regions = Mat::zeros(1, 6, matType);
	MatIterator_<double> it = n_regions.begin<double>();
	MatIterator_<double> itend = n_regions.end<double>();
	int i = 1;

	while (it != itend){
		*it = i;
		++it;
		++i;
	}
	int dim = 3;
	int n = 10;
	double c_polar = 1.5;
	double area = 1.5;
	Mat s_cap = Mat::ones(1, 5, matType);
	s_cap.at<double>(0, 0) = 0;
	s_cap.at<double>(0, 1) = 4.9348;
	s_cap.at<double>(0, 2) = 9.8696;
	s_cap.at<double>(0, 3) = 14.8044;
	s_cap.at<double>(0, 4) = 19.7392;
//	vector<Mat> v;
//	v.assign(5, Mat(0, 0, matType));
	//v.insert(v.begin()+6, s_cap);



	//copy(v.begin(), v.end(), ostream_iterator<Mat>(cout, "\n"));
///	temp.assign(10, 4);
	//temp.erase(temp.begin() + temp.size()-1);
//	temp.insert(temp.begin() + 3, 1);
	//cout << temp[0] << temp[1] << temp[2] << temp[3] << temp[4] << temp[5]<< temp.size()<<endl;
//	temp.erase(temp.begin() + 3);
//	cout << temp[0] << temp[1] << temp[2] << temp[3] << temp[4] << temp[5] << temp.size() << endl;

	//eqsp.printMat(eqsp.eq_caps(2,3));
	eqsp.printMat(eqsp.eq_point_set_polar(3, 50));



	//eqsp.printMat(eqsp.cap_colats(dim,n,c_polar,n_regions));
	//eqsp.printMat(eqsp.cap_colats(dim, n, c_polar, n_regions));
	//eqsp.printMat(eqsp.round_to_naturals(n_regions));
	//eqsp.printMat(eqsp.sradius_of_cap(1,eqsp.createUnitMat(1.5)));
	//	eqsp.printMat(eqsp.sradius_of_cap(2, eqsp.createUnitMat(1.5)));
	//eqsp.printMat(eqsp.ideal_region_list(3, 10, 0.6435, 4));
	//eqsp.printMat(eqsp.area_of_cap(1, s_cap));
	//std::cout<<eqsp.num_collars(eqsp.createUnitMat(10), eqsp.createUnitMat(0.6435), eqsp.ideal_collar_angle(2, eqsp.createUnitMat(10))).at<double>(0, 0);
	//	auto result=eqsp.eq_caps(2, 3);
	 // eqsp.printMat(result.first);
	//	eqsp.printMat(result.second);

	//eqsp.printMat(eqsp.sradius_of_cap(3, s_cap));
	//std::cout << eqsp.circle_offset(2, 2, true)<<endl;
	//std::system("pause");
	//	Mat c_polar(eqsp.polar_colat(1, 1));
	//Mat temp = (Mat_<double>(1, 2) << 1,1);
	//	Mat temp(Mat::ones(1, 5, matType));
	//	eqsp.printMat(eqsp.cap_colats(2, 10, 0.6435, temp));
	//	Mat temp1(eqsp.polar_colat(1, 1));
//	Matx33d temp1(1, 2, 3, 4, 5, 6, 7, 8, 9);
//	Mat print = Mat(temp1);
//	Matx33d temp2(2, 1, 0.0, 3, 1, 0.0, 3, 1, 0.0);
//	cv::Mat_<double> myMat_(3, 1, 0.0);
//	cv::Mat_<double> myMat2_(3, 1, 0.0);
//	print.col(1) = 0;
//	Mat imageroi=print(Rect(1, 1, 2, 2));
//	imageroi = 0;
//	eqsp.printMat(print);

	return 0;
}
