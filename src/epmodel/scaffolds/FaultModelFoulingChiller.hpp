/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCHILLER_HPP
#define EPMODEL_FAULTMODELFOULINGCHILLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelFoulingChiller_Impl;
  }

  class EPMODEL_API FaultModelFoulingChiller : public ModelObject
  {
   public:
    explicit FaultModelFoulingChiller(const Model& model);

    virtual ~FaultModelFoulingChiller() override = default;
    FaultModelFoulingChiller(const FaultModelFoulingChiller& other) = default;
    FaultModelFoulingChiller(FaultModelFoulingChiller&& other) = default;
    FaultModelFoulingChiller& operator=(const FaultModelFoulingChiller&) = default;
    FaultModelFoulingChiller& operator=(FaultModelFoulingChiller&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> chillerObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: chillerObjectType maps directly to EnergyPlus FaultModel:Fouling:Chiller / Chiller Object Type.
    // - Field Mapping: foulingFactor maps directly to EnergyPlus FaultModel:Fouling:Chiller / Fouling Factor.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name, Severity Schedule Name, and Chiller Object Name are relationship-like
    //   object-list/reference target-link fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    std::string chillerObjectType() const;
    bool setChillerObjectType(const std::string& chillerObjectType);

    double foulingFactor() const;
    bool setFoulingFactor(double foulingFactor);
    bool isFoulingFactorDefaulted() const;
    void resetFoulingFactor();

   protected:
    using ImplType = detail::FaultModelFoulingChiller_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelFoulingChiller(std::shared_ptr<detail::FaultModelFoulingChiller_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
