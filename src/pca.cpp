#include <iostream>
#include "pca.h"
#include "eigen.h"
#include <cmath>
using namespace std;


PCA::PCA(unsigned int n_components)
{
	n = n_components;     
}

void PCA::fit(Matrix X)
{
	M = X;
}


MatrixXd PCA::transform(/*SparseMatrix Y*/unsigned int alfa, unsigned int num_iter, double epsilon)
{
	//Calculo mu, el vector de promedios de las variables de cada medicion
	//(O sea el promedio para cada fila de la matriz)
	Matrix mu(M.cols(),1);
	for(int i = 0; i < M.cols(); i++){
		mu(i) = M.row(i).sum()/M.rows();
	}
	cout << mu << endl; 
	Matrix X(M.rows(),M.cols());
	for(int i = 0; i < M.cols(); i++){
		X.row(i) = (M.row(i).array() - mu(i,0)).transpose() / sqrt(M.rows() - 1);
	} 
	cout << X << endl; 
	Matrix Cov = X.transpose() * X;
	cout << Cov << endl;

	auto eig = get_first_eigenvalues(M, alfa, num_iter, epsilon);
	Matrix TC(X.rows(),eig.second.rows());
	for(int i = 0; i < M.cols(); i++){
		//Supongo que hay que transponer los autovectores
		TC.row(i) = eig.second.col(i).transpose() * X.row(i);
	}
}
