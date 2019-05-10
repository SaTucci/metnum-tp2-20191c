#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort
#include "eigen.h"


std::vector<int> sort_indexes(const Vector &v) {

  // initialize original index locations
  std::vector<int> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v(i1) < v(i2);});

  return idx;
}

Vector bin_count(const Vector &v) {
  Vector bc(v.size());
  for(int i = 0; i < v.size(); i++){
    bc(i) = std::count(v.begin(), v.end(), v(i));
  }

  return bc;
}

int max_elem_index(const Vector &v){
   double max = -1;
   int index = -1;
   for(int i = 0; i < v.count(); i++){
     if(v(i) > max){
       max = v(i);
       index = i;
     }
   }

   return index;
}