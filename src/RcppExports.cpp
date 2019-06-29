// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rcpp_calculate_bbox
SEXP rcpp_calculate_bbox(SEXP x);
RcppExport SEXP _sfheaders_rcpp_calculate_bbox(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_calculate_bbox(x));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_attach_sfc_attributes
void rcpp_attach_sfc_attributes(Rcpp::List& sfc, std::string geom_type, Rcpp::NumericVector& bbox, std::string epsg, std::string proj4string, int n_empty, double precision);
RcppExport SEXP _sfheaders_rcpp_attach_sfc_attributes(SEXP sfcSEXP, SEXP geom_typeSEXP, SEXP bboxSEXP, SEXP epsgSEXP, SEXP proj4stringSEXP, SEXP n_emptySEXP, SEXP precisionSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type sfc(sfcSEXP);
    Rcpp::traits::input_parameter< std::string >::type geom_type(geom_typeSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type bbox(bboxSEXP);
    Rcpp::traits::input_parameter< std::string >::type epsg(epsgSEXP);
    Rcpp::traits::input_parameter< std::string >::type proj4string(proj4stringSEXP);
    Rcpp::traits::input_parameter< int >::type n_empty(n_emptySEXP);
    Rcpp::traits::input_parameter< double >::type precision(precisionSEXP);
    rcpp_attach_sfc_attributes(sfc, geom_type, bbox, epsg, proj4string, n_empty, precision);
    return R_NilValue;
END_RCPP
}
// rcpp_sfg_dimension
std::string rcpp_sfg_dimension(SEXP x);
RcppExport SEXP _sfheaders_rcpp_sfg_dimension(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_sfg_dimension(x));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_vec
SEXP rcpp_get_vec(SEXP x, SEXP cols);
RcppExport SEXP _sfheaders_rcpp_get_vec(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_vec(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_mat
SEXP rcpp_get_mat(SEXP x, SEXP cols);
RcppExport SEXP _sfheaders_rcpp_get_mat(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_mat(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_list_mat
SEXP rcpp_get_list_mat(SEXP x, SEXP cols, SEXP id);
RcppExport SEXP _sfheaders_rcpp_get_list_mat(SEXP xSEXP, SEXP colsSEXP, SEXP idSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id(idSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_list_mat(x, cols, id));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_points
SEXP rcpp_to_points(SEXP x, SEXP cols);
RcppExport SEXP _sfheaders_rcpp_to_points(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_points(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_multipoints
SEXP rcpp_to_multipoints(Rcpp::NumericMatrix x);
RcppExport SEXP _sfheaders_rcpp_to_multipoints(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_multipoints(x));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_point
SEXP rcpp_to_point(SEXP x, SEXP geometry_columns);
RcppExport SEXP _sfheaders_rcpp_to_point(SEXP xSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_point(x, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_multipoint
SEXP rcpp_to_multipoint(SEXP x, SEXP geometry_columns);
RcppExport SEXP _sfheaders_rcpp_to_multipoint(SEXP xSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_multipoint(x, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_linestring
SEXP rcpp_to_linestring(SEXP x, SEXP geometry_columns);
RcppExport SEXP _sfheaders_rcpp_to_linestring(SEXP xSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_linestring(x, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_multilinestring
SEXP rcpp_to_multilinestring(SEXP x, SEXP geometry_columns, SEXP line_id);
RcppExport SEXP _sfheaders_rcpp_to_multilinestring(SEXP xSEXP, SEXP geometry_columnsSEXP, SEXP line_idSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type line_id(line_idSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_multilinestring(x, geometry_columns, line_id));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_polygon
SEXP rcpp_to_polygon(SEXP x, SEXP geometry_columns, SEXP line_id);
RcppExport SEXP _sfheaders_rcpp_to_polygon(SEXP xSEXP, SEXP geometry_columnsSEXP, SEXP line_idSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type line_id(line_idSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_polygon(x, geometry_columns, line_id));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_multipolygon
SEXP rcpp_to_multipolygon(SEXP x, SEXP geometry_columns, SEXP polygon_id, SEXP line_id);
RcppExport SEXP _sfheaders_rcpp_to_multipolygon(SEXP xSEXP, SEXP geometry_columnsSEXP, SEXP polygon_idSEXP, SEXP line_idSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type polygon_id(polygon_idSEXP);
    Rcpp::traits::input_parameter< SEXP >::type line_id(line_idSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_multipolygon(x, geometry_columns, polygon_id, line_id));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_sfg
SEXP rcpp_to_sfg(SEXP x, std::string geom_type);
RcppExport SEXP _sfheaders_rcpp_to_sfg(SEXP xSEXP, SEXP geom_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type geom_type(geom_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_sfg(x, geom_type));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_other_columns
SEXP rcpp_other_columns(SEXP x, SEXP id_cols);
RcppExport SEXP _sfheaders_rcpp_other_columns(SEXP xSEXP, SEXP id_colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_cols(id_colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_other_columns(x, id_cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_line_ids
Rcpp::IntegerMatrix rcpp_line_ids(Rcpp::NumericVector line_ids, Rcpp::NumericVector unique_ids);
RcppExport SEXP _sfheaders_rcpp_line_ids(SEXP line_idsSEXP, SEXP unique_idsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type line_ids(line_idsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type unique_ids(unique_idsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_line_ids(line_ids, unique_ids));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_subset_dataframe
Rcpp::DataFrame rcpp_subset_dataframe(Rcpp::DataFrame df, Rcpp::StringVector cols, int start, int end);
RcppExport SEXP _sfheaders_rcpp_subset_dataframe(SEXP dfSEXP, SEXP colsSEXP, SEXP startSEXP, SEXP endSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type cols(colsSEXP);
    Rcpp::traits::input_parameter< int >::type start(startSEXP);
    Rcpp::traits::input_parameter< int >::type end(endSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_subset_dataframe(df, cols, start, end));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_sfheaders_rcpp_calculate_bbox", (DL_FUNC) &_sfheaders_rcpp_calculate_bbox, 1},
    {"_sfheaders_rcpp_attach_sfc_attributes", (DL_FUNC) &_sfheaders_rcpp_attach_sfc_attributes, 7},
    {"_sfheaders_rcpp_sfg_dimension", (DL_FUNC) &_sfheaders_rcpp_sfg_dimension, 1},
    {"_sfheaders_rcpp_get_vec", (DL_FUNC) &_sfheaders_rcpp_get_vec, 2},
    {"_sfheaders_rcpp_get_mat", (DL_FUNC) &_sfheaders_rcpp_get_mat, 2},
    {"_sfheaders_rcpp_get_list_mat", (DL_FUNC) &_sfheaders_rcpp_get_list_mat, 3},
    {"_sfheaders_rcpp_to_points", (DL_FUNC) &_sfheaders_rcpp_to_points, 2},
    {"_sfheaders_rcpp_to_multipoints", (DL_FUNC) &_sfheaders_rcpp_to_multipoints, 1},
    {"_sfheaders_rcpp_to_point", (DL_FUNC) &_sfheaders_rcpp_to_point, 2},
    {"_sfheaders_rcpp_to_multipoint", (DL_FUNC) &_sfheaders_rcpp_to_multipoint, 2},
    {"_sfheaders_rcpp_to_linestring", (DL_FUNC) &_sfheaders_rcpp_to_linestring, 2},
    {"_sfheaders_rcpp_to_multilinestring", (DL_FUNC) &_sfheaders_rcpp_to_multilinestring, 3},
    {"_sfheaders_rcpp_to_polygon", (DL_FUNC) &_sfheaders_rcpp_to_polygon, 3},
    {"_sfheaders_rcpp_to_multipolygon", (DL_FUNC) &_sfheaders_rcpp_to_multipolygon, 4},
    {"_sfheaders_rcpp_to_sfg", (DL_FUNC) &_sfheaders_rcpp_to_sfg, 2},
    {"_sfheaders_rcpp_other_columns", (DL_FUNC) &_sfheaders_rcpp_other_columns, 2},
    {"_sfheaders_rcpp_line_ids", (DL_FUNC) &_sfheaders_rcpp_line_ids, 2},
    {"_sfheaders_rcpp_subset_dataframe", (DL_FUNC) &_sfheaders_rcpp_subset_dataframe, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_sfheaders(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
