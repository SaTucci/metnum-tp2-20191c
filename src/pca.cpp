#include <iostream>
#include "pca.h"
#include "eigen.h"
#include <cmath>
using namespace std;


PCA::PCA(unsigned int n_components)
{
	alfa = n_components;     
}

void PCA::fit(Matrix Y, unsigned int num_iter, double epsilon)
{
	M = Y;
	//Calculo mu, el vector de promedios de las variables de cada medicion
	//(O sea el promedio para cada fila de la matriz)
	Matrix mu(M.cols(),1);
	for(int i = 0; i < M.cols(); i++){
		mu(i) = M.row(i).sum()/M.rows();
	}
	cout << mu << endl; 
	Matrix X(M.rows(),M.cols());
	for(int i = 0; i < M.cols(); i++){
		X.row(i) = (M.row(i) - mu.transpose()).transpose() / sqrt(M.rows() - 1);
	} 
	
	Matrix Cov = X.transpose() * X;
	cout << Cov << endl;
	auto eig = get_first_eigenvalues(Cov, alfa, num_iter, epsilon);
	V = eig.second;
}


MatrixXd PCA::transform(Matrix Y)
{
	//Tal vez tambien habria que cambiar de base a M, no estoy seguro
	Matrix res = Y* V; 
	return res;
}
