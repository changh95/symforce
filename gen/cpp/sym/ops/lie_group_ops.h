// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/geo_package/ops/lie_group_ops.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <limits>

#include <Eigen/Dense>
#include <sym/util/epsilon.h>

#include "./storage_ops.h"

namespace sym {

/**
 * C++ LieGroupOps concept, specialized per type.
 * See `symforce.ops.lie_group_ops` for details.
 */
template <typename T>
struct LieGroupOps {
  using Scalar = typename T::Scalar;

  static constexpr int32_t TangentDim();
  using TangentVec = Eigen::Matrix<Scalar, TangentDim(), 1>;
  using SelfJacobian = Eigen::Matrix<Scalar, TangentDim(), TangentDim()>;

  static T FromTangent(const TangentVec& vec, const Scalar epsilon);
  static TangentVec ToTangent(const T& a, const Scalar epsilon);
  static T Retract(const T& a, const TangentVec& vec, const Scalar epsilon);
  static TangentVec LocalCoordinates(const T& a, const T& b, const Scalar epsilon);
  static bool IsClose(const T& a, const T& b, const Scalar epsilon, const Scalar tol);
};

namespace internal {

/**
 * A helper struct containing default implementations of methods in LieGroupOps. Meant only to
 * be inherited by template specializations of LieGroupOps.
 */
template <typename T, typename Scalar>
struct LieGroupOpsBase {
  static bool IsClose(const T& a, const T& b, const Scalar tol) {
    return LieGroupOps<T>::LocalCoordinates(a, b, kDefaultEpsilon<Scalar>).norm() < tol;
  }
};

}  // namespace internal

// Returns true if the distance from a to b in local coordinate space is less than tol. Returns
// false otherwise. epsilon is present to avoid dividing by zero.
template <typename T>
bool IsClose(const T& a, const T& b, const typename StorageOps<T>::Scalar tol) {
  return LieGroupOps<T>::IsClose(a, b, tol);
}

}  // namespace sym

#include "./matrix/lie_group_ops.h"
#include "./scalar/lie_group_ops.h"
