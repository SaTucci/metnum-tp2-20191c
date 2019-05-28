#include <iostream>
#include "pca.h"
#include "eigen.h"
#include <cmath>
using namespace std;


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
	Matrix mu(M.cols(),1);
	for(int i = 0; i < M.cols(); i++){
        //el i itera por columna pero accede por fila! esto puede causar problemas
		mu(i) = M.row(i).sum()/M.rows();
	}
	cout << mu << endl; 
	Matrix X(M.rows(),M.cols());
	for(int i = 0; i < M.cols(); i++){
        //el i itera por columna pero accede por fila! esto puede causar problemas
		X.row(i) = (M.row(i) - mu.transpose()).transpose() / sqrt(M.rows() - 1);
	} 
	
	Matrix Cov = X.transpose() * X;
	cout << Cov << endl;
	auto eig = get_first_eigenvalues(Cov, max_alfa, num_iter, epsilon);
	V = eig.second;
}


MatrixXd PCA::transform(SparseMatrix Y, int alfa)
{
	//Tal vez tambien habria que cambiar de base a M, no estoy seguro
	Matrix denseY = MatrixXd(Y);
	Matrix trimmedV = V(Eigen::all, Eigen::seq(0,alfa - 1)); 
	Matrix res = denseY* trimmedV;
	return res;
}
