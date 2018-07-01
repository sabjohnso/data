#ifndef DELAY_HPP_INCLUDED_1374762113390523350
#define DELAY_HPP_INCLUDED_1374762113390523350 1


//
// ... Data header files
//
#include <data/import.hpp>

namespace Data{
  namespace Core{






    /** 
     * @brief A multithreaded evaluation policy for the Delay class.
     * 
     * @details This class is intended as a policy for the Delay class,
     * implementing evaluation of the function with the necessary
     * protection for multithreaded use.
     */
    template< typename Function >
    class Evaluate_multithreaded {
    public:
      template< typename T >
      void
      evaluate( T&  data ){
	lock_guard<mutex> lock( mex );
	if( holds_alternative<Function>( data )){
	  data = get<Function>( data )();
	}
      }
    private:
      mutex mex;      
    }; // end of class Evaluate_multithreaded

    

    /** 
     * @brief A single threaded evaluation policy for the Delay class.
     * 
     * @details This class is a policy for the Delay class,
     * implementing evaluation of the function for single threaded use. 
     * This class only offers a small reduction overhead by eliminating 
     * the protection given by Evaluate_delay_multithreaded and its use
     * should be considered carefully.
     */
    template< typename Function >
    class Evaluate_single_threaded {
    public:
      /**
       * @brief Evaluate the function
       */
    template< typename T >
    static void
    evaluate( T& data ){
	assert( holds_alternative<Function>( data ));
	data = get<Function>( data )();
      }
    }; // end of class Evaluate_single_threaded


    template<
      typename T,
      typename Pointer = shared_ptr<T>
      >
    class Shared_storage {

    public:
      
      using value_type = T;
      using reference = value_type&;
      using const_reference = const value_type&;
      using pointer = Pointer;

      Shared_storage(){}
      Shared_storage( const Shared_storage& input ) : ptr( input.ptr ) {}
      Shared_storage( Shared_storage&& input ) : ptr( move( input.ptr )){}

      template< typename U >
      Shared_storage( U&& input ) : ptr( make_shared<value_type>( forward<U>( input ))) {}
      

      const_reference
      get_value() const & { return *ptr; }

      reference
      get_value() & { return *ptr; }

      operator bool() const &{ return bool( ptr ); }
      
    private:
      
      pointer ptr;
      
    }; // end of class shared_storage




    




    template<
      typename T,
      typename F,
      typename Sum = variant<T,F>,
      typename Storage = Shared_storage<Sum>,
      typename Evaluation = Evaluate_multithreaded<F>
      >
    class Delay : Evaluation
    {

    public:

      using value_type    = T;
      using function_type = F;
      using storage_type  = Storage;
      using evaluation    = Evaluation;





      static_assert(
	is_invocable_r<value_type,function_type>::value,
	"\nExpected the function type would yeild a value that "
	"\nis convertible to the value type when invoked without "
	"\narguments " );

      Delay(){}
      Delay( Delay&& input ) : data( move( input.data )) {}
      Delay( const Delay& input ) : data( input.data ) {}

      template< typename U >
      Delay( U&& input ) : data( forward<U>( input )){}
      

      const value_type& 
      get_value() {
	if( holds_alternative<function_type>( data.get_value())){
	  evaluation::evaluate( data.get_value());
	}
	return get<value_type>( data.get_value());
      }
      
      operator bool () const & { return bool( data ); }

    private:

      storage_type data;
      
      friend bool
      operator ==( Delay x, Delay y ){
	return x.get_value() == y.get_value();
      }
    
    };

    template< typename F >
    auto
    delay( F&& f ){
      using dF = decay_t<F>;
      using T = result_of_t<dF()>;
      return Delay<T,dF>( forward<F>( f ));
    }



    

    

    
  } // end of namespace Core
} // end of namespace Data


#endif // !defined DELAY_HPP_INCLUDED_1374762113390523350
