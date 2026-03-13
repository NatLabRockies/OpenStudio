/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGBOILER_HPP
#define EPMODEL_FAULTMODELFOULINGBOILER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelFoulingBoiler_Impl;
  }

  class EPMODEL_API FaultModelFoulingBoiler : public ModelObject
  {
   public:
    explicit FaultModelFoulingBoiler(const Model& model);

    virtual ~FaultModelFoulingBoiler() override = default;
    FaultModelFoulingBoiler(const FaultModelFoulingBoiler& other) = default;
    FaultModelFoulingBoiler(FaultModelFoulingBoiler&& other) = default;
    FaultModelFoulingBoiler& operator=(const FaultModelFoulingBoiler&) = default;
    FaultModelFoulingBoiler& operator=(FaultModelFoulingBoiler&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> boilerObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: boilerObjectType maps directly to EnergyPlus FaultModel:Fouling:Boiler / Boiler Object Type.
    // - Field Mapping: foulingFactor maps directly to EnergyPlus FaultModel:Fouling:Boiler / Fouling Factor.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name, Severity Schedule Name, and Boiler Object Name are relationship-like
    //   object-list/reference target-link fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.

    /** Boiler Object Type */
    std::string boilerObjectType() const;
    bool setBoilerObjectType(const std::string& boilerObjectType);

    /** Fouling Factor */
    double foulingFactor() const;
    bool setFoulingFactor(double foulingFactor);
    bool isFoulingFactorDefaulted() const;
    void resetFoulingFactor();

   protected:
    using ImplType = detail::FaultModelFoulingBoiler_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelFoulingBoiler(std::shared_ptr<detail::FaultModelFoulingBoiler_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
