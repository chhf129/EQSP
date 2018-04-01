#include "EQ_partition.h"

Mat EQSP::eq_point_set_polar(int dim, int n){
//	std::cout << "hello world !" << std::endl;
//	std::system("pause");

	Mat points_s;
	if (dim<1 || dim>3 || n < 1){
		printf("1<=dim<=3,n>=1");
	}

	if (n == 1){
		points_s = Mat::zeros(dim, n, matType);
		return points_s;
	}
	int i = 1;
	int j = 2;
	//int test1 = eq_caps(i, j);
		std::cout << i+j << std::endl;
	//	std::system("pause");

	return points_s;
}


int main(){
	EQSP eqsp;
	
	Mat c_polar(eqsp.polar_colat(1, 1));
	eqsp.printMat(c_polar);
//	Mat temp1(eqsp.polar_colat(1, 1));
	
	return 1;
}
