// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     geo_package/CLASS.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <ostream>
#include <random>
#include <vector>

#include <Eigen/Dense>

#include "./ops/group_ops.h"
#include "./ops/lie_group_ops.h"
#include "./ops/storage_ops.h"
#include "./rot2.h"
#include "./util/epsilon.h"

namespace sym {

/**
 * Autogenerated C++ implementation of <class 'symforce.geo.pose2.Pose2'>.
 *
 * Group of two-dimensional rigid body transformations - R2 x SO(2).
 *
 * The storage space is a complex (real, imag) for rotation followed by a position (x, y).
 *
 * The tangent space is one angle for rotation followed by two elements for translation in the
 * non-rotated frame.
 *
 * For Lie group enthusiasts: This class is on the PRODUCT manifold, if you really really want
 * SE(2) you should use Pose2_SE2.  On this class, the group operations (e.g. compose and between)
 * operate as you'd expect for a Pose or SE(2), but the manifold operations (e.g. retract and
 * local_coordinates) operate on the product manifold SO(2) x R2.  This means that:
 *
 *   - retract(a, vec) != compose(a, from_tangent(vec))
 *
 *   - local_coordinates(a, b) != to_tangent(between(a, b))
 *
 *   - There is no hat operator, because from_tangent/to_tangent is not the matrix exp/log
 */
template <typename ScalarType>
class Pose2 {
 public:
  // Typedefs
  using Scalar = ScalarType;
  using Self = Pose2<Scalar>;
  using DataVec = Eigen::Matrix<Scalar, 4, 1>;
  using TangentVec = Eigen::Matrix<Scalar, 3, 1>;
  using SelfJacobian = Eigen::Matrix<Scalar, 3, 3>;

  // Construct from data vec
  explicit Pose2(const DataVec& data) : data_(data) {}

  // Default construct to identity
  Pose2() : Pose2(GroupOps<Self>::Identity()) {}

  // Access underlying storage as const
  inline const DataVec& Data() const {
    return data_;
  }

  // Matrix type aliases
  using Vector2 = Eigen::Matrix<Scalar, 2, 1>;

  // --------------------------------------------------------------------------
  // Handwritten methods included from "custom_methods/pose2.h.jinja"
  // --------------------------------------------------------------------------

  template <typename Derived>
  Pose2(const Rot2<Scalar>& rotation, const Eigen::MatrixBase<Derived>& position) {
    static_assert(Derived::RowsAtCompileTime == 2, "Position must be a 2x1 vector");
    static_assert(Derived::ColsAtCompileTime == 1, "Position must be a 2x1 vector");
    data_.template head<2>() = rotation.Data();
    data_.template tail<2>() = position;
  }

  Rot2<Scalar> Rotation() const {
    return Rot2<Scalar>(data_.template head<2>());
  }

  Vector2 Position() const {
    return data_.template tail<2>();
  }

  // Generate a random element, with normally distributed position
  template <typename Generator>
  static Pose2 Random(Generator& gen) {
    return Pose2(Rot2<Scalar>::Random(gen), sym::StorageOps<Vector2>::Random(gen));
  }

  Eigen::Transform<Scalar, 2, Eigen::TransformTraits::Isometry> ToTransform() const {
    return Eigen::Transform<Scalar, 2, Eigen::TransformTraits::Isometry>{ToHomogenousMatrix()};
  }

  // --------------------------------------------------------------------------
  // Custom generated methods
  // --------------------------------------------------------------------------

  Vector2 ComposeWithPoint(const Vector2& right) const;

  Vector2 InverseCompose(const Vector2& point) const;

  Eigen::Matrix<Scalar, 3, 3> ToHomogenousMatrix() const;

  // --------------------------------------------------------------------------
  // StorageOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t StorageDim() {
    return StorageOps<Self>::StorageDim();
  }

  void ToStorage(Scalar* const vec) const {
    return StorageOps<Self>::ToStorage(*this, vec);
  }

  static Pose2 FromStorage(const Scalar* const vec) {
    return StorageOps<Self>::FromStorage(vec);
  }

  // --------------------------------------------------------------------------
  // GroupOps concept
  // --------------------------------------------------------------------------

  static Self Identity() {
    return GroupOps<Self>::Identity();
  }

  Self Inverse() const {
    return GroupOps<Self>::Inverse(*this);
  }

  Self Compose(const Self& b) const {
    return GroupOps<Self>::Compose(*this, b);
  }

  Vector2 Compose(const Vector2& point) const {
    return ComposeWithPoint(point);
  }

  Self Between(const Self& b) const {
    return GroupOps<Self>::Between(*this, b);
  }

  Self InverseWithJacobian(SelfJacobian* const res_D_a = nullptr) const {
    return GroupOps<Self>::InverseWithJacobian(*this, res_D_a);
  }

  Self ComposeWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::ComposeWithJacobians(*this, b, res_D_a, res_D_b);
  }

  Self BetweenWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::BetweenWithJacobians(*this, b, res_D_a, res_D_b);
  }

  // Compose shorthand
  template <typename Other>
  auto operator*(const Other& b) const -> decltype(Compose(b)) {
    return Compose(b);
  }

  // --------------------------------------------------------------------------
  // LieGroupOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t TangentDim() {
    return LieGroupOps<Self>::TangentDim();
  }

  static Self FromTangent(const TangentVec& vec, const Scalar epsilon = kDefaultEpsilon<Scalar>) {
    return LieGroupOps<Self>::FromTangent(vec, epsilon);
  }

  TangentVec ToTangent(const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::ToTangent(*this, epsilon);
  }

  Self Retract(const TangentVec& vec, const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::Retract(*this, vec, epsilon);
  }

  TangentVec LocalCoordinates(const Self& b, const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::LocalCoordinates(*this, b, epsilon);
  }

  // --------------------------------------------------------------------------
  // General Helpers
  // --------------------------------------------------------------------------

  bool IsApprox(const Self& b, const Scalar tol) const {
    // isApprox is multiplicative so we check the norm for the exact zero case
    // https://eigen.tuxfamily.org/dox/classEigen_1_1DenseBase.html#ae8443357b808cd393be1b51974213f9c
    if (b.Data() == DataVec::Zero()) {
      return Data().norm() < tol;
    }

    return Data().isApprox(b.Data(), tol);
  }

  template <typename ToScalar>
  Pose2<ToScalar> Cast() const {
    return Pose2<ToScalar>(Data().template cast<ToScalar>());
  }

  bool operator==(const Pose2& rhs) const {
    return data_ == rhs.Data();
  }

 protected:
  DataVec data_;
};

// Shorthand for scalar types
using Pose2d = Pose2<double>;
using Pose2f = Pose2<float>;

// Print definitions
std::ostream& operator<<(std::ostream& os, const Pose2<double>& a);
std::ostream& operator<<(std::ostream& os, const Pose2<float>& a);

}  // namespace sym

// Externs to reduce duplicate instantiation
extern template class sym::Pose2<double>;
extern template class sym::Pose2<float>;

// Concept implementations for this class
#include "./ops/pose2/group_ops.h"
#include "./ops/pose2/lie_group_ops.h"
#include "./ops/pose2/storage_ops.h"
