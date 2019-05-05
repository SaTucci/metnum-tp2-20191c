#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix Y, unsigned int num_iter, double epsilon);

    Eigen::MatrixXd transform(Matrix Y);
private:
	unsigned int alfa;
	//Matriz de datos
	Matrix M;
	//Matriz de cambio de base
	Matrix V;
};
