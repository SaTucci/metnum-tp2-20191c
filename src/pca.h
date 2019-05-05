#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix Y,unsigned int alfa, unsigned int num_iter, double epsilon);

    Eigen::MatrixXd transform(Matrix Y/*SparseMatrix Y*/);
private:
	unsigned int n;
	Matrix M;
};
