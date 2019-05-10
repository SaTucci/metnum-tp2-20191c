#pragma once

#include "types.h"


class KNNClassifier {
public:
    KNNClassifier(unsigned int n_neighbors);

    void fit(SparseMatrix X, Matrix y);

    Vector predict(SparseMatrix X);
private:
    //Funciones privadas
    double _predict_row(Vector row);
    //Variables privadas
    unsigned int n_neighbors;
    //Datos de entrenamiento
    Matrix X;
    //Etiquetas
    Matrix y;
    
    
};
