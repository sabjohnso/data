//
// ... Standard header files
//
#include <vector>
#include <string>


//
// ... Data header files
//
#include <data/either.hpp>


//
// ... External library header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>



//
// ... Testing header files
//
#include <data_testing/test_macros.hpp>



/** Test the Either class*/
struct Either_test
{

  Either_test() : accum( 0 ) {
    trivial_test();
    nontrivial_test();
  }

  operator int() const { return accum; }

  void
  trivial_test(){

    using TypeUtility::type;
    using Data::Core::Either;
    using Data::Core::either_functor;
    using char_or_int = Either<char,int>;


    DATA_STATIC_TEST( isfirst( char_or_int( type<char>, 'x' )));
    DATA_STATIC_TEST( !issecond( char_or_int( type<char>, 'x' )));
    DATA_STATIC_TEST( first( char_or_int( type<char>, 'x' )) == 'x' );

    DATA_STATIC_TEST( !isfirst( char_or_int( type<int>, 3 )));
    DATA_STATIC_TEST( issecond( char_or_int( type<int>, 3 )));
    DATA_STATIC_TEST( second( char_or_int( type<int>, 3 )));

    DATA_STATIC_TEST(
      issecond(
	either_functor.trans( 
	  []( auto x ){ return x; },
	  char_or_int( type<int>, 3 ))));



    DATA_STATIC_TEST(
      either_functor.trans( []( auto x ){ return nullptr; },
			    char_or_int( type<int>, 3 )) ==
      nullptr );

    auto x = char_or_int( type<char>, 'x' );
    DATA_TEST( accum, isfirst( x ));
    DATA_TEST( accum, first( x ) == 'x' );


    set_first( x, 'y' );
    DATA_TEST( accum, isfirst( x ));
    DATA_TEST( accum, ! issecond( x ));
    DATA_TEST( accum, first( x ) == 'y' );

    set_second( x, 3 );
    DATA_TEST( accum, ! isfirst( x ));
    DATA_TEST( accum, issecond( x ));
    DATA_TEST( accum, second( x ) == 3 );

  }

  void
  nontrivial_test(){
    
    using TypeUtility::type;
    using Data::Core::Either;
    using std::vector;
    using std::string;
    
    using doubles_or_string = Either<vector<double>,string>;
    DATA_STATIC_TEST( ! doubles_or_string::trivial );

    doubles_or_string xs( type<vector<double>>, 10, 0.0 );
    DATA_TEST( accum, isfirst( xs ));
    for( auto x : first( xs )){
      DATA_TEST( accum, x == 0.0 );
    }

    
    


    
    
    
  }
  int accum;
}; // end of struct Literable_either_test




int
main( int, char** )
{
  int accum = 0;
  accum += Either_test();
  return accum;
}
