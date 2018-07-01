macro( data_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  add_test( ${name} ${name}_test ) 
endmacro( data_add_simple_test  name )

data_add_simple_test( optional )
data_add_simple_test( shared )

data_add_simple_test( either )

data_add_simple_test( delay )

data_add_simple_test( list )



