#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
Rcpp::List rcpp_to_sfc() {

  Rcpp::List res(1);

  return res;
}

// [[Rcpp::export]]
List first_three(List x) {
  IntegerVector idx = IntegerVector::create(0, 1, 2);
  return x[idx];
}

// [[Rcpp::export]]
NumericMatrix rcpp_matrix(){
  // Creating a vector object
  NumericVector v = {1,2,3,4};

  // Set the number of rows and columns to attribute dim of the vector object.
  v.attr("dim") = Dimension(2, 2);

  // Converting to Rcpp Matrix type
  NumericMatrix m = as<NumericMatrix>(v);
  // Return the vector to R
  return m;
}

// NumericMatrix::Column col = m( _ , 1);  // Reference to the column 1
// NumericMatrix::Row    row = m( 1 , _ ); // Reference to the row 1
// NumericMatrix::Sub    sub = m( Range(0,1) , Range(2,3) ); // Reference to sub matrix
