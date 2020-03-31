# geojsonsf

<details>

* Version: 1.3.3
* Source code: https://github.com/cran/geojsonsf
* URL: https://github.com/SymbolixAU/geojsonsf
* BugReports: https://github.com/SymbolixAU/geojsonsf/issues
* Date/Publication: 2020-03-18 14:40:09 UTC
* Number of recursive dependencies: 49

Run `revdep_details(,"geojsonsf")` for more info

</details>

## Newly broken

*   checking whether package ‘geojsonsf’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/dave/Documents/github/sfheaders/revdep/checks.noindex/geojsonsf/new/geojsonsf.Rcheck/00install.out’ for details.
    ```

## Newly fixed

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘jsonify’
      All declared Imports should be used.
    ```

## Installation

### Devel

```
* installing *source* package ‘geojsonsf’ ...
** package ‘geojsonsf’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c df_geojson.cpp -o df_geojson.o
In file included from df_geojson.cpp:3:
../inst/include/geojsonsf/geojson/api/df_api.hpp:43:22: error: no matching function for call to 'sfg_dimension'
        std::string dim = sfheaders::sfg::sfg_dimension( n_geometry_columns );
                          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:24:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension(
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:47:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::IntegerVector& iv, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:52:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::NumericVector& nv, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:57:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::IntegerMatrix& im, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:62:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::NumericMatrix& nm, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:67:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::DataFrame& df, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:72:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( SEXP x, std::string xyzm ) {
                     ^
In file included from df_geojson.cpp:3:
../inst/include/geojsonsf/geojson/api/df_api.hpp:129:22: error: no matching function for call to 'sfg_dimension'
        std::string dim = sfheaders::sfg::sfg_dimension( n_geometry_columns );
                          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:24:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension(
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:47:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::IntegerVector& iv, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:52:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::NumericVector& nv, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:57:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::IntegerMatrix& im, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:62:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::NumericMatrix& nm, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:67:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( Rcpp::DataFrame& df, std::string xyzm ) {
                     ^
/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/new/sfheaders/include/sfheaders/sfg/sfg_dimension.hpp:72:22: note: candidate function not viable: requires 2 arguments, but 1 was provided
  inline std::string sfg_dimension( SEXP x, std::string xyzm ) {
                     ^
2 errors generated.
make: *** [df_geojson.o] Error 1
ERROR: compilation failed for package ‘geojsonsf’
* removing ‘/Users/dave/Documents/github/sfheaders/revdep/checks.noindex/geojsonsf/new/geojsonsf.Rcheck/geojsonsf’

```
### CRAN

```
* installing *source* package ‘geojsonsf’ ...
** package ‘geojsonsf’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c df_geojson.cpp -o df_geojson.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c geojson_to_sf.cpp -o geojson_to_sf.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c geojson_to_wkt.cpp -o geojson_to_wkt.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c geojson_wkt.cpp -o geojson_wkt.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c read_geojson.cpp -o read_geojson.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/jsonify/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/rapidjsonr/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/geojsonsf/Rcpp/include" -I"/Users/dave/Documents/github/sfheaders/revdep/library.noindex/sfheaders/old/sfheaders/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include/ -fPIC  -Wall -g -O2  -c sf_geojson.cpp -o sf_geojson.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/clang8/lib -o geojsonsf.so RcppExports.o df_geojson.o geojson_to_sf.o geojson_to_wkt.o geojson_wkt.o read_geojson.o sf_geojson.o -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: text-based stub file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd and library file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation are out of sync. Falling back to library file for linking.
installing to /Users/dave/Documents/github/sfheaders/revdep/checks.noindex/geojsonsf/old/geojsonsf.Rcheck/00LOCK-geojsonsf/00new/geojsonsf/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
*** copying figures
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
** checking absolute paths in shared objects and dynamic libraries
** testing if installed package can be loaded from final location
** testing if installed package keeps a record of temporary installation path
* DONE (geojsonsf)

```
