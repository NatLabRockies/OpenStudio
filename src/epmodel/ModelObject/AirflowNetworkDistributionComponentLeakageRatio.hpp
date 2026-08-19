/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAKAGERATIO_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAKAGERATIO_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentLeakageRatio_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:LeakageRatio object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentleakageratio,AirflowNetwork:Distribution:Component:LeakageRatio}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentLeakageRatio : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentLeakageRatio(const Model& model);

    virtual ~AirflowNetworkDistributionComponentLeakageRatio() override = default;
    AirflowNetworkDistributionComponentLeakageRatio(const AirflowNetworkDistributionComponentLeakageRatio& other) = default;
    AirflowNetworkDistributionComponentLeakageRatio(AirflowNetworkDistributionComponentLeakageRatio&& other) = default;
    AirflowNetworkDistributionComponentLeakageRatio& operator=(const AirflowNetworkDistributionComponentLeakageRatio&) = default;
    AirflowNetworkDistributionComponentLeakageRatio& operator=(AirflowNetworkDistributionComponentLeakageRatio&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> effectiveLeakageRatio() const;
    bool setEffectiveLeakageRatio(double effectiveLeakageRatio);
    void resetEffectiveLeakageRatio();

    // Maximum flow rate accessors
    double maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);

    // Reference pressure difference accessors
    double referencePressureDifference() const;
    bool setReferencePressureDifference(double referencePressureDifference);

    // Air mass flow exponent accessors
    double airMassFlowExponent() const;
    bool isAirMassFlowExponentDefaulted() const;
    bool setAirMassFlowExponent(double airMassFlowExponent);
    void resetAirMassFlowExponent();

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentLeakageRatio_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentLeakageRatio(std::shared_ptr<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
