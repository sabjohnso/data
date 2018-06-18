//
// ... Standard header files
//
#include <optional>
#include <memory>



//
// ... Data header files
//
#include <data/optional.hpp>


//
// ... Testing header files
//
#include <data_testing/test_macros.hpp>

constexpr auto sqr = []( auto x ){ return x*x; };

/** Test the optional abstraction functionality */
struct Optional_test
{
  Optional_test() : accum( 0 ) {
    optional_test();
    
  }
  operator int() const { return accum; }
private:

  void
  optional_test(){
    using namespace Data::Core;
    using std::optional;
    using std::nullopt;


    DATA_STATIC_TEST( optional_monad.trans( sqr, optional<int>( 3 ))
		      == optional<int>( 9 ));
    
    DATA_STATIC_TEST( optional_monad.trans( sqr, optional<int>( nullopt ))
		      == optional<int>( nullopt ));

    DATA_STATIC_TEST(
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( sqr ),
	optional<int>( 3 )) == 
      optional<int>( 9 ));


    DATA_STATIC_TEST(
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( nullopt ),
	optional<int>( 3 )) == 
      optional<int>( nullopt ));

    DATA_STATIC_TEST(
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( sqr ),
	optional<int>( nullopt )) == 
      optional<int>( nullopt ));

    DATA_STATIC_TEST(
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( nullopt ),
	optional<int>( nullopt )) == 
      optional<int>( nullopt ));



    
    
    DATA_TEST( accum, optional_monad.trans( sqr, optional<int>( 3 )) ==
	       optional<int>( 9 ));
    
    DATA_TEST( accum, optional_monad.trans( sqr, optional<int>( nullopt )) ==
	       optional<int>( nullopt ));

    DATA_TEST( accum,
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( sqr ),
	optional<int>( 3 )) == 
      optional<int>( 9 ));


    DATA_TEST( accum,
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( nullopt ),
	optional<int>( 3 )) == 
      optional<int>( nullopt ));

    DATA_TEST( accum,
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( sqr ),
	optional<int>( nullopt )) == 
      optional<int>( nullopt ));

    DATA_TEST( accum,
      optional_monad.app(
	optional<decay_t<decltype(sqr)>>( nullopt ),
	optional<int>( nullopt )) == 
      optional<int>( nullopt ));
    
  }

  int accum;
}; // end of struct Optional_test



int
main( int, char** )
{
  int accum = 0;
  return accum;
}
