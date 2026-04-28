/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEHEIGHTVARIATION_HPP
#define EPMODEL_SITEHEIGHTVARIATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SiteHeightVariation_Impl;
}

class EPMODEL_API SiteHeightVariation : public ModelObject
{
 public:
  explicit SiteHeightVariation(const Model& model);

  virtual ~SiteHeightVariation() override = default;
  SiteHeightVariation(const SiteHeightVariation& other) = default;
  SiteHeightVariation(SiteHeightVariation&& other) = default;
  SiteHeightVariation& operator=(const SiteHeightVariation&) = default;
  SiteHeightVariation& operator=(SiteHeightVariation&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Site:HeightVariation scalar fields.
  // - TODO(parity): Add non-scalar parity only if future schema changes introduce relationship-like fields.
  double windSpeedProfileExponent() const;
  bool isWindSpeedProfileExponentDefaulted() const;
  bool setWindSpeedProfileExponent(double windSpeedProfileExponent);
  void resetWindSpeedProfileExponent();

  double windSpeedProfileBoundaryLayerThickness() const;
  bool isWindSpeedProfileBoundaryLayerThicknessDefaulted() const;
  bool setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness);
  void resetWindSpeedProfileBoundaryLayerThickness();

  double airTemperatureGradientCoefficient() const;
  bool isAirTemperatureGradientCoefficientDefaulted() const;
  bool setAirTemperatureGradientCoefficient(double airTemperatureGradientCoefficient);
  void resetAirTemperatureGradientCoefficient();

 protected:
  using ImplType = detail::SiteHeightVariation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SiteHeightVariation(std::shared_ptr<detail::SiteHeightVariation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
