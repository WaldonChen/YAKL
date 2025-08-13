#pragma once
// Included by YAKL_intrinsics.h

namespace yakl {
namespace intrinsics {

///////////////////////////////////////////////////////////////////////
// Max(left,right) with Array LHS and scalar RHS
///////////////////////////////////////////////////////////////////////

template <
    class T1, class T2, int N, int STYLE,
    typename std::enable_if<std::is_arithmetic<T2>::value, bool>::type = false>
inline Array<decltype(T1()), N, memHost, STYLE>
max(Array<T1, N, memHost, STYLE> const &left, T2 const &right) {
  auto ret = left.template createHostObject<decltype(T1())>();
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left.data()[i], right);
  }
  return ret;
}
template <class T1, class T2, int N, int STYLE>
inline Array<decltype(T1()), N, memDevice, STYLE>
max_array_scalar(Array<T1, N, memDevice, STYLE> const &left, T2 const &right) {
  auto ret = left.template createDeviceObject<decltype(T1())>();
  c::parallel_for(
      YAKL_AUTO_LABEL(), ret.totElems(), KOKKOS_LAMBDA(int i) {
        ret.data()[i] = std::max(left.data()[i], right);
      });
  return ret;
}
template <
    class T1, class T2, int N, int STYLE,
    typename std::enable_if<std::is_arithmetic<T2>::value, bool>::type = false>
inline Array<decltype(T1()), N, memDevice, STYLE>
max(Array<T1, N, memDevice, STYLE> const &left, T2 const &right) {
  return max_array_scalar(left, right);
}
template <
    class T1, class T2, int N, size_t D0, size_t D1, size_t D2, size_t D3,
    typename std::enable_if<std::is_arithmetic<T2>::value, bool>::type = false>
KOKKOS_INLINE_FUNCTION SArray<decltype(T1()), N, D0, D1, D2, D3>
max(SArray<T1, N, D0, D1, D2, D3> const &left, T2 const &right) {
  SArray<decltype(T1()), N, D0, D1, D2, D3> ret;
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left.data()[i], right);
  }
  return ret;
}
template <
    class T1, class T2, int N, class B0, class B1, class B2, class B3,
    typename std::enable_if<std::is_arithmetic<T2>::value, bool>::type = false>
KOKKOS_INLINE_FUNCTION FSArray<decltype(T1()), N, B0, B1, B2, B3>
max(FSArray<T1, N, B0, B1, B2, B3> const &left, T2 const &right) {
  FSArray<decltype(T1()), N, B0, B1, B2, B3> ret;
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left.data()[i], right);
  }
  return ret;
}

///////////////////////////////////////////////////////////////////////
// Max(left,right) with scalar LHS and Array RHS
///////////////////////////////////////////////////////////////////////

template <
    class T1, class T2, int N, int STYLE,
    typename std::enable_if<std::is_arithmetic<T1>::value, bool>::type = false>
inline Array<decltype(T2()), N, memHost, STYLE>
max(T1 const &left, Array<T2, N, memHost, STYLE> const &right) {
  auto ret = right.template createHostObject<decltype(T2())>();
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left, right.data()[i]);
  }
  return ret;
}
template <class T1, class T2, int N, int STYLE>
inline Array<decltype(T2()), N, memDevice, STYLE>
max_scalar_array(T1 const &left, Array<T2, N, memDevice, STYLE> const &right) {
  auto ret = right.template createDeviceObject<decltype(T2())>();
  c::parallel_for(
      YAKL_AUTO_LABEL(), ret.totElems(), KOKKOS_LAMBDA(int i) {
        ret.data()[i] = std::max(left, right.data()[i]);
      });
  return ret;
}
template <
    class T1, class T2, int N, int STYLE,
    typename std::enable_if<std::is_arithmetic<T1>::value, bool>::type = false>
inline Array<decltype(T2()), N, memDevice, STYLE>
max(T1 const &left, Array<T2, N, memDevice, STYLE> const &right) {
  return max_scalar_array(left, right);
}
template <
    class T1, class T2, int N, size_t D0, size_t D1, size_t D2, size_t D3,
    typename std::enable_if<std::is_arithmetic<T1>::value, bool>::type = false>
KOKKOS_INLINE_FUNCTION SArray<decltype(T2()), N, D0, D1, D2, D3>
max(T1 const &left, SArray<T2, N, D0, D1, D2, D3> const &right) {
  SArray<decltype(T2()), N, D0, D1, D2, D3> ret;
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left, right.data()[i]);
  }
  return ret;
}
template <
    class T1, class T2, int N, class B0, class B1, class B2, class B3,
    typename std::enable_if<std::is_arithmetic<T1>::value, bool>::type = false>
KOKKOS_INLINE_FUNCTION FSArray<decltype(T2()), N, B0, B1, B2, B3>
max(T1 const &left, FSArray<T2, N, B0, B1, B2, B3> const &right) {
  FSArray<decltype(T2()), N, B0, B1, B2, B3> ret;
  for (size_t i = 0; i < ret.totElems(); i++) {
    ret.data()[i] = std::max(left, right.data()[i]);
  }
  return ret;
}

} // namespace intrinsics
} // namespace yakl
