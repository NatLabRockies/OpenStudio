/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGEVAPORATIVECOOLER_HPP
#define EPMODEL_FAULTMODELFOULINGEVAPORATIVECOOLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelFoulingEvaporativeCooler_Impl;
  }

  class EPMODEL_API FaultModelFoulingEvaporativeCooler : public ModelObject
  {
   public:
    explicit FaultModelFoulingEvaporativeCooler(const Model& model);

    virtual ~FaultModelFoulingEvaporativeCooler() override = default;
    FaultModelFoulingEvaporativeCooler(const FaultModelFoulingEvaporativeCooler& other) = default;
    FaultModelFoulingEvaporativeCooler(FaultModelFoulingEvaporativeCooler&& other) = default;
    FaultModelFoulingEvaporativeCooler& operator=(const FaultModelFoulingEvaporativeCooler&) = default;
    FaultModelFoulingEvaporativeCooler& operator=(FaultModelFoulingEvaporativeCooler&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> evaporativeCoolerObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: evaporativeCoolerObjectType maps directly to EnergyPlus FaultModel:Fouling:EvaporativeCooler /
    //   Evaporative Cooler Object Type.
    // - Field Mapping: foulingFactor maps directly to EnergyPlus FaultModel:Fouling:EvaporativeCooler / Fouling Factor.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name, Severity Schedule Name, and Evaporative Cooler Object Name are
    //   relationship-like object-list/reference target-link fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    std::string evaporativeCoolerObjectType() const;
    bool setEvaporativeCoolerObjectType(const std::string& evaporativeCoolerObjectType);

    double foulingFactor() const;
    bool setFoulingFactor(double foulingFactor);
    bool isFoulingFactorDefaulted() const;
    void resetFoulingFactor();

   protected:
    using ImplType = detail::FaultModelFoulingEvaporativeCooler_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelFoulingEvaporativeCooler(std::shared_ptr<detail::FaultModelFoulingEvaporativeCooler_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
