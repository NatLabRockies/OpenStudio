/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCONSTANTPRESSUREDROP_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCONSTANTPRESSUREDROP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentConstantPressureDrop_Impl;
  }

  class EPMODEL_API AirflowNetworkDistributionComponentConstantPressureDrop : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentConstantPressureDrop(const Model& model);

    virtual ~AirflowNetworkDistributionComponentConstantPressureDrop() override = default;
    AirflowNetworkDistributionComponentConstantPressureDrop(const AirflowNetworkDistributionComponentConstantPressureDrop& other) = default;
    AirflowNetworkDistributionComponentConstantPressureDrop(AirflowNetworkDistributionComponentConstantPressureDrop&& other) = default;
    AirflowNetworkDistributionComponentConstantPressureDrop& operator=(const AirflowNetworkDistributionComponentConstantPressureDrop&) = default;
    AirflowNetworkDistributionComponentConstantPressureDrop& operator=(AirflowNetworkDistributionComponentConstantPressureDrop&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: pressureDifferenceAcrosstheComponent maps directly to EnergyPlus
    //   AirflowNetwork:Distribution:Component:ConstantPressureDrop field
    //   Pressure Difference Across the Component.
    // - ForwardTranslator evidence: translateAirflowNetworkConstantPressureDrop writes
    //   PressureDifferenceAcrosstheComponent directly from modelObject.pressureDrop().
    // - TODO(parity): Align with potential model-counterpart semantics during later parity work.
    double pressureDifferenceAcrosstheComponent() const;
    bool setPressureDifferenceAcrosstheComponent(double pressureDifferenceAcrosstheComponent);

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentConstantPressureDrop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentConstantPressureDrop(
      std::shared_ptr<detail::AirflowNetworkDistributionComponentConstantPressureDrop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
