/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCOIL_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGCOIL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelFoulingCoil_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelFoulingCoil_Impl() override = default;

  std::string foulingInputMethod() const;
  bool isFoulingInputMethodDefaulted() const;
  bool setFoulingInputMethod(const std::string& foulingInputMethod);
  void resetFoulingInputMethod();

  boost::optional<double> uAFouled() const;
  bool setUAFouled(double uAFouled);
  void resetUAFouled();

  double waterSideFoulingFactor() const;
  bool isWaterSideFoulingFactorDefaulted() const;
  bool setWaterSideFoulingFactor(double waterSideFoulingFactor);
  void resetWaterSideFoulingFactor();

  double airSideFoulingFactor() const;
  bool isAirSideFoulingFactorDefaulted() const;
  bool setAirSideFoulingFactor(double airSideFoulingFactor);
  void resetAirSideFoulingFactor();

  boost::optional<double> outsideCoilSurfaceArea() const;
  bool setOutsideCoilSurfaceArea(double outsideCoilSurfaceArea);
  void resetOutsideCoilSurfaceArea();

  double insidetoOutsideCoilSurfaceAreaRatio() const;
  bool isInsidetoOutsideCoilSurfaceAreaRatioDefaulted() const;
  bool setInsidetoOutsideCoilSurfaceAreaRatio(double insidetoOutsideCoilSurfaceAreaRatio);
  void resetInsidetoOutsideCoilSurfaceAreaRatio();

  std::vector<std::string> foulingInputMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
