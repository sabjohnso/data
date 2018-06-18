#ifndef SHARED_HPP_INCLUDED_171209974067976451
#define SHARED_HPP_INCLUDED_171209974067976451 1

//
// ... Data header files
//
#include <data/import.hpp>
#include <data/maybe.hpp>


namespace Data
{
  namespace Core
  {

    using std::nullptr_t;
    using std::shared_ptr;
    using std::make_shared;


    /** 
     * @brief A class implementing the operators necessary
     * for generation of a maybe monad for shared pointers.
     **/
    class Shared {
    public:

      template< typename T >
      static constexpr auto
      test( T&& x ){ return bool( x ); }

      template< typename T >
      static constexpr auto
      value( T&& x ){ return *(forward<T>( x )); }

      template< typename T >
      static constexpr auto
      make( T&& x ){ return make_shared<decay_t<T>>( forward<T>( x )); }
	  
      static constexpr auto fail = nullptr;
      
    }; // end of class Shared_operators

    constexpr auto shared_functor =
      functor( Maybe<Shared>::trans );
    
    constexpr auto shared_applicative =
      applicative( Maybe<Shared>::trans,
		   Maybe<Shared>::app,
		   Maybe<Shared>::unit );

    constexpr auto shared_monad =
      monad( Maybe<Shared>::trans,
	     Maybe<Shared>::app,
	     Maybe<Shared>::unit,
	     Maybe<Shared>::bind,
	     Maybe<Shared>::join );
    
  } // end of namespace Core

  using Core::shared_functor;
  using Core::shared_applicative;
  using Core::shared_monad;
  
} // end of namespace Data
#endif // !defined SHARED_HPP_INCLUDED_171209974067976451
