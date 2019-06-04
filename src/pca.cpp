#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <iostream>
#include "pca.h"
#include "eigen.h"
#include <cmath>
#include <stdexcept>
using namespace std;

namespace py=pybind11;

PCA::PCA(unsigned int n_components)
{
	max_alfa = n_components;  
}

void PCA::fit(SparseMatrix Y, unsigned int num_iter, double epsilon)
{
	M = MatrixXd(Y);
	//M = Y;
	//Calculo mu, el vector de promedios de las variables de cada medicion
	//(O sea el promedio para cada fila de la matriz)
	Matrix mu = Matrix::Zero(1,M.cols());
	for(int i = 0; i < M.rows(); i++){		
		mu += M.row(i);
	}
	mu = mu/M.rows();
	Matrix X(M.rows(),M.cols());
	for(int i = 0; i < M.rows(); i++){

		X.row(i) = (M.row(i) - mu) / sqrt(M.rows() - 1);
	}
	Matrix Cov = X.transpose() * X;
	py::print(Cov.allFinite());
	auto eig = get_first_eigenvalues(Cov, max_alfa, num_iter, epsilon);
	V = eig.second;
}


MatrixXd PCA::transform(SparseMatrix Y, int alfa)
{
	//Tal vez tambien habria que cambiar de base a M, no estoy seguro
	Matrix denseY = MatrixXd(Y);
	Matrix trimmedV = V(Eigen::all, Eigen::seq(0,alfa - 1)); 
	Matrix res = denseY* trimmedV;
	cout << res << endl;
	return res;
}
