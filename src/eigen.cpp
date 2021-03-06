#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"
#include <cmath>
using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double eps)
{
    Vector b = Vector::Random(X.cols());
    double eigenvalue;
    for(int i = 0; i < num_iter; i++){
        Vector mult = X * b;
        b = mult / mult.norm();
        Matrix res = (b.transpose() * X * b) / (pow(b.norm(),2));
        eigenvalue = res(0,0);
        double diff = (mult - (eigenvalue * b)).norm();
        if(diff < eps)
            break;
    }
    return make_pair(eigenvalue, b);
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon)
{
    Matrix A(X);
    Vector eigvalues(num);
    Matrix eigvectors(A.rows(), num);

    for(int i = 0; i < num; i++){
        auto result = power_iteration(A, num_iter, epsilon);
        eigvalues(i) = result.first;
        eigvectors.col(i) = result.second;
        A = A - result.first * result.second * result.second.transpose();        
    }

    return make_pair(eigvalues, eigvectors);
}
