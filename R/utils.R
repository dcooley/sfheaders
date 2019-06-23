
## convert R-index to c++-index
index_correct <- function( geometry_columns ) {
  if( is.numeric( geometry_columns ) )
    return( geometry_columns - 1 )

  return( geometry_columns )
}

