
//
// ... Data header files
//
#include <data/list.hpp>


//
// ... Testing header files
//
#include <data_testing/test_macros.hpp>



/** Test static lists */
struct Static_list_test
{
  
  Static_list_test() : accum( 0 ) {
    construction_test();
  }
  operator int() const { return accum; }

  void
  construction_test(){
    using Data::Core::Static_list;

    
  }
  
  int accum;
}; // end of struct Static_list_test





int
main( int, char** )
{
  int accum = 0;
  accum += Static_list_test();
  return accum;
}
