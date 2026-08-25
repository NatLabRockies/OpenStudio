/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentOutdoorAirFlow_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:OutdoorAirFlow object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflowNetworkdistributioncomponentoutdoorairflow,AirflowNetwork:Distribution:Component:OutdoorAirFlow}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentOutdoorAirFlow : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentOutdoorAirFlow(const Model& model);

    virtual ~AirflowNetworkDistributionComponentOutdoorAirFlow() override = default;
    AirflowNetworkDistributionComponentOutdoorAirFlow(const AirflowNetworkDistributionComponentOutdoorAirFlow& other) = default;
    AirflowNetworkDistributionComponentOutdoorAirFlow(AirflowNetworkDistributionComponentOutdoorAirFlow&& other) = default;
    AirflowNetworkDistributionComponentOutdoorAirFlow& operator=(const AirflowNetworkDistributionComponentOutdoorAirFlow&) = default;
    AirflowNetworkDistributionComponentOutdoorAirFlow& operator=(AirflowNetworkDistributionComponentOutdoorAirFlow&&) = default;

    static IddObjectType iddObjectType();

    double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const;
    bool setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);

    double airMassFlowExponentWhenNoOutdoorAirFlow() const;
    bool setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow);
    bool isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const;
    void resetAirMassFlowExponentWhenNoOutdoorAirFlow();

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentOutdoorAirFlow(std::shared_ptr<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
