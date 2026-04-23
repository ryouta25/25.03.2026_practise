#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

namespace knk {

template <class T>
class Vector;

template <class T>
class VectorIterator;

template <class T>
class VectorConstIterator;

template <class T>
class VectorIterator {
 public:
  VectorIterator();
  explicit VectorIterator(T* ptr);
  VectorIterator(Vector<T>& vec, size_t idx);

  T& operator*() const;
  T* operator->() const;

  VectorIterator& operator++();
  VectorIterator operator++(int);
  VectorIterator& operator--();
  VectorIterator operator--(int);

  VectorIterator operator+(size_t n) const;
  VectorIterator operator-(size_t n) const;
  ptrdiff_t operator-(const VectorIterator& other) const;

  VectorIterator& operator+=(size_t n);
  VectorIterator& operator-=(size_t n);

  bool operator==(const VectorIterator& other) const;
  bool operator!=(const VectorIterator& other) const;
  bool operator<(const VectorIterator& other) const;
  bool operator<=(const VectorIterator& other) const;
  bool operator>(const VectorIterator& other) const;
  bool operator>=(const VectorIterator& other) const;

  size_t getId(const Vector<T>& vec) const;

 private:
  T* ptr_;
  friend class VectorConstIterator<T>;
  friend class Vector<T>;
};

template <class T>
class VectorConstIterator {
 public:
  VectorConstIterator();
  explicit VectorConstIterator(const T* ptr);
  VectorConstIterator(const Vector<T>& vec, size_t idx);
  VectorConstIterator(const VectorIterator<T>& other);

  const T& operator*() const;
  const T* operator->() const;

  VectorConstIterator& operator++();
  VectorConstIterator operator++(int);
  VectorConstIterator& operator--();
  VectorConstIterator operator--(int);

  VectorConstIterator operator+(size_t n) const;
  VectorConstIterator operator-(size_t n) const;
  ptrdiff_t operator-(const VectorConstIterator& other) const;

  VectorConstIterator& operator+=(size_t n);
  VectorConstIterator& operator-=(size_t n);

  bool operator==(const VectorConstIterator& other) const;
  bool operator!=(const VectorConstIterator& other) const;
  bool operator<(const VectorConstIterator& other) const;
  bool operator<=(const VectorConstIterator& other) const;
  bool operator>(const VectorConstIterator& other) const;
  bool operator>=(const VectorConstIterator& other) const;

  size_t getId(const Vector<T>& vec) const;

 private:
  const T* ptr_;
};

template <class T>
class Vector {
 public:
  ~Vector();
  Vector();
  Vector(size_t size, const T& value);
  explicit Vector(std::initializer_list<T> il);

  Vector(const Vector<T>& rhs);
  Vector(Vector<T>&& rhs) noexcept;
  Vector<T>& operator=(const Vector<T>& rhs);
  Vector<T>& operator=(Vector<T>&& rhs) noexcept;
  void swap(Vector<T>& rhs) noexcept;

  void insert(size_t id, const T& t);
  void insert(size_t id, const Vector<T>& rhs, size_t beg, size_t end);
  void erase(size_t id);
  void erase(size_t beg, size_t end);

  VectorIterator<T> insert(VectorIterator<T> pos, const T& t);
  VectorIterator<T> insert(VectorIterator<T> pos, VectorConstIterator<T> begin, VectorConstIterator<T> end);
  VectorIterator<T> insertRepeated(VectorIterator<T> pos, const T& t, size_t k);

  VectorIterator<T> erase(VectorIterator<T> pos);
  VectorIterator<T> erase(VectorIterator<T> begin, VectorIterator<T> end);
  VectorIterator<T> eraseCount(VectorIterator<T> pos, size_t k);

  bool isEmpty() const noexcept;
  size_t getSize() const noexcept;
  size_t getCapcity() const noexcept;

  void pushBack(const T& t);
  void pushBackRepeat(const T& t, size_t k);
  void popBack();
  void pushFront(const T& t);

  T& operator[](size_t id) noexcept;
  const T& operator[](size_t id) const noexcept;
  T& at(size_t id);
  const T& at(size_t id) const;

  VectorIterator<T> begin() noexcept;
  VectorIterator<T> end() noexcept;
  VectorConstIterator<T> begin() const noexcept;
  VectorConstIterator<T> end() const noexcept;
  VectorConstIterator<T> cbegin() const noexcept;
  VectorConstIterator<T> cend() const noexcept;

 private:
  T* data_;
  size_t size_;
  size_t capacity_;

  explicit Vector(size_t size);

  friend class VectorIterator<T>;
  friend class VectorConstIterator<T>;
};

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
VectorIterator<T>::VectorIterator() : ptr_(nullptr) {}

template <class T>
VectorIterator<T>::VectorIterator(T* ptr) : ptr_(ptr) {}

template <class T>
VectorIterator<T>::VectorIterator(Vector<T>& vec, size_t idx) : ptr_(&vec.data_[idx]) {}

template <class T>
T& VectorIterator<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* VectorIterator<T>::operator->() const {
  return ptr_;
}

template <class T>
VectorIterator<T>& VectorIterator<T>::operator++() {
  ++ptr_;
  return *this;
}

template <class T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
  VectorIterator tmp = *this;
  ++ptr_;
  return tmp;
}

template <class T>
VectorIterator<T>& VectorIterator<T>::operator--() {
  --ptr_;
  return *this;
}

template <class T>
VectorIterator<T> VectorIterator<T>::operator--(int) {
  VectorIterator tmp = *this;
  --ptr_;
  return tmp;
}

template <class T>
VectorIterator<T> VectorIterator<T>::operator+(size_t n) const {
  return VectorIterator(ptr_ + n);
}

template <class T>
VectorIterator<T> VectorIterator<T>::operator-(size_t n) const {
  return VectorIterator(ptr_ - n);
}

template <class T>
ptrdiff_t VectorIterator<T>::operator-(const VectorIterator& other) const {
  return ptr_ - other.ptr_;
}

template <class T>
VectorIterator<T>& VectorIterator<T>::operator+=(size_t n) {
  ptr_ += n;
  return *this;
}

template <class T>
VectorIterator<T>& VectorIterator<T>::operator-=(size_t n) {
  ptr_ -= n;
  return *this;
}

template <class T>
bool VectorIterator<T>::operator==(const VectorIterator& other) const {
  return ptr_ == other.ptr_;
}

template <class T>
bool VectorIterator<T>::operator!=(const VectorIterator& other) const {
  return ptr_ != other.ptr_;
}

template <class T>
bool VectorIterator<T>::operator<(const VectorIterator& other) const {
  return ptr_ < other.ptr_;
}

template <class T>
bool VectorIterator<T>::operator<=(const VectorIterator& other) const {
  return ptr_ <= other.ptr_;
}

template <class T>
bool VectorIterator<T>::operator>(const VectorIterator& other) const {
  return ptr_ > other.ptr_;
}

template <class T>
bool VectorIterator<T>::operator>=(const VectorIterator& other) const {
  return ptr_ >= other.ptr_;
}

template <class T>
size_t VectorIterator<T>::getId(const Vector<T>& vec) const {
  return static_cast<size_t>(ptr_ - vec.data_);
}

template <class T>
VectorConstIterator<T>::VectorConstIterator() : ptr_(nullptr) {}

template <class T>
VectorConstIterator<T>::VectorConstIterator(const T* ptr) : ptr_(ptr) {}

template <class T>
VectorConstIterator<T>::VectorConstIterator(const Vector<T>& vec, size_t idx) : ptr_(&vec.data_[idx]) {}

template <class T>
VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T>& other) : ptr_(other.ptr_) {}

template <class T>
const T& VectorConstIterator<T>::operator*() const {
  return *ptr_;
}

template <class T>
const T* VectorConstIterator<T>::operator->() const {
  return ptr_;
}

template <class T>
VectorConstIterator<T>& VectorConstIterator<T>::operator++() {
  ++ptr_;
  return *this;
}

template <class T>
VectorConstIterator<T> VectorConstIterator<T>::operator++(int) {
  VectorConstIterator tmp = *this;
  ++ptr_;
  return tmp;
}

template <class T>
VectorConstIterator<T>& VectorConstIterator<T>::operator--() {
  --ptr_;
  return *this;
}

template <class T>
VectorConstIterator<T> VectorConstIterator<T>::operator--(int) {
  VectorConstIterator tmp = *this;
  --ptr_;
  return tmp;
}

template <class T>
VectorConstIterator<T> VectorConstIterator<T>::operator+(size_t n) const {
  return VectorConstIterator(ptr_ + n);
}

template <class T>
VectorConstIterator<T> VectorConstIterator<T>::operator-(size_t n) const {
  return VectorConstIterator(ptr_ - n);
}

template <class T>
ptrdiff_t VectorConstIterator<T>::operator-(const VectorConstIterator& other) const {
  return ptr_ - other.ptr_;
}

template <class T>
VectorConstIterator<T>& VectorConstIterator<T>::operator+=(size_t n) {
  ptr_ += n;
  return *this;
}

template <class T>
VectorConstIterator<T>& VectorConstIterator<T>::operator-=(size_t n) {
  ptr_ -= n;
  return *this;
}

template <class T>
bool VectorConstIterator<T>::operator==(const VectorConstIterator& other) const {
  return ptr_ == other.ptr_;
}

template <class T>
bool VectorConstIterator<T>::operator!=(const VectorConstIterator& other) const {
  return ptr_ != other.ptr_;
}

template <class T>
bool VectorConstIterator<T>::operator<(const VectorConstIterator& other) const {
  return ptr_ < other.ptr_;
}

template <class T>
bool VectorConstIterator<T>::operator<=(const VectorConstIterator& other) const {
  return ptr_ <= other.ptr_;
}

template <class T>
bool VectorConstIterator<T>::operator>(const VectorConstIterator& other) const {
  return ptr_ > other.ptr_;
}

template <class T>
bool VectorConstIterator<T>::operator>=(const VectorConstIterator& other) const {
  return ptr_ >= other.ptr_;
}

template <class T>
size_t VectorConstIterator<T>::getId(const Vector<T>& vec) const {
  return static_cast<size_t>(ptr_ - vec.data_);
}

template <class T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <class T>
Vector<T>::Vector(size_t size) : data_(size ? new T[size] : nullptr), size_(size), capacity_(size) {}

template <class T>
Vector<T>::Vector(size_t size, const T& value) : Vector(size) {
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> il) : Vector(il.size()) {
  size_t j = 0;
  for (auto i = il.begin(); i != il.end(); ++i) {
    data_[j++] = *i;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T>& rhs) : Vector(rhs.getSize()) {
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}

template <class T>
Vector<T>::Vector(Vector<T>&& rhs) noexcept : Vector() {
  swap(rhs);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector<T> cpy(rhs);
  swap(cpy);
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept {
  Vector<T> cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template <class T>
void Vector<T>::swap(Vector<T>& rhs) noexcept {
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template <class T>
Vector<T>::~Vector() {
  delete[] data_;
}

template <class T>
T& Vector<T>::at(size_t id) {
  const Vector<T>* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast<T&>(cr);
  return r;
}

template <class T>
const T& Vector<T>::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template <class T>
T& Vector<T>::operator[](size_t id) noexcept {
  return const_cast<T&>((*static_cast<const Vector<T>*>(this))[id]);
}

template <class T>
const T& Vector<T>::operator[](size_t id) const noexcept {
  return data_[id];
}

template <class T>
bool Vector<T>::isEmpty() const noexcept {
  return !size_;
}

template <class T>
size_t Vector<T>::getSize() const noexcept {
  return size_;
}

template <class T>
size_t Vector<T>::getCapcity() const noexcept {
  return capacity_;
}

template <class T>
void Vector<T>::pushBack(const T& t) {
  Vector<T> v(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i) {
    v[i] = (*this)[i];
  }
  v[getSize()] = t;
  swap(v);
}

template <class T>
void Vector<T>::pushBackRepeat(const T& t, size_t k) {
  Vector<T> cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}

template <class T>
void Vector<T>::popBack() {
  if (!size_) {
    throw std::out_of_range("Vector is empty");
  }
  --size_;
}

template <class T>
void Vector<T>::pushFront(const T& t) {
  Vector<T> v(getSize() + 1);
  v[0] = t;
  for (size_t i = 1; i < v.getSize(); ++i) {
    v[i] = (*this)[i - 1];
  }
  swap(v);
}

template <class T>
void Vector<T>::insert(size_t id, const T& t) {
  if (id > getSize()) {
    throw std::out_of_range("id out of bound");
  }
  Vector<T> v;
  for (size_t i = 0; i < id; ++i) {
    v.pushBack((*this)[i]);
  }
  v.pushBack(t);
  for (size_t i = id; i < getSize(); ++i) {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template <class T>
void Vector<T>::insert(size_t id, const Vector<T>& rhs, size_t beg, size_t end) {
  if (id > getSize()) {
    throw std::out_of_range("id out of bound");
  }
  if (beg > end || end > rhs.getSize()) {
    throw std::out_of_range("range out of bound");
  }
  if (beg == end) {
    return;
  }
  Vector<T> v;
  for (size_t i = 0; i < id; ++i) {
    v.pushBack((*this)[i]);
  }
  for (size_t i = beg; i < end; ++i) {
    v.pushBack(rhs[i]);
  }
  for (size_t i = id; i < getSize(); ++i) {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template <class T>
void Vector<T>::erase(size_t id) {
  if (id >= getSize()) {
    throw std::out_of_range("id out of bound");
  }
  Vector<T> v(getSize() - 1);
  for (size_t i = 0; i < id; ++i) {
    v[i] = (*this)[i];
  }
  for (size_t i = id; i < v.getSize(); ++i) {
    v[i] = (*this)[i + 1];
  }
  swap(v);
}

template <class T>
void Vector<T>::erase(size_t beg, size_t end) {
  if (beg > end || end > getSize()) {
    throw std::out_of_range("range out of bound");
  }
  if (beg == end) {
    return;
  }
  size_t count = end - beg;
  Vector<T> v(getSize() - count);
  for (size_t i = 0; i < beg; ++i) {
    v[i] = (*this)[i];
  }
  for (size_t i = beg; i < v.getSize(); ++i) {
    v[i] = (*this)[i + count];
  }
  swap(v);
}

template <class T>
VectorIterator<T> Vector<T>::insert(VectorIterator<T> pos, const T& t) {
  size_t id = pos.getId(*this);
  insert(id, t);
  return VectorIterator<T>(*this, id);
}

template <class T>
VectorIterator<T> Vector<T>::insert(VectorIterator<T> pos, VectorConstIterator<T> begin, VectorConstIterator<T> end) {
  size_t id = pos.getId(*this);
  if (begin > end) {
    throw std::out_of_range("range out of bound");
  }
  if (begin == end) {
    return pos;
  }
  Vector<T> v;
  for (size_t i = 0; i < id; ++i) {
    v.pushBack((*this)[i]);
  }
  VectorConstIterator<T> it = begin;
  while (it != end) {
    v.pushBack(*it);
    ++it;
  }
  for (size_t i = id; i < getSize(); ++i) {
    v.pushBack((*this)[i]);
  }
  swap(v);
  return VectorIterator<T>(*this, id);
}

template <class T>
VectorIterator<T> Vector<T>::insertRepeated(VectorIterator<T> pos, const T& t, size_t k) {
  size_t id = pos.getId(*this);
  if (k == 0) {
    return pos;
  }
  Vector<T> v;
  for (size_t i = 0; i < id; ++i) {
    v.pushBack((*this)[i]);
  }
  for (size_t i = 0; i < k; ++i) {
    v.pushBack(t);
  }
  for (size_t i = id; i < getSize(); ++i) {
    v.pushBack((*this)[i]);
  }
  swap(v);
  return VectorIterator<T>(*this, id);
}

template <class T>
VectorIterator<T> Vector<T>::erase(VectorIterator<T> pos) {
  size_t id = pos.getId(*this);
  erase(id);
  if (id >= getSize()) {
    return end();
  }
  return VectorIterator<T>(*this, id);
}

template <class T>
VectorIterator<T> Vector<T>::erase(VectorIterator<T> begin, VectorIterator<T> end) {
  if (begin == end) {
    return begin;
  }
  size_t b = begin.getId(*this);
  size_t e = end.getId(*this);
  erase(b, e);
  if (b >= getSize()) {
    return end();
  }
  return VectorIterator<T>(*this, b);
}

template <class T>
VectorIterator<T> Vector<T>::eraseCount(VectorIterator<T> pos, size_t k) {
  size_t id = pos.getId(*this);
  erase(id, id + k);
  if (id >= getSize()) {
    return end();
  }
  return VectorIterator<T>(*this, id);
}

template <class T>
VectorIterator<T> Vector<T>::begin() noexcept {
  return VectorIterator<T>(*this, 0);
}

template <class T>
VectorIterator<T> Vector<T>::end() noexcept {
  return VectorIterator<T>(*this, size_);
}

template <class T>
VectorConstIterator<T> Vector<T>::begin() const noexcept {
  return VectorConstIterator<T>(*this, 0);
}

template <class T>
VectorConstIterator<T> Vector<T>::end() const noexcept {
  return VectorConstIterator<T>(*this, size_);
}

template <class T>
VectorConstIterator<T> Vector<T>::cbegin() const noexcept {
  return begin();
}

template <class T>
VectorConstIterator<T> Vector<T>::cend() const noexcept {
  return end();
}

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

}

#endif
