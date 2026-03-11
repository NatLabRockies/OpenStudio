/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGAIRFILTER_HPP
#define EPMODEL_FAULTMODELFOULINGAIRFILTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelFoulingAirFilter_Impl;
}

class EPMODEL_API FaultModelFoulingAirFilter : public ModelObject
{
 public:
  explicit FaultModelFoulingAirFilter(const Model& model);

  virtual ~FaultModelFoulingAirFilter() override = default;
  FaultModelFoulingAirFilter(const FaultModelFoulingAirFilter& other) = default;
  FaultModelFoulingAirFilter(FaultModelFoulingAirFilter&& other) = default;
  FaultModelFoulingAirFilter& operator=(const FaultModelFoulingAirFilter&) = default;
  FaultModelFoulingAirFilter& operator=(FaultModelFoulingAirFilter&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fanObjectTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: fanObjectType maps directly to EnergyPlus FaultModel:Fouling:AirFilter / Fan Object Type.
  // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
  // - Field Mapping: Fan Name, Availability Schedule Name, Pressure Fraction Schedule Name, and Fan Curve Name are
  //   relationship-like object-list target-link fields and intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  std::string fanObjectType() const;
  bool setFanObjectType(const std::string& fanObjectType);

 protected:
  using ImplType = detail::FaultModelFoulingAirFilter_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelFoulingAirFilter(std::shared_ptr<detail::FaultModelFoulingAirFilter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
