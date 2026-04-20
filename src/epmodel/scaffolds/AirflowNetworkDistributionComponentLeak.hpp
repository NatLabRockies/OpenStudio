/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAK_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentLeak_Impl;
  }

  class EPMODEL_API AirflowNetworkDistributionComponentLeak : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentLeak(const Model& model);

    virtual ~AirflowNetworkDistributionComponentLeak() override = default;
    AirflowNetworkDistributionComponentLeak(const AirflowNetworkDistributionComponentLeak& other) = default;
    AirflowNetworkDistributionComponentLeak(AirflowNetworkDistributionComponentLeak&& other) = default;
    AirflowNetworkDistributionComponentLeak& operator=(const AirflowNetworkDistributionComponentLeak&) = default;
    AirflowNetworkDistributionComponentLeak& operator=(AirflowNetworkDistributionComponentLeak&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: airMassFlowCoefficient and airMassFlowExponent map directly to
    //   EnergyPlus AirflowNetwork:Distribution:Component:Leak scalar fields.
    // - TODO(parity): Re-evaluate naming if a future model-counterpart parity layer is introduced.
    double airMassFlowCoefficient() const;
    bool setAirMassFlowCoefficient(double airMassFlowCoefficient);

    double airMassFlowExponent() const;
    bool setAirMassFlowExponent(double airMassFlowExponent);
    bool isAirMassFlowExponentDefaulted() const;
    void resetAirMassFlowExponent();

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentLeak_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentLeak(std::shared_ptr<detail::AirflowNetworkDistributionComponentLeak_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
