#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort
#include "eigen.h"


Vector sort_indexes(const Vector &v) {

  // initialize original index locations
  Vector idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v(i1) > v(i2);});

  return idx;
}

Vector bin_count(const Vector &v) {
  Vector bc(v.size());
  for(int i = 0; i < v.size(); i++){
    bc(i) = count(v.begin(), v.end(), v(i));
  }

  return bc;
}

int max_elem(const Vector &v){
   double max = -1;
   for(int i = 0; i < v.count(); i++){
     if(v(i) > max){
       max = v(i);
     }
   }

   return max;
}