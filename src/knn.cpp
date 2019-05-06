//#include <chrono>
#include <iostream>
#include "knn.h"
#include "helper.cpp"

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
{
    this->n_neighbors = n_neighbors;
}

void KNNClassifier::fit(Matrix X, Matrix y)
{
    this->X = X;
    this->y = y;
}

double KNNClassifier::_predict_row(Vector row){
    Matrix Xprima = Matrix(X.rows(), X.cols());
    Matrix resta = Matrix(X.rows(), X.cols());
    Vector sumas = Vector(X.rows());
    Vector votes = Vector(n_neighbors);
    
    //Genero una matriz de filas de row para poder restar con X
    for(int i = 0; i < resta.rows(); i++){
        resta.row(i) = row;
    }

    Xprima = X - resta;
    
    //Lleno el vector de sumas con la norma al cuadrado de cada fila de Xprima
    for(int i = 0; i < X.rows(); i++){
        sumas(i) = Xprima.row(i).squaredNorm();
    }

    //Hago un sort de mayor a menor guardando los indices 
    vector<int> indices = sort_indexes(sumas);
    
    //Me quedo con los primeros n_neighbors indices 
    indices.resize(n_neighbors); // Uso un vector comun porque con Vector pincha
        
    for(int i = 0; i < n_neighbors; i++){
        votes(i) = y(0,indices[i]);
    }
    
    Vector votes_count = bin_count(votes);
        
    return votes(max_elem_index(votes_count));
}

Vector KNNClassifier::predict(Matrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());
        
    for (unsigned k = 0; k < X.rows(); ++k)
    {
        ret(k) = _predict_row(X.row(k));
    }

    return ret;
}

