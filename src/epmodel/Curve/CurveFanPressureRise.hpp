/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFANPRESSURERISE_HPP
#define EPMODEL_CURVEFANPRESSURERISE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveFanPressureRise_Impl;
}

class EPMODEL_API CurveFanPressureRise : public ModelObject
{
 public:
  explicit CurveFanPressureRise(const Model& model);

  virtual ~CurveFanPressureRise() override = default;
  CurveFanPressureRise(const CurveFanPressureRise& other) = default;
  CurveFanPressureRise(CurveFanPressureRise&& other) = default;
  CurveFanPressureRise& operator=(const CurveFanPressureRise&) = default;
  CurveFanPressureRise& operator=(CurveFanPressureRise&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveFanPressureRise scalar accessor names/signatures.
  // - Field Mapping: coefficient/min/max and output-limit APIs map directly to E+ Curve:FanPressureRise fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveFanPressureRise.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
  double coefficient1C1() const;
  double coefficient2C2() const;
  double coefficient3C3() const;
  double coefficient4C4() const;
  double minimumValueofQfan() const;
  double maximumValueofQfan() const;
  double minimumValueofPsm() const;
  double maximumValueofPsm() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;

  bool setCoefficient1C1(double coefficient1C1);
  bool setCoefficient2C2(double coefficient2C2);
  bool setCoefficient3C3(double coefficient3C3);
  bool setCoefficient4C4(double coefficient4C4);
  bool setMinimumValueofQfan(double minimumValueofQfan);
  bool setMaximumValueofQfan(double maximumValueofQfan);
  bool setMinimumValueofPsm(double minimumValueofPsm);
  bool setMaximumValueofPsm(double maximumValueofPsm);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();

 protected:
  using ImplType = detail::CurveFanPressureRise_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveFanPressureRise(std::shared_ptr<detail::CurveFanPressureRise_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
