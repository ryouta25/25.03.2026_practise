#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <ctddef>
namespace knk
{
  template< class T >
  class Vector {
   public:
    ~Vector();
    Vector();

    bool 
   private:
    T* data;
    size_t size_, capacity_;
  };
}
template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}
#endif
  
