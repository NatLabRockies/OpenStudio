/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCOOLINGTOWER_HPP
#define EPMODEL_FAULTMODELFOULINGCOOLINGTOWER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelFoulingCoolingTower_Impl;
  }

  class EPMODEL_API FaultModelFoulingCoolingTower : public ModelObject
  {
   public:
    explicit FaultModelFoulingCoolingTower(const Model& model);

    virtual ~FaultModelFoulingCoolingTower() override = default;
    FaultModelFoulingCoolingTower(const FaultModelFoulingCoolingTower& other) = default;
    FaultModelFoulingCoolingTower(FaultModelFoulingCoolingTower&& other) = default;
    FaultModelFoulingCoolingTower& operator=(const FaultModelFoulingCoolingTower&) = default;
    FaultModelFoulingCoolingTower& operator=(FaultModelFoulingCoolingTower&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> coolingTowerObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name, Severity Schedule Name, and Cooling Tower Object Name are
    //   relationship-like object-list target-link fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.

    // Field Mapping: coolingTowerObjectType maps directly to EnergyPlus FaultModel:Fouling:CoolingTower /
    //   Cooling Tower Object Type.
    std::string coolingTowerObjectType() const;
    bool setCoolingTowerObjectType(const std::string& coolingTowerObjectType);

    // Field Mapping: referenceUAReductionFactor maps directly to EnergyPlus FaultModel:Fouling:CoolingTower /
    //   Reference UA Reduction Factor.
    boost::optional<double> referenceUAReductionFactor() const;
    bool setReferenceUAReductionFactor(double referenceUAReductionFactor);
    void resetReferenceUAReductionFactor();

   protected:
    using ImplType = detail::FaultModelFoulingCoolingTower_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelFoulingCoolingTower(std::shared_ptr<detail::FaultModelFoulingCoolingTower_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
