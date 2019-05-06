#include "eigen.cpp"
#include "knn.cpp"
#include <Eigen/Dense>
#include <iostream>

int main(){

    
    Matrix X = Matrix(4,4);
    Matrix y = Matrix(1,4);
    Matrix predict = Matrix(1,4);
    X <<    100,200,300,400,
            2000,3000,4000,5000,
            3,4,5,6,
            2000,30000,400,500000;
    y << 1, 8, 3, 7;
    predict << 2,3,4,5;
    // cout << X << endl << y << endl << predict << endl;
    // auto res = get_first_eigenvalues(m1, 3, 10000, 0.00001);
    KNNClassifier knn = KNNClassifier(2);
    knn.fit(X,y);
    cout << knn.predict(predict) << endl;
    

    // cout << "result: " << res.first <<  ", " << endl << res.second << endl;
    return 0;
}