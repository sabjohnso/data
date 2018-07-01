#ifndef EITHER_HPP_INCLUDED_184247862683828988
#define EITHER_HPP_INCLUDED_184247862683828988 1


//
// ... Data header files
//
#include <data/import.hpp>


namespace Data
{
  namespace Core
  {


    class Either_module {

      /** 
       * @brief An empty struct used as a tag to
       * indicated the first type.
       */
      struct first_tag{};

      /**
       * @brief An empty struct used as a tag to
       * indicate selection of the second type
       */
      struct second_tag{};

      
      /** 
       * @brief A data structure holding trivial data
       * for an Either class.
       *
       * @details This type stores trivial data in an
       * encapsulated unnamed union.  It is intended for
       * use by the Either class, and should not be used on
       * its own.
       */
      template< typename First, typename Second >
      struct Trivial_either_data {

	using first_type = First;
	using second_type = Second;
	
	union{ first_type fst; second_type snd; };
	
	template< typename ... Ts >
	constexpr
	Trivial_either_data( first_tag, Ts&& ... inputs )
	  : fst( forward<Ts>( inputs ) ... )
	{}
	
	template< typename ... Ts >
	constexpr
	Trivial_either_data( second_tag, Ts&& ... inputs )
	  : snd( forward<Ts>( inputs ) ... )
	{}

	constexpr const first_type&
	get_first() const& { return fst; }

	constexpr first_type&&
	get_first() && { return move( fst ); }

	first_type&
	get_first() & { return fst; }

	constexpr const second_type&
	get_second() const& { return snd; }

	constexpr second_type&&
	get_second() && { return move( snd ); }

	second_type&
	get_second() & { return snd; }

	

      }; // end of struct Trivial_either_data




      
      /** 
       * @brief A data structure holding nontrivial
       * data for an Either class.
       */
      template< typename First, typename Second >
      struct Nontrivial_either_data {

	using first_type = First;
	using second_type = Second;
	
	union{ unique_ptr<first_type> fst; unique_ptr<second_type> snd; };
	
	template< typename ... Ts >
	constexpr
	Nontrivial_either_data( first_tag, Ts&& ... inputs )
	  : fst( make_unique<first_type>( forward<Ts>( inputs ) ... ))
	{}
	
	template< typename ... Ts >
	constexpr
	Nontrivial_either_data( second_tag, Ts&& ... inputs )
	  : snd( make_unique<first_type>( forward<Ts>( inputs ) ... ))
	{}

	
	~Nontrivial_either_data(){};

	const first_type&
	get_first() const& { return *fst; }

	first_type&&
	get_first() && { return move( *fst ); }

	template< typename ... Ts >
	Nontrivial_either_data&
	set_first( Ts&& ... xs ){
	  fst = make_unique<first_type>( forward<Ts>( xs ) ... );
	}

	const second_type&
	get_second() const& { return *snd; }

	second_type&&
	get_second() && { return move( *snd ); }

	template< typename ... Ts >
	Nontrivial_either_data&
	set_second( Ts&& ... xs ){
	  snd = make_unique<second_type>( forward<Ts>( xs ) ... );
	}
	







      }; // end of struct Trivial_either_data

      

    public:


      

      template< typename First, typename Second >
      class Either {
      public:

	static_assert(
	  ! is_same<First,Second>::value,
	  "\nThe class Either cannot be specialized to use"
	  "\nthe same type for both template parameters." );
	static constexpr bool trivial =
	  is_literal_type<First>::value &&
	  is_literal_type<Second>::value;
       
	using data_type = 
	  conditional_t< trivial, Trivial_either_data<First,Second>,
			 Nontrivial_either_data<First,Second> >;

	using first_type  = typename data_type::first_type;
	using second_type = typename data_type::second_type;

	

	

	constexpr
	Either( const Either& input )
	  : data( input.data )
	  , first_flag( input.first_flag )
	{}


	constexpr
	Either( Either&& input )
	  : data( move( input.data ))
	  , first_flag( input.first_flag )
	{}

	template< typename ... Ts>
	constexpr
	Either( Type<first_type>, Ts&& ... xs )
	  : data( first_tag{}, forward<Ts>( xs ) ... )
	  , first_flag( true )
	{}

	template< typename ... Ts>
	constexpr
	Either( Type<second_type>, Ts&& ... xs )
	  : data( second_tag{}, forward<Ts>( xs ) ... )
	  , first_flag( false )
	{}


      private:

	data_type data;
	bool first_flag;

	friend constexpr bool
	isfirst( const Either& x ){ return x.first_flag; }

	friend constexpr bool
	issecond( const Either& x ){ return ! x.first_flag; }
       
	friend constexpr const first_type&
	first( const Either& x ){ return x.data.get_first(); }

	friend constexpr first_type&&
	first( Either&& x ){ return move( x.data ).get_first(); }

	friend constexpr const second_type&
	second( const Either& x ){ return x.data.get_second(); }

	friend constexpr second_type&&
	second( Either&& x ){ return move( x.data ).get_second(); }
	
	template< typename ... Ts >
	friend Either&
	set_first( Either& x, Ts&& ... xs ) {
	  x.data.get_first() = first_type( forward<Ts>( xs ) ... );
	  x.first_flag = true;
	  return x;
	}

	template< typename ... Ts >
	friend Either&
	set_second( Either& x, Ts&& ... xs ){
	  x.data.get_second() = second_type( forward<Ts>( xs ) ... );
	  x.first_flag = false;
	  return x;
	}
	
      }; // end of class Either


    private:


      class Transform : public Static_callable<Transform> {
      public:
	template<
	typename F, typename E,
	typename First = typename E::first_type,
	typename Second = typename E::second_type,
	typename dF           = decay_t<F>,
	typename FirstResult  = result_of_t<dF(First)>,
	typename SecondResult = result_of_t<dF(Second)>
	>
	static constexpr auto
	call( F&& fun, E&& x ){
	  static_assert( is_same<decay_t<FirstResult>,FirstResult>::value );
	  static_assert( is_same<decay_t<SecondResult>,SecondResult>::value );
	  return aux(
	    bool_constant<is_same<FirstResult,SecondResult>::value>(),
	    forward<F>( fun ), forward<E>( x ));
	}

      private:

	template< typename F, typename E >
	static constexpr auto
	aux( true_type, F&& fun, E&& x ){
	  return isfirst( x )
	    ? forward<F>( fun )( first( forward<E>( x )))
	    : forward<F>( fun )( second( forward<E>( x )));
	}
	

	template<
	typename F, typename E,
	typename First  = typename E::first_type,
	typename Second = typename E::second_type,
	typename dF           = decay_t<F>,
	typename FirstResult  = result_of_t<dF(First)>,
	typename SecondResult = result_of_t<dF(Second)>,
	typename Result = Either<FirstResult,SecondResult>
	>
	static constexpr auto
	aux( false_type, F&& fun, E&& x ){
	  return isfirst( x ) 
	    ? Result( type<FirstResult>,  forward<F>( fun )( first(  forward<E>( x ))))
	    : Result( type<SecondResult>, forward<F>( fun )( second( forward<E>( x ))));
	}
      
      };

    public:
      
      static constexpr auto either_functor = functor( Transform() );
      
    }; // end of class Either_module


    template< typename First, typename Second >
    using Either = Either_module::Either<First,Second>;

    constexpr auto either_functor = Either_module::either_functor;

    


    
    
    
  } // end of namespace Core
} // end of namespace Data

#endif // !defined EITHER_HPP_INCLUDED_184247862683828988
