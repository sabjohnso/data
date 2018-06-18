#ifndef OPTIONAL_HPP_INCLUDED_900700224566529675
#define OPTIONAL_HPP_INCLUDED_900700224566529675 1

//
// ... Standard header files
//
#include <optional>


//
// ... Data header files
//
#include <data/import.hpp>
#include <data/maybe.hpp>


namespace Data
{
  namespace Core
  {

    
    using std::optional;
    using std::nullopt;

    /**
     * @brief A class implementing the operator necessary
     * for generationof a maybe monad for optional values.
     */
    class Optional{
    public:
      
      template< typename T >
      static constexpr auto
      test( T&& x ){ return bool( x ); }

      template< typename T >
      static constexpr auto
      value( T&& x ){ return *(forward<T>( x )); }

      template< typename T >
      static constexpr auto
      make( T&& x ){ return optional<decay_t<T>>( forward<T>( x )); }

      static constexpr auto fail = nullopt;
      
    }; // end of clas Optional

    constexpr auto optional_functor =
      functor( Maybe<Optional>::trans );

    constexpr auto optional_applicative =
      applicative( Maybe<Optional>::trans,
		   Maybe<Optional>::app,
		   Maybe<Optional>::unit );

    constexpr auto optional_monad =
      monad( Maybe<Optional>::trans,
	     Maybe<Optional>::app,
	     Maybe<Optional>::unit,
	     Maybe<Optional>::bind,
	     Maybe<Optional>::join );



	
    
  } // end of namespace Core


  using Core::optional_monad;


  
} // end of namespace Data


#endif // !defined OPTIONAL_HPP_INCLUDED_900700224566529675
