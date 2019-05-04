#include "eigen.cpp"
#include <Eigen/Dense>
#include <iostream>

int main(){
	std::cout << "hola mundo" << endl;
    Eigen::DiagonalMatrix<double, 3> m(3, 8, 6);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> m1(m);
    cout << m1.diagonal() << endl;
    auto res = get_first_eigenvalues(m1, 3, 10000, 0.00001);
    cout << "result: " << res.first <<  ", " << res.second << endl;
    return 0;
}