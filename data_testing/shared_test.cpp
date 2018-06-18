//
// ... Standard header files
//
#include <memory>
#include <type_traits>

//
// ... Data header files
//
#include <data/shared.hpp>

//
// ... Test header files
//
#include <data_testing/test_macros.hpp>


//
// ... External library header files
//
#include <control/control.hpp>
#include <function_utility/function_utility.hpp>

#define DECAYTYPE( ... ) std::decay_t<decltype(__VA_ARGS__)>



namespace {


/** Test the shared pointer monad 
 */
struct Shared_test
{
  Shared_test() : accum( 0 ) {
    using namespace Data;
    using namespace Control;
    using namespace FunctionUtility;
    auto mx = call_with( shared_monad, unit( 3 ));
    using std::make_shared;
    using std::shared_ptr;

    constexpr auto sqr = []( auto x ){ return x*x; };

    DATA_TEST( accum, bool( mx ));
    if( mx ){ DATA_TEST( accum, *mx == 3 ); }
	       
			 
    auto my = call_with( shared_monad,  trans( sqr, pure( mx )));

    DATA_TEST( accum, bool( my ));
    if( mx ){ DATA_TEST( accum, *my == 9 ) }


    auto mz = call_with( 
      shared_monad, app( unit( sqr ), unit( 3 )));

    DATA_TEST( accum, bool( mz ));
    if( mz ){ DATA_TEST( accum, *mz == 9  ); }

    
    auto no_sqr = shared_ptr<DECAYTYPE(sqr)>( nullptr );
    auto no_mx  = shared_ptr<int>( nullptr );
    auto ma = 
      app( pure( no_sqr ), pure( mx ))
      (shared_monad);
    DATA_TEST( accum, !( ma ));


    auto mb = call_with(
      shared_monad,
      app( unit( sqr ), 
	   pure( no_mx )));

    DATA_TEST( accum, !( mb ));

    auto mc = call_with(
      shared_monad,
      app( pure( no_sqr ),
	   pure( no_mx )));

    DATA_TEST( accum, ! mc );

    
    auto divide =
      []( auto x, auto y ){
	using U = decltype( x/y );
	return y != 0
	  ? make_shared<U>( x/y )
	  : nullptr;
      };

    auto md = divide( 4, 2 );
    DATA_TEST( accum, md );
    DATA_TEST( accum, *md == 2 );

    auto me = divide( 4, 0 );
    DATA_TEST( accum, ! me);

    auto mf = call_with( shared_monad, unit( 4 ));
    auto mg = call_with( shared_monad, unit( 2 ));
    auto mh = call_with(
      shared_monad,
      bind( pure( mf ), [&]( auto x ){ return
      bind( pure( mg ), [&]( auto y ){ return 
	    pure( divide( x, y )); }); }));
      
    DATA_TEST( accum, mh );
    if( mh ){ 
      DATA_TEST( accum, *mh == 2 );
    }

    
    

      

       

    
    
	
		    

    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Shared_test

}

int
main( int, char** )
{
  int accum = 0;
  accum += Shared_test();
  return accum;
}
