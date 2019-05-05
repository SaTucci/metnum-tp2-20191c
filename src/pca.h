#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(/*SparseMatrix Y*/unsigned int alfa, unsigned int num_iter, double epsilon);
private:
	unsigned int n;
	Matrix M;
};
