#ifndef MAYBE_HPP_INCLUDED_1886559793111210205
#define MAYBE_HPP_INCLUDED_1886559793111210205 1


//
// ... Data header files
//
#include <data/import.hpp>


namespace Data
{
  namespace Core
  {

    
    
    template< typename K >
    class Maybe
    {
      class Trans : public Static_curried<Trans,Nat<2>>{
      public:
	
	template<typename F, typename T >
	static constexpr auto
	call( F&& f, T&& x ){
	  return K::test( x )
	    ? K::make( forward<F>( f )( K::value( forward<T>( x )) ))
	    : K::fail;
	}
      }; // end of class Trans

      
      class App   : public Static_curried<App,Nat<2>>{
      public:
	template<typename F, typename T >
	static constexpr auto
	call( F&& f, T&& x ){
	  return K::test( f ) && K::test( x )
	    ? K::make( K::value( forward<F>( f ))( K::value( forward<T>( x )) ))
	    : K::fail;
	}
      }; // end of class App

      
      class Unit  : public Static_curried<Unit,Nat<1>>{
      public:
	template< typename T >
	static constexpr auto
	call( T&& x ){
	  return K::make( forward<T>( x ));
	}
      }; // end of class Unit

      class Bind  : public Static_curried<Bind,Nat<2>>{
      public:
	template< typename T, typename F >
	static constexpr auto
	call( T&& x, F&& f ){
	  return K::test( x )
	    ? forward<F>( f )( K::value( forward<T>( x )))
	    : K::fail;
	}
      };

      class Join  : public Static_curried<Join,Nat<1>>{
      public:
	template< typename T, typename F >
	static constexpr auto
	call( T&& x, F&& f ){
	  return K::test( x )
	    ? forward<F>( f )( K::value( x ))
	    : K::fail;
	}
      }; // end of class Join

    public:
      
      static constexpr auto trans = Trans{};
      static constexpr auto app   = App{};
      static constexpr auto unit  = Unit{};
      static constexpr auto bind  = Bind{};
      static constexpr auto join  = Join{};
      
    }; // end of class Maybe

    



    
  } // end of namespace Core
} // end of namespace Data


#endif // !defined MAYBE_HPP_INCLUDED_1886559793111210205
