// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <sym/pose3.h>

namespace sym {

/**
 * Return the 2dof residual of reprojecting the landmark into the target camera and comparing
 * against the correspondence in the target camera.
 *
 * The landmark is specified as a pixel in the source camera and an inverse range; this means the
 * landmark is fixed in the source camera and always has residual 0 there (this 0 residual is not
 * returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the Barron noise model.  Whitening each component of
 * the reprojection error separately would result in rejecting individual components as outliers.
 * Instead, we minimize the whitened norm of the full reprojection error for each point.  See the
 * docstring for `NoiseModel.whiten_norm` for more information on this, and the docstring of
 * `BarronNoiseModel` for more information on the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     source_calibration_storage: The storage vector of the source camera calibration
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     source_pixel: The location of the landmark in the source camera
 *     target_pixel: The location of the correspondence in the target camera
 *     weight: The weight of the factor
 *     gnc_mu: The mu convexity parameter for the Barron noise model
 *     gnc_scale: The scale parameter for the Barron noise model
 *     epsilon: Small positive value
 *     camera_model_class: The subclass of CameraCal to use as the camera model
 *
 * Outputs:
 *     res: 2dof residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkEquirectangularReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose,
    const Eigen::Matrix<Scalar, 4, 1>& source_calibration_storage,
    const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 4, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 2, 1>& source_pixel,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 976

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (254)
  const Scalar _tmp0 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp3 = -2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3 + 1;
  const Scalar _tmp5 = 2 * _source_pose[0];
  const Scalar _tmp6 = _source_pose[2] * _tmp5;
  const Scalar _tmp7 = 2 * _source_pose[1];
  const Scalar _tmp8 = _source_pose[3] * _tmp7;
  const Scalar _tmp9 = _tmp6 + _tmp8;
  const Scalar _tmp10 =
      (-source_calibration_storage(2, 0) + source_pixel(0, 0)) / source_calibration_storage(0, 0);
  const Scalar _tmp11 = std::cos(_tmp10);
  const Scalar _tmp12 =
      (-source_calibration_storage(3, 0) + source_pixel(1, 0)) / source_calibration_storage(1, 0);
  const Scalar _tmp13 = std::sin(_tmp12);
  const Scalar _tmp14 = std::cos(_tmp12);
  const Scalar _tmp15 = std::pow(_tmp14, Scalar(2));
  const Scalar _tmp16 = std::sin(_tmp10);
  const Scalar _tmp17 =
      std::pow(Scalar(std::pow(_tmp11, Scalar(2)) * _tmp15 + std::pow(_tmp13, Scalar(2)) +
                      _tmp15 * std::pow(_tmp16, Scalar(2))),
               Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp18 = _tmp14 * _tmp17;
  const Scalar _tmp19 = _tmp11 * _tmp18;
  const Scalar _tmp20 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp21 = -2 * _tmp20;
  const Scalar _tmp22 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp23 = -2 * _tmp22;
  const Scalar _tmp24 = _tmp16 * _tmp18;
  const Scalar _tmp25 = _source_pose[1] * _tmp5;
  const Scalar _tmp26 = 2 * _source_pose[2] * _source_pose[3];
  const Scalar _tmp27 = -_tmp26;
  const Scalar _tmp28 = _tmp25 + _tmp27;
  const Scalar _tmp29 = _tmp13 * _tmp17;
  const Scalar _tmp30 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp31 = _tmp19 * _tmp9 + _tmp24 * (_tmp21 + _tmp23 + 1) + _tmp28 * _tmp29 +
                        _tmp30 * source_inverse_range;
  const Scalar _tmp32 = 2 * _target_pose[0];
  const Scalar _tmp33 = _target_pose[2] * _tmp32;
  const Scalar _tmp34 = 2 * _target_pose[3];
  const Scalar _tmp35 = _target_pose[1] * _tmp34;
  const Scalar _tmp36 = -_tmp35;
  const Scalar _tmp37 = _tmp33 + _tmp36;
  const Scalar _tmp38 = _source_pose[3] * _tmp5;
  const Scalar _tmp39 = _source_pose[2] * _tmp7;
  const Scalar _tmp40 = _tmp38 + _tmp39;
  const Scalar _tmp41 = -_tmp8;
  const Scalar _tmp42 = _tmp41 + _tmp6;
  const Scalar _tmp43 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp44 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp45 = 1 - 2 * _tmp44;
  const Scalar _tmp46 = _tmp19 * (_tmp23 + _tmp45) + _tmp24 * _tmp42 + _tmp29 * _tmp40 +
                        _tmp43 * source_inverse_range;
  const Scalar _tmp47 = _target_pose[2] * _tmp34;
  const Scalar _tmp48 = _target_pose[1] * _tmp32;
  const Scalar _tmp49 = _tmp47 + _tmp48;
  const Scalar _tmp50 = _tmp25 + _tmp26;
  const Scalar _tmp51 = -_tmp38;
  const Scalar _tmp52 = _tmp39 + _tmp51;
  const Scalar _tmp53 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp54 = _tmp19 * _tmp52 + _tmp24 * _tmp50 + _tmp29 * (_tmp21 + _tmp45) +
                        _tmp53 * source_inverse_range;
  const Scalar _tmp55 = _tmp37 * _tmp46 + _tmp49 * _tmp54;
  const Scalar _tmp56 = _tmp31 * _tmp4 + _tmp55;
  const Scalar _tmp57 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp58 = 1 - 2 * _tmp57;
  const Scalar _tmp59 = _tmp1 + _tmp58;
  const Scalar _tmp60 = _tmp33 + _tmp35;
  const Scalar _tmp61 = 2 * _target_pose[1] * _target_pose[2];
  const Scalar _tmp62 = _target_pose[0] * _tmp34;
  const Scalar _tmp63 = -_tmp62;
  const Scalar _tmp64 = _tmp61 + _tmp63;
  const Scalar _tmp65 = _tmp31 * _tmp60 + _tmp54 * _tmp64;
  const Scalar _tmp66 = _tmp46 * _tmp59 + _tmp65;
  const Scalar _tmp67 = _tmp66 + epsilon * ((((_tmp66) > 0) - ((_tmp66) < 0)) + Scalar(0.5));
  const Scalar _tmp68 = target_calibration_storage(0, 0) * std::atan2(_tmp56, _tmp67) +
                        target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp69 = _tmp3 + _tmp58;
  const Scalar _tmp70 = _tmp61 + _tmp62;
  const Scalar _tmp71 = -_tmp47;
  const Scalar _tmp72 = _tmp48 + _tmp71;
  const Scalar _tmp73 = _tmp31 * _tmp72 + _tmp46 * _tmp70;
  const Scalar _tmp74 = _tmp54 * _tmp69 + _tmp73;
  const Scalar _tmp75 = std::pow(_tmp56, Scalar(2));
  const Scalar _tmp76 = std::pow(_tmp66, Scalar(2)) + _tmp75;
  const Scalar _tmp77 = _tmp76 + epsilon;
  const Scalar _tmp78 = std::sqrt(_tmp77);
  const Scalar _tmp79 = target_calibration_storage(1, 0) * std::atan2(_tmp74, _tmp78) +
                        target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp80 = std::pow(_tmp68, Scalar(2)) + std::pow(_tmp79, Scalar(2)) + epsilon;
  const Scalar _tmp81 = std::pow(_tmp80, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp82 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp83 = epsilon + std::fabs(_tmp82);
  const Scalar _tmp84 = 2 - _tmp82;
  const Scalar _tmp85 =
      _tmp84 + epsilon * (2 * std::min<Scalar>(0, (((_tmp84) > 0) - ((_tmp84) < 0))) + 1);
  const Scalar _tmp86 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp87 = _tmp80 * _tmp86 / _tmp83 + 1;
  const Scalar _tmp88 = (Scalar(1) / Scalar(2)) * _tmp85;
  const Scalar _tmp89 =
      std::sqrt(Scalar(2)) * std::sqrt(Scalar(_tmp83 * (std::pow(_tmp87, _tmp88) - 1) / _tmp85));
  const Scalar _tmp90 = std::pow(_tmp74, Scalar(2));
  const Scalar _tmp91 =
      std::sqrt(weight) *
      std::sqrt(Scalar(std::max<Scalar>(0, (((_tmp76 + _tmp90) > 0) - ((_tmp76 + _tmp90) < 0))))) *
      std::sqrt(Scalar(
          std::max<Scalar>(0, std::min<Scalar>((((Scalar(M_PI) - std::fabs(_tmp10)) > 0) -
                                                ((Scalar(M_PI) - std::fabs(_tmp10)) < 0)),
                                               (((-std::fabs(_tmp12) + Scalar(M_PI_2)) > 0) -
                                                ((-std::fabs(_tmp12) + Scalar(M_PI_2)) < 0))))));
  const Scalar _tmp92 = _tmp89 * _tmp91;
  const Scalar _tmp93 = _tmp81 * _tmp92;
  const Scalar _tmp94 = _tmp68 * _tmp93;
  const Scalar _tmp95 = _tmp79 * _tmp93;
  const Scalar _tmp96 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp97 = -_tmp44;
  const Scalar _tmp98 = _tmp96 + _tmp97;
  const Scalar _tmp99 = -_tmp22;
  const Scalar _tmp100 = _tmp20 + _tmp99;
  const Scalar _tmp101 = -_tmp39;
  const Scalar _tmp102 = _tmp19 * (_tmp101 + _tmp51) + _tmp29 * (_tmp100 + _tmp98);
  const Scalar _tmp103 = -_tmp96;
  const Scalar _tmp104 = _tmp103 + _tmp44;
  const Scalar _tmp105 = _tmp19 * (_tmp100 + _tmp104) + _tmp29 * _tmp52;
  const Scalar _tmp106 = -_tmp25;
  const Scalar _tmp107 = _tmp19 * (_tmp106 + _tmp26) + _tmp29 * _tmp9;
  const Scalar _tmp108 = _tmp102 * _tmp59 + _tmp105 * _tmp64 + _tmp107 * _tmp60;
  const Scalar _tmp109 = 2 * _tmp66;
  const Scalar _tmp110 = _tmp102 * _tmp37 + _tmp105 * _tmp49 + _tmp107 * _tmp4;
  const Scalar _tmp111 = 2 * _tmp56;
  const Scalar _tmp112 = _tmp74 / (_tmp77 * std::sqrt(_tmp77));
  const Scalar _tmp113 = (Scalar(1) / Scalar(2)) * _tmp112;
  const Scalar _tmp114 = Scalar(1.0) / (_tmp78);
  const Scalar _tmp115 = -_tmp113 * (_tmp108 * _tmp109 + _tmp110 * _tmp111) +
                         _tmp114 * (_tmp102 * _tmp70 + _tmp105 * _tmp69 + _tmp107 * _tmp72);
  const Scalar _tmp116 = target_calibration_storage(1, 0) / (_tmp77 + _tmp90);
  const Scalar _tmp117 = _tmp116 * _tmp79;
  const Scalar _tmp118 = 2 * _tmp117;
  const Scalar _tmp119 = _tmp118 * _tmp77;
  const Scalar _tmp120 = Scalar(1.0) / (_tmp67);
  const Scalar _tmp121 = std::pow(_tmp67, Scalar(2));
  const Scalar _tmp122 = _tmp56 / _tmp121;
  const Scalar _tmp123 = -_tmp108 * _tmp122 + _tmp110 * _tmp120;
  const Scalar _tmp124 = target_calibration_storage(0, 0) / (_tmp121 + _tmp75);
  const Scalar _tmp125 = _tmp124 * _tmp68;
  const Scalar _tmp126 = 2 * _tmp125;
  const Scalar _tmp127 = _tmp121 * _tmp126;
  const Scalar _tmp128 = _tmp115 * _tmp119 + _tmp123 * _tmp127;
  const Scalar _tmp129 = (Scalar(1) / Scalar(2)) * _tmp68;
  const Scalar _tmp130 = _tmp81 * _tmp86 * std::pow(_tmp87, Scalar(_tmp88 - 1)) * _tmp91 / _tmp89;
  const Scalar _tmp131 = _tmp129 * _tmp130;
  const Scalar _tmp132 = _tmp92 / (_tmp80 * std::sqrt(_tmp80));
  const Scalar _tmp133 = _tmp129 * _tmp132;
  const Scalar _tmp134 = _tmp124 * _tmp93;
  const Scalar _tmp135 = _tmp121 * _tmp134;
  const Scalar _tmp136 = _tmp123 * _tmp135 + _tmp128 * _tmp131 - _tmp128 * _tmp133;
  const Scalar _tmp137 = -_tmp20;
  const Scalar _tmp138 = _tmp137 + _tmp22;
  const Scalar _tmp139 = _tmp19 * _tmp42 + _tmp24 * (_tmp104 + _tmp138);
  const Scalar _tmp140 = _tmp19 * _tmp50 + _tmp24 * (_tmp101 + _tmp38);
  const Scalar _tmp141 = -_tmp6;
  const Scalar _tmp142 =
      _tmp19 * (_tmp137 + _tmp44 + _tmp96 + _tmp99) + _tmp24 * (_tmp141 + _tmp41);
  const Scalar _tmp143 = _tmp139 * _tmp37 + _tmp140 * _tmp49 + _tmp142 * _tmp4;
  const Scalar _tmp144 = _tmp139 * _tmp59 + _tmp140 * _tmp64 + _tmp142 * _tmp60;
  const Scalar _tmp145 = _tmp120 * _tmp143 - _tmp122 * _tmp144;
  const Scalar _tmp146 = -_tmp113 * (_tmp109 * _tmp144 + _tmp111 * _tmp143) +
                         _tmp114 * (_tmp139 * _tmp70 + _tmp140 * _tmp69 + _tmp142 * _tmp72);
  const Scalar _tmp147 = _tmp119 * _tmp146 + _tmp127 * _tmp145;
  const Scalar _tmp148 = _tmp131 * _tmp147 - _tmp133 * _tmp147 + _tmp135 * _tmp145;
  const Scalar _tmp149 = _tmp24 * _tmp40 + _tmp29 * (_tmp141 + _tmp8);
  const Scalar _tmp150 = _tmp24 * _tmp28 + _tmp29 * (_tmp103 + _tmp20 + _tmp22 + _tmp97);
  const Scalar _tmp151 = _tmp24 * (_tmp138 + _tmp98) + _tmp29 * (_tmp106 + _tmp27);
  const Scalar _tmp152 = _tmp149 * _tmp59 + _tmp150 * _tmp60 + _tmp151 * _tmp64;
  const Scalar _tmp153 = _tmp149 * _tmp37 + _tmp150 * _tmp4 + _tmp151 * _tmp49;
  const Scalar _tmp154 = -_tmp113 * (_tmp109 * _tmp152 + _tmp111 * _tmp153) +
                         _tmp114 * (_tmp149 * _tmp70 + _tmp150 * _tmp72 + _tmp151 * _tmp69);
  const Scalar _tmp155 = _tmp120 * _tmp153 - _tmp122 * _tmp152;
  const Scalar _tmp156 = _tmp119 * _tmp154 + _tmp127 * _tmp155;
  const Scalar _tmp157 = _tmp131 * _tmp156 - _tmp133 * _tmp156 + _tmp135 * _tmp155;
  const Scalar _tmp158 = _tmp120 * source_inverse_range;
  const Scalar _tmp159 = _tmp158 * _tmp4;
  const Scalar _tmp160 = _tmp122 * source_inverse_range;
  const Scalar _tmp161 = _tmp160 * _tmp60;
  const Scalar _tmp162 = _tmp159 - _tmp161;
  const Scalar _tmp163 = _tmp109 * source_inverse_range;
  const Scalar _tmp164 = _tmp163 * _tmp60;
  const Scalar _tmp165 = _tmp111 * source_inverse_range;
  const Scalar _tmp166 = _tmp165 * _tmp4;
  const Scalar _tmp167 = _tmp114 * source_inverse_range;
  const Scalar _tmp168 = _tmp167 * _tmp72;
  const Scalar _tmp169 = -_tmp113 * (_tmp164 + _tmp166) + _tmp168;
  const Scalar _tmp170 = _tmp119 * _tmp169 + _tmp127 * _tmp162;
  const Scalar _tmp171 = _tmp131 * _tmp170 - _tmp133 * _tmp170 + _tmp135 * _tmp162;
  const Scalar _tmp172 = _tmp158 * _tmp49;
  const Scalar _tmp173 = _tmp160 * _tmp64;
  const Scalar _tmp174 = _tmp172 - _tmp173;
  const Scalar _tmp175 = _tmp167 * _tmp69;
  const Scalar _tmp176 = _tmp163 * _tmp64;
  const Scalar _tmp177 = _tmp165 * _tmp49;
  const Scalar _tmp178 = -_tmp113 * (_tmp176 + _tmp177) + _tmp175;
  const Scalar _tmp179 = _tmp119 * _tmp178 + _tmp127 * _tmp174;
  const Scalar _tmp180 = _tmp131 * _tmp179 - _tmp133 * _tmp179 + _tmp135 * _tmp174;
  const Scalar _tmp181 = _tmp165 * _tmp37;
  const Scalar _tmp182 = _tmp163 * _tmp59;
  const Scalar _tmp183 = _tmp167 * _tmp70;
  const Scalar _tmp184 = -_tmp113 * (_tmp181 + _tmp182) + _tmp183;
  const Scalar _tmp185 = _tmp160 * _tmp59;
  const Scalar _tmp186 = _tmp158 * _tmp37;
  const Scalar _tmp187 = -_tmp185 + _tmp186;
  const Scalar _tmp188 = _tmp119 * _tmp184 + _tmp127 * _tmp187;
  const Scalar _tmp189 = _tmp131 * _tmp188 - _tmp133 * _tmp188 + _tmp135 * _tmp187;
  const Scalar _tmp190 = -_tmp61;
  const Scalar _tmp191 = -_tmp48;
  const Scalar _tmp192 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp193 = -_tmp192;
  const Scalar _tmp194 = _tmp193 + _tmp57;
  const Scalar _tmp195 = -_tmp0;
  const Scalar _tmp196 = _tmp195 + _tmp2;
  const Scalar _tmp197 =
      _tmp31 * (_tmp191 + _tmp47) + _tmp46 * (_tmp190 + _tmp63) + _tmp54 * (_tmp194 + _tmp196);
  const Scalar _tmp198 = -_tmp57;
  const Scalar _tmp199 = _tmp192 + _tmp198;
  const Scalar _tmp200 =
      -_tmp112 * _tmp197 * _tmp66 + _tmp114 * (_tmp46 * (_tmp196 + _tmp199) + _tmp65);
  const Scalar _tmp201 = -_tmp111 * _tmp125 * _tmp197 + _tmp119 * _tmp200;
  const Scalar _tmp202 = _tmp129 * _tmp201;
  const Scalar _tmp203 = _tmp130 * _tmp202 - _tmp132 * _tmp202 - _tmp134 * _tmp197 * _tmp56;
  const Scalar _tmp204 = -_tmp2;
  const Scalar _tmp205 = _tmp0 + _tmp204;
  const Scalar _tmp206 = -_tmp33;
  const Scalar _tmp207 =
      _tmp31 * (_tmp206 + _tmp36) + _tmp46 * (_tmp194 + _tmp205) + _tmp54 * (_tmp190 + _tmp62);
  const Scalar _tmp208 = _tmp31 * (_tmp192 + _tmp195 + _tmp204 + _tmp57) + _tmp55;
  const Scalar _tmp209 = _tmp114 * _tmp74 * (_tmp109 * _tmp208 + _tmp111 * _tmp207);
  const Scalar _tmp210 = _tmp120 * _tmp207 - _tmp122 * _tmp208;
  const Scalar _tmp211 = -_tmp117 * _tmp209 + _tmp127 * _tmp210;
  const Scalar _tmp212 = _tmp131 * _tmp211 - _tmp133 * _tmp211 + _tmp135 * _tmp210;
  const Scalar _tmp213 = _tmp54 * (_tmp199 + _tmp205) + _tmp73;
  const Scalar _tmp214 = -_tmp112 * _tmp213 * _tmp56 +
                         _tmp114 * (_tmp31 * (_tmp0 + _tmp193 + _tmp198 + _tmp2) +
                                    _tmp46 * (_tmp206 + _tmp35) + _tmp54 * (_tmp191 + _tmp71));
  const Scalar _tmp215 = _tmp213 * _tmp67;
  const Scalar _tmp216 = _tmp119 * _tmp214 + _tmp126 * _tmp215;
  const Scalar _tmp217 = _tmp131 * _tmp216 - _tmp133 * _tmp216 + _tmp134 * _tmp215;
  const Scalar _tmp218 = -_tmp113 * (-_tmp164 - _tmp166) - _tmp168;
  const Scalar _tmp219 = -_tmp159 + _tmp161;
  const Scalar _tmp220 = _tmp119 * _tmp218 + _tmp127 * _tmp219;
  const Scalar _tmp221 = _tmp131 * _tmp220 - _tmp133 * _tmp220 + _tmp135 * _tmp219;
  const Scalar _tmp222 = -_tmp172 + _tmp173;
  const Scalar _tmp223 = _tmp77 * (-_tmp113 * (-_tmp176 - _tmp177) - _tmp175);
  const Scalar _tmp224 = _tmp118 * _tmp223 + _tmp127 * _tmp222;
  const Scalar _tmp225 = _tmp131 * _tmp224 - _tmp133 * _tmp224 + _tmp135 * _tmp222;
  const Scalar _tmp226 = _tmp185 - _tmp186;
  const Scalar _tmp227 = -_tmp113 * (-_tmp181 - _tmp182) - _tmp183;
  const Scalar _tmp228 = _tmp119 * _tmp227 + _tmp127 * _tmp226;
  const Scalar _tmp229 = _tmp131 * _tmp228 - _tmp133 * _tmp228 + _tmp135 * _tmp226;
  const Scalar _tmp230 = _tmp30 * _tmp4 + _tmp37 * _tmp43 + _tmp49 * _tmp53;
  const Scalar _tmp231 = _tmp30 * _tmp60 + _tmp43 * _tmp59 + _tmp53 * _tmp64;
  const Scalar _tmp232 = _tmp121 * (_tmp120 * _tmp230 - _tmp122 * _tmp231);
  const Scalar _tmp233 = -_tmp113 * (_tmp109 * _tmp231 + _tmp111 * _tmp230) +
                         _tmp114 * (_tmp30 * _tmp72 + _tmp43 * _tmp70 + _tmp53 * _tmp69);
  const Scalar _tmp234 = _tmp119 * _tmp233 + _tmp126 * _tmp232;
  const Scalar _tmp235 = _tmp131 * _tmp234 - _tmp133 * _tmp234 + _tmp134 * _tmp232;
  const Scalar _tmp236 = (Scalar(1) / Scalar(2)) * _tmp79;
  const Scalar _tmp237 = _tmp130 * _tmp236;
  const Scalar _tmp238 = _tmp132 * _tmp236;
  const Scalar _tmp239 = _tmp116 * _tmp93;
  const Scalar _tmp240 = _tmp239 * _tmp77;
  const Scalar _tmp241 = _tmp115 * _tmp240 + _tmp128 * _tmp237 - _tmp128 * _tmp238;
  const Scalar _tmp242 = _tmp146 * _tmp240 + _tmp147 * _tmp237 - _tmp147 * _tmp238;
  const Scalar _tmp243 = _tmp154 * _tmp240 + _tmp156 * _tmp237 - _tmp156 * _tmp238;
  const Scalar _tmp244 = _tmp169 * _tmp240 + _tmp170 * _tmp237 - _tmp170 * _tmp238;
  const Scalar _tmp245 = _tmp178 * _tmp240 + _tmp179 * _tmp237 - _tmp179 * _tmp238;
  const Scalar _tmp246 = _tmp184 * _tmp240 + _tmp188 * _tmp237 - _tmp188 * _tmp238;
  const Scalar _tmp247 = _tmp200 * _tmp240 + _tmp201 * _tmp237 - _tmp201 * _tmp238;
  const Scalar _tmp248 =
      -Scalar(1) / Scalar(2) * _tmp209 * _tmp239 + _tmp211 * _tmp237 - _tmp211 * _tmp238;
  const Scalar _tmp249 = _tmp214 * _tmp240 + _tmp216 * _tmp237 - _tmp216 * _tmp238;
  const Scalar _tmp250 = _tmp218 * _tmp240 + _tmp220 * _tmp237 - _tmp220 * _tmp238;
  const Scalar _tmp251 = _tmp223 * _tmp239 + _tmp224 * _tmp237 - _tmp224 * _tmp238;
  const Scalar _tmp252 = _tmp227 * _tmp240 + _tmp228 * _tmp237 - _tmp228 * _tmp238;
  const Scalar _tmp253 = _tmp233 * _tmp240 + _tmp234 * _tmp237 - _tmp234 * _tmp238;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp94;
    _res(1, 0) = _tmp95;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp136;
    _jacobian(0, 1) = _tmp148;
    _jacobian(0, 2) = _tmp157;
    _jacobian(0, 3) = _tmp171;
    _jacobian(0, 4) = _tmp180;
    _jacobian(0, 5) = _tmp189;
    _jacobian(0, 6) = _tmp203;
    _jacobian(0, 7) = _tmp212;
    _jacobian(0, 8) = _tmp217;
    _jacobian(0, 9) = _tmp221;
    _jacobian(0, 10) = _tmp225;
    _jacobian(0, 11) = _tmp229;
    _jacobian(0, 12) = _tmp235;
    _jacobian(1, 0) = _tmp241;
    _jacobian(1, 1) = _tmp242;
    _jacobian(1, 2) = _tmp243;
    _jacobian(1, 3) = _tmp244;
    _jacobian(1, 4) = _tmp245;
    _jacobian(1, 5) = _tmp246;
    _jacobian(1, 6) = _tmp247;
    _jacobian(1, 7) = _tmp248;
    _jacobian(1, 8) = _tmp249;
    _jacobian(1, 9) = _tmp250;
    _jacobian(1, 10) = _tmp251;
    _jacobian(1, 11) = _tmp252;
    _jacobian(1, 12) = _tmp253;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp136, Scalar(2)) + std::pow(_tmp241, Scalar(2));
    _hessian(0, 1) = 0;
    _hessian(0, 2) = 0;
    _hessian(0, 3) = 0;
    _hessian(0, 4) = 0;
    _hessian(0, 5) = 0;
    _hessian(0, 6) = 0;
    _hessian(0, 7) = 0;
    _hessian(0, 8) = 0;
    _hessian(0, 9) = 0;
    _hessian(0, 10) = 0;
    _hessian(0, 11) = 0;
    _hessian(0, 12) = 0;
    _hessian(1, 0) = _tmp136 * _tmp148 + _tmp241 * _tmp242;
    _hessian(1, 1) = std::pow(_tmp148, Scalar(2)) + std::pow(_tmp242, Scalar(2));
    _hessian(1, 2) = 0;
    _hessian(1, 3) = 0;
    _hessian(1, 4) = 0;
    _hessian(1, 5) = 0;
    _hessian(1, 6) = 0;
    _hessian(1, 7) = 0;
    _hessian(1, 8) = 0;
    _hessian(1, 9) = 0;
    _hessian(1, 10) = 0;
    _hessian(1, 11) = 0;
    _hessian(1, 12) = 0;
    _hessian(2, 0) = _tmp136 * _tmp157 + _tmp241 * _tmp243;
    _hessian(2, 1) = _tmp148 * _tmp157 + _tmp242 * _tmp243;
    _hessian(2, 2) = std::pow(_tmp157, Scalar(2)) + std::pow(_tmp243, Scalar(2));
    _hessian(2, 3) = 0;
    _hessian(2, 4) = 0;
    _hessian(2, 5) = 0;
    _hessian(2, 6) = 0;
    _hessian(2, 7) = 0;
    _hessian(2, 8) = 0;
    _hessian(2, 9) = 0;
    _hessian(2, 10) = 0;
    _hessian(2, 11) = 0;
    _hessian(2, 12) = 0;
    _hessian(3, 0) = _tmp136 * _tmp171 + _tmp241 * _tmp244;
    _hessian(3, 1) = _tmp148 * _tmp171 + _tmp242 * _tmp244;
    _hessian(3, 2) = _tmp157 * _tmp171 + _tmp243 * _tmp244;
    _hessian(3, 3) = std::pow(_tmp171, Scalar(2)) + std::pow(_tmp244, Scalar(2));
    _hessian(3, 4) = 0;
    _hessian(3, 5) = 0;
    _hessian(3, 6) = 0;
    _hessian(3, 7) = 0;
    _hessian(3, 8) = 0;
    _hessian(3, 9) = 0;
    _hessian(3, 10) = 0;
    _hessian(3, 11) = 0;
    _hessian(3, 12) = 0;
    _hessian(4, 0) = _tmp136 * _tmp180 + _tmp241 * _tmp245;
    _hessian(4, 1) = _tmp148 * _tmp180 + _tmp242 * _tmp245;
    _hessian(4, 2) = _tmp157 * _tmp180 + _tmp243 * _tmp245;
    _hessian(4, 3) = _tmp171 * _tmp180 + _tmp244 * _tmp245;
    _hessian(4, 4) = std::pow(_tmp180, Scalar(2)) + std::pow(_tmp245, Scalar(2));
    _hessian(4, 5) = 0;
    _hessian(4, 6) = 0;
    _hessian(4, 7) = 0;
    _hessian(4, 8) = 0;
    _hessian(4, 9) = 0;
    _hessian(4, 10) = 0;
    _hessian(4, 11) = 0;
    _hessian(4, 12) = 0;
    _hessian(5, 0) = _tmp136 * _tmp189 + _tmp241 * _tmp246;
    _hessian(5, 1) = _tmp148 * _tmp189 + _tmp242 * _tmp246;
    _hessian(5, 2) = _tmp157 * _tmp189 + _tmp243 * _tmp246;
    _hessian(5, 3) = _tmp171 * _tmp189 + _tmp244 * _tmp246;
    _hessian(5, 4) = _tmp180 * _tmp189 + _tmp245 * _tmp246;
    _hessian(5, 5) = std::pow(_tmp189, Scalar(2)) + std::pow(_tmp246, Scalar(2));
    _hessian(5, 6) = 0;
    _hessian(5, 7) = 0;
    _hessian(5, 8) = 0;
    _hessian(5, 9) = 0;
    _hessian(5, 10) = 0;
    _hessian(5, 11) = 0;
    _hessian(5, 12) = 0;
    _hessian(6, 0) = _tmp136 * _tmp203 + _tmp241 * _tmp247;
    _hessian(6, 1) = _tmp148 * _tmp203 + _tmp242 * _tmp247;
    _hessian(6, 2) = _tmp157 * _tmp203 + _tmp243 * _tmp247;
    _hessian(6, 3) = _tmp171 * _tmp203 + _tmp244 * _tmp247;
    _hessian(6, 4) = _tmp180 * _tmp203 + _tmp245 * _tmp247;
    _hessian(6, 5) = _tmp189 * _tmp203 + _tmp246 * _tmp247;
    _hessian(6, 6) = std::pow(_tmp203, Scalar(2)) + std::pow(_tmp247, Scalar(2));
    _hessian(6, 7) = 0;
    _hessian(6, 8) = 0;
    _hessian(6, 9) = 0;
    _hessian(6, 10) = 0;
    _hessian(6, 11) = 0;
    _hessian(6, 12) = 0;
    _hessian(7, 0) = _tmp136 * _tmp212 + _tmp241 * _tmp248;
    _hessian(7, 1) = _tmp148 * _tmp212 + _tmp242 * _tmp248;
    _hessian(7, 2) = _tmp157 * _tmp212 + _tmp243 * _tmp248;
    _hessian(7, 3) = _tmp171 * _tmp212 + _tmp244 * _tmp248;
    _hessian(7, 4) = _tmp180 * _tmp212 + _tmp245 * _tmp248;
    _hessian(7, 5) = _tmp189 * _tmp212 + _tmp246 * _tmp248;
    _hessian(7, 6) = _tmp203 * _tmp212 + _tmp247 * _tmp248;
    _hessian(7, 7) = std::pow(_tmp212, Scalar(2)) + std::pow(_tmp248, Scalar(2));
    _hessian(7, 8) = 0;
    _hessian(7, 9) = 0;
    _hessian(7, 10) = 0;
    _hessian(7, 11) = 0;
    _hessian(7, 12) = 0;
    _hessian(8, 0) = _tmp136 * _tmp217 + _tmp241 * _tmp249;
    _hessian(8, 1) = _tmp148 * _tmp217 + _tmp242 * _tmp249;
    _hessian(8, 2) = _tmp157 * _tmp217 + _tmp243 * _tmp249;
    _hessian(8, 3) = _tmp171 * _tmp217 + _tmp244 * _tmp249;
    _hessian(8, 4) = _tmp180 * _tmp217 + _tmp245 * _tmp249;
    _hessian(8, 5) = _tmp189 * _tmp217 + _tmp246 * _tmp249;
    _hessian(8, 6) = _tmp203 * _tmp217 + _tmp247 * _tmp249;
    _hessian(8, 7) = _tmp212 * _tmp217 + _tmp248 * _tmp249;
    _hessian(8, 8) = std::pow(_tmp217, Scalar(2)) + std::pow(_tmp249, Scalar(2));
    _hessian(8, 9) = 0;
    _hessian(8, 10) = 0;
    _hessian(8, 11) = 0;
    _hessian(8, 12) = 0;
    _hessian(9, 0) = _tmp136 * _tmp221 + _tmp241 * _tmp250;
    _hessian(9, 1) = _tmp148 * _tmp221 + _tmp242 * _tmp250;
    _hessian(9, 2) = _tmp157 * _tmp221 + _tmp243 * _tmp250;
    _hessian(9, 3) = _tmp171 * _tmp221 + _tmp244 * _tmp250;
    _hessian(9, 4) = _tmp180 * _tmp221 + _tmp245 * _tmp250;
    _hessian(9, 5) = _tmp189 * _tmp221 + _tmp246 * _tmp250;
    _hessian(9, 6) = _tmp203 * _tmp221 + _tmp247 * _tmp250;
    _hessian(9, 7) = _tmp212 * _tmp221 + _tmp248 * _tmp250;
    _hessian(9, 8) = _tmp217 * _tmp221 + _tmp249 * _tmp250;
    _hessian(9, 9) = std::pow(_tmp221, Scalar(2)) + std::pow(_tmp250, Scalar(2));
    _hessian(9, 10) = 0;
    _hessian(9, 11) = 0;
    _hessian(9, 12) = 0;
    _hessian(10, 0) = _tmp136 * _tmp225 + _tmp241 * _tmp251;
    _hessian(10, 1) = _tmp148 * _tmp225 + _tmp242 * _tmp251;
    _hessian(10, 2) = _tmp157 * _tmp225 + _tmp243 * _tmp251;
    _hessian(10, 3) = _tmp171 * _tmp225 + _tmp244 * _tmp251;
    _hessian(10, 4) = _tmp180 * _tmp225 + _tmp245 * _tmp251;
    _hessian(10, 5) = _tmp189 * _tmp225 + _tmp246 * _tmp251;
    _hessian(10, 6) = _tmp203 * _tmp225 + _tmp247 * _tmp251;
    _hessian(10, 7) = _tmp212 * _tmp225 + _tmp248 * _tmp251;
    _hessian(10, 8) = _tmp217 * _tmp225 + _tmp249 * _tmp251;
    _hessian(10, 9) = _tmp221 * _tmp225 + _tmp250 * _tmp251;
    _hessian(10, 10) = std::pow(_tmp225, Scalar(2)) + std::pow(_tmp251, Scalar(2));
    _hessian(10, 11) = 0;
    _hessian(10, 12) = 0;
    _hessian(11, 0) = _tmp136 * _tmp229 + _tmp241 * _tmp252;
    _hessian(11, 1) = _tmp148 * _tmp229 + _tmp242 * _tmp252;
    _hessian(11, 2) = _tmp157 * _tmp229 + _tmp243 * _tmp252;
    _hessian(11, 3) = _tmp171 * _tmp229 + _tmp244 * _tmp252;
    _hessian(11, 4) = _tmp180 * _tmp229 + _tmp245 * _tmp252;
    _hessian(11, 5) = _tmp189 * _tmp229 + _tmp246 * _tmp252;
    _hessian(11, 6) = _tmp203 * _tmp229 + _tmp247 * _tmp252;
    _hessian(11, 7) = _tmp212 * _tmp229 + _tmp248 * _tmp252;
    _hessian(11, 8) = _tmp217 * _tmp229 + _tmp249 * _tmp252;
    _hessian(11, 9) = _tmp221 * _tmp229 + _tmp250 * _tmp252;
    _hessian(11, 10) = _tmp225 * _tmp229 + _tmp251 * _tmp252;
    _hessian(11, 11) = std::pow(_tmp229, Scalar(2)) + std::pow(_tmp252, Scalar(2));
    _hessian(11, 12) = 0;
    _hessian(12, 0) = _tmp136 * _tmp235 + _tmp241 * _tmp253;
    _hessian(12, 1) = _tmp148 * _tmp235 + _tmp242 * _tmp253;
    _hessian(12, 2) = _tmp157 * _tmp235 + _tmp243 * _tmp253;
    _hessian(12, 3) = _tmp171 * _tmp235 + _tmp244 * _tmp253;
    _hessian(12, 4) = _tmp180 * _tmp235 + _tmp245 * _tmp253;
    _hessian(12, 5) = _tmp189 * _tmp235 + _tmp246 * _tmp253;
    _hessian(12, 6) = _tmp203 * _tmp235 + _tmp247 * _tmp253;
    _hessian(12, 7) = _tmp212 * _tmp235 + _tmp248 * _tmp253;
    _hessian(12, 8) = _tmp217 * _tmp235 + _tmp249 * _tmp253;
    _hessian(12, 9) = _tmp221 * _tmp235 + _tmp250 * _tmp253;
    _hessian(12, 10) = _tmp225 * _tmp235 + _tmp251 * _tmp253;
    _hessian(12, 11) = _tmp229 * _tmp235 + _tmp252 * _tmp253;
    _hessian(12, 12) = std::pow(_tmp235, Scalar(2)) + std::pow(_tmp253, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp136 * _tmp94 + _tmp241 * _tmp95;
    _rhs(1, 0) = _tmp148 * _tmp94 + _tmp242 * _tmp95;
    _rhs(2, 0) = _tmp157 * _tmp94 + _tmp243 * _tmp95;
    _rhs(3, 0) = _tmp171 * _tmp94 + _tmp244 * _tmp95;
    _rhs(4, 0) = _tmp180 * _tmp94 + _tmp245 * _tmp95;
    _rhs(5, 0) = _tmp189 * _tmp94 + _tmp246 * _tmp95;
    _rhs(6, 0) = _tmp203 * _tmp94 + _tmp247 * _tmp95;
    _rhs(7, 0) = _tmp212 * _tmp94 + _tmp248 * _tmp95;
    _rhs(8, 0) = _tmp217 * _tmp94 + _tmp249 * _tmp95;
    _rhs(9, 0) = _tmp221 * _tmp94 + _tmp250 * _tmp95;
    _rhs(10, 0) = _tmp225 * _tmp94 + _tmp251 * _tmp95;
    _rhs(11, 0) = _tmp229 * _tmp94 + _tmp252 * _tmp95;
    _rhs(12, 0) = _tmp235 * _tmp94 + _tmp253 * _tmp95;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym