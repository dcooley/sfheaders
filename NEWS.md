
# v0.2.2

* `unlist` argument in `sf_to_df()` to specify columns you want to unlist when converted to data.frame
* helper functions with easier syntax - thanks to @mdsumner

# v 0.2.1

* `sf_remove_holes()` removes holes from polygons
* `calculate_bbox()` function for (re) calculating the bounding box of an `sfc` object
* `sf_cast()` functions for casting between geometry types
* optimised converting `sfc_POINT`-only objects to data.frames
* `sf_to_df()` adds `sfc_columns` attributes to identify which of the columns form the coordinates

# v 0.1

* `keep = TRUE` argument to keep other data columns when converting to `sf`
* `sf_to_df` functions for converting sf objects to data.frames
* `fill = TRUE` argument to fill the data.frame columns with data
