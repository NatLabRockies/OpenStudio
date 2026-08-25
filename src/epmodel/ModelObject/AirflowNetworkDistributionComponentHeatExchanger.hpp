/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentHeatExchanger_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:HeatExchanger object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentheatexchanger,AirflowNetwork:Distribution:Component:HeatExchanger}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentHeatExchanger : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentHeatExchanger(const Model& model);

    virtual ~AirflowNetworkDistributionComponentHeatExchanger() override = default;
    AirflowNetworkDistributionComponentHeatExchanger(const AirflowNetworkDistributionComponentHeatExchanger& other) = default;
    AirflowNetworkDistributionComponentHeatExchanger(AirflowNetworkDistributionComponentHeatExchanger&& other) = default;
    AirflowNetworkDistributionComponentHeatExchanger& operator=(const AirflowNetworkDistributionComponentHeatExchanger&) = default;
    AirflowNetworkDistributionComponentHeatExchanger& operator=(AirflowNetworkDistributionComponentHeatExchanger&&) = default;

    static IddObjectType iddObjectType();


    /** @name Air Path Length */
    //@{
    double airPathLength() const;
    bool setAirPathLength(double airPathLength);
    //@}

    /** @name Air Path Hydraulic Diameter */
    //@{
    double airPathHydraulicDiameter() const;
    bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);
    //@}

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentHeatExchanger_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentHeatExchanger(std::shared_ptr<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
