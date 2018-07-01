#ifndef LIST_HPP_INCLUDED_362529388768003921
#define LIST_HPP_INCLUDED_362529388768003921 1
//
// ... Data header files
//
#include <data/import.hpp>
#include <data/delay.hpp>

namespace Data {
  namespace Core {

    template< typename T >
    class Shared_value {
    public:
      using value_type      = T;
      using reference       = value_type&;
      using const_reference = const value_type&;
      using pointer         = shared_ptr<const T>;

      Shared_value() :
	ptr( make_shared<value_type>( value_type())){
	static_assert(
	  is_trivially_constructible<value_type>::value,
	  "\nThe default construction of a shared value requires "
	  "\nthe underlying value type to be trivially constructible. " );
      }

      operator const_reference () const& { return *ptr; }

    private:
      pointer ptr;
    };  // end of class Shared_value


    /**
     * - cons
     * - has_data
     * - head
     * - tail
     */
    template< typename List, typename T >
    class List_ops : public CRTP<List_ops,List> {

      friend constexpr bool
      empty( const List_ops& xs ){
	return ! has_data( xs );
      }

      static constexpr size_t
      length_aux( const List_ops& xs, size_t accum ){
	return has_data( xs )
	  ? length_aux( tail( xs ), accum+1 )
	  : accum;
      }
      
      friend constexpr size_t
      length( const List_ops& xs ){
	return length_aux( xs, 0 );
      }


      //
      // ... list reversal and appending
      //

      friend constexpr List
      rappend( const List_ops& xs, const List_ops& ys ){
	return has_data( xs )
	  ? rappend( tail( xs ), cons( head( xs ), ys ))
	  : ys;
      }

      
      friend constexpr List
      reverse( const List_ops& xs ){ return rappend( xs, List()); }

      friend constexpr List
      append( const List_ops& xs, const List_ops& ys ){
	return rappend( reverse( xs ), ys );
      }

      
    }; // end of class List_ops








    


    template< typename T >
    class Simple_list
      : public List_ops<Simple_list<T>,T>{
    public:
      
      using value_type = T;
      using cell_type  = pair<T,Simple_list<T>>;
      using data_type  = shared_ptr<cell_type>;

      Simple_list(){}

      Simple_list( value_type& x, const Simple_list& xs )
	: data( make_shared<cell_type>( x, xs ))
      {}
      
    private:
      
      data_type data;

      friend bool
      has_data( const Simple_list& xs ){
	return bool( xs.data );
      }

      friend value_type
      head( const Simple_list& xs ){
	return xs.data->first;
      }

      friend Simple_list
      tail( const Simple_list& xs ){
	return xs.data->second;
      }

      
    }; // end of class Simple_list


    



    template< typename T >
    class Static_list : public List_ops<Static_list<T>,T> {

    public:
      
      using value_type = T;
      using cell_type  = pair<T,Simple_list<T>>;
      using data_type  = optional<cell_type>;

      constexpr
      Static_list(){}

      constexpr
      Static_list( const Static_list& input ) : data( input.data ) {}

      constexpr
      Static_list( Static_list&& input ) : data( move( input.data )) {}


      template< typename U, typename Us >
      constexpr
      Static_list( U&& x, Us&& xs )
	: data( in_place, forward<U>( x ), forward<Us>( xs ))
      {}

    private:

      data_type data;

      friend constexpr bool
      has_data( const Static_list& xs ){
	return bool( xs.data );
      }

      friend constexpr value_type
      head( const Static_list& xs ){
	return xs.data->first;
      }

      friend constexpr Static_list
      tail( const Static_list& xs ){
	return xs.data->second;
      }
      
    }; // end of class Static_list
    



    
  } // end of namespace Core
} // end of namespace Data
#endif // !defined LIST_HPP_INCLUDED_362529388768003921
