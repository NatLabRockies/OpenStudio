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

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:ConstantPressureDrop object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentconstantpressuredrop,AirflowNetwork:Distribution:Component:ConstantPressureDrop}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
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
