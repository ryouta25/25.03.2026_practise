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

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
   private:
    T* data;
    size_t size_, capacity_;
  };
}
template< class T >
bool knk::Vector< T >::getSize() const noexcept {
 return -1;
}
template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return false;
}
knk::Vector< T >::~Vector() {
  data_(nullptr),
  size_(0),
  capacity_(0)
  delete [] data_;
}
#endif
  
