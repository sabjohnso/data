#ifndef IMPORT_HPP_INCLUDED_1632195692353348667
#define IMPORT_HPP_INCLUDED_1632195692353348667 1

//
// ... Standard header files
//
#include <utility>
#include <type_traits>
#include <variant>
#include <memory>


//
// ... External library header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>
#include <control/control.hpp>


namespace Data
{
  namespace Core
  {

    using std::forward;
    using std::move;

    using std::decay_t;
    using std::result_of_t;
    
    using std::variant;
    using std::holds_alternative;
    


    using TypeUtility::Type;
    using TypeUtility::Nat;

    using FunctionUtility::Static_curried;

    using Control::functor;
    using Control::applicative;
    using Control::monad;
    

    
  } // end of namespace Core
} // end of namespace Data


#endif // !defined IMPORT_HPP_INCLUDED_1632195692353348667
