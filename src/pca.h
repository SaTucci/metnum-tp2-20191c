#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(SparseMatrix Y, unsigned int num_iter, double epsilon);

    Eigen::MatrixXd transform(SparseMatrix Y, int alfa);
private:
	unsigned int max_alfa;
	//Matriz de datos
	Matrix M;
	//Matriz de cambio de base
	Matrix V;
};
