//
// ... Standard header files
//
#include <thread>
#include <vector>
#include <algorithm>



//
// ... Data header files
//
#include <data/delay.hpp>


//
// ... Testing header files
//
#include <data_testing/test_macros.hpp>

/** Test the delay class  */
struct Delay_test
{
  Delay_test() : accum( 0 ) {
    using Data::Core::Delay;
    using Data::Core::delay;
    using std::make_pair;
    using std::pair;

    int counter = 0;
    auto x = delay( [&counter](){ ++counter; return 1; });
    
    DATA_TEST( accum, bool( x ));
    DATA_TEST( accum, counter == 0 );
    DATA_TEST( accum, x.get_value() == 1 );
    DATA_TEST( accum, counter == 1 );
    DATA_TEST( accum, x.get_value() == 1 );
    DATA_TEST( accum, counter == 1 );


    constexpr auto f = [](){ return 2; };
    Delay<int,decltype(f)> y;
    DATA_TEST( accum, ! bool( y ));


    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Delay_test


/** Test Multithreaded_delay */
struct Multithreaded_delay_test
{
  Multithreaded_delay_test() : accum( 0 ) {

    using std::thread;
    using std::vector;
    using std::for_each;
    using std::ref;
    using Data::Core::delay;
    

    constexpr size_t nth = 64;
    constexpr size_t xvalue = 3.0;
    int counter = 0;
    
    auto x = delay([&counter]() mutable { ++counter; return xvalue; });

    vector<thread> threads;
    vector<int> values( nth, 0 );

    DATA_TEST( accum, counter == 0 )
    for( size_t ith = 0; ith < nth; ++ith){
      threads.push_back(thread( [=,&values](auto& x){ values[ith] = x.get_value(); },ref(x) ));
    }
    for_each( begin( threads ), end( threads ), []( auto& th ){ th.join(); });
    for_each( begin( values ), end( values ),
	      [&]( auto value ){ DATA_TEST( accum, value == xvalue ); });

    
  }
  operator int() const { return accum; }
  int accum;

}; // end of struct Multithreaded_delay_test




int
main( int, char** )
{
  int accum = 0;
  accum += Delay_test();
  accum += Multithreaded_delay_test();
  return accum;
}
