#ifndef ZIPPER_HPP_INCLUDED_1384589680293803432
#define ZIPPER_HPP_INCLUDED_1384589680293803432 1


//
// ... Data header files
//
#include <data/import.hpp>
#include <data/list.hpp>

namespace Data{
  namespace Core{


    template<
      typename T,
      template< typename ... > class Variant  = variant,
      template< typename ... > class Pointer  = shared_ptr,
      template< typename ... > class Function = function,
      template< typename ... > class Pair     = pair
      >
    class Zipper {
    public:
      

      
    private:
      list_type data;
      list_type context;
    }; // end of class Zipper
    
    
    
  } // end of namespace Core
} // end of namespace Data

#endif // !defined ZIPPER_HPP_INCLUDED_1384589680293803432
