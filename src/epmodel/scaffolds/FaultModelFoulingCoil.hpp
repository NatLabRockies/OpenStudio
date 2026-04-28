/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCOIL_HPP
#define EPMODEL_FAULTMODELFOULINGCOIL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelFoulingCoil_Impl;
}

class EPMODEL_API FaultModelFoulingCoil : public ModelObject
{
 public:
  explicit FaultModelFoulingCoil(const Model& model);

  virtual ~FaultModelFoulingCoil() override = default;
  FaultModelFoulingCoil(const FaultModelFoulingCoil& other) = default;
  FaultModelFoulingCoil(FaultModelFoulingCoil&& other) = default;
  FaultModelFoulingCoil& operator=(const FaultModelFoulingCoil&) = default;
  FaultModelFoulingCoil& operator=(FaultModelFoulingCoil&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> foulingInputMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: foulingInputMethod, uAFouled, waterSideFoulingFactor, airSideFoulingFactor,
  //   outsideCoilSurfaceArea, and insidetoOutsideCoilSurfaceAreaRatio map directly to the identically named
  //   EnergyPlus FaultModel:Fouling:Coil scalar fields.
  // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
  // - Field Mapping: Coil Name, Availability Schedule Name, and Severity Schedule Name are relationship-like
  //   object-list target-link fields and intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::FaultModelFoulingCoil_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelFoulingCoil(std::shared_ptr<detail::FaultModelFoulingCoil_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
