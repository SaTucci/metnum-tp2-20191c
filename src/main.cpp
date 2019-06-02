#include "eigen.cpp"
#include "knn.cpp"
#include "pca.cpp"
#include <Eigen/Dense>
#include <iostream>
//#include <pybind11/pybind11.h>
//#include <pybind11/eigen.h>


//namespace py=pybind11;

int main(){

    
    Matrix X = Matrix(5,4);
    Matrix y = Matrix(1,4);
    Matrix predict = Matrix(1,4);
    X <<    1,2,3,4,
            105,107,113,125,
            14,225,6,9,
            17,23,15,94,
            1784,12,19,135;
    y << 1, 8, 3, 7;
    predict << 2,3,4,5;

    SparseMatrix XSparse = X.sparseView();
    cout << XSparse << endl;
    // cout << X << endl << y << endl << predict << endl;
    // auto res = get_first_eigenvalues(m1, 3, 10000, 0.00001);
    //KNNClassifier knn = KNNClassifier(2);
    //knn.fit(X,y);
    PCA pca(3);
    pca.fit(XSparse,100000,1e-16);
    //cout << knn.predict(predict) << endl;
    

    // cout << "result: " << res.first <<  ", " << endl << res.second << endl;
    return 0;
}