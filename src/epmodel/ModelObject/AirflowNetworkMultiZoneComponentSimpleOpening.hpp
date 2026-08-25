/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTSIMPLEOPENING_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTSIMPLEOPENING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneComponentSimpleOpening_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Component:SimpleOpening object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonecomponentsimpleopening,AirflowNetwork:MultiZone:Component:SimpleOpening}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneComponentSimpleOpening : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneComponentSimpleOpening(const Model& model);

    virtual ~AirflowNetworkMultiZoneComponentSimpleOpening() override = default;
    AirflowNetworkMultiZoneComponentSimpleOpening(const AirflowNetworkMultiZoneComponentSimpleOpening& other) = default;
    AirflowNetworkMultiZoneComponentSimpleOpening(AirflowNetworkMultiZoneComponentSimpleOpening&& other) = default;
    AirflowNetworkMultiZoneComponentSimpleOpening& operator=(const AirflowNetworkMultiZoneComponentSimpleOpening&) = default;
    AirflowNetworkMultiZoneComponentSimpleOpening& operator=(AirflowNetworkMultiZoneComponentSimpleOpening&&) = default;

    static IddObjectType iddObjectType();

    double airMassFlowCoefficientWhenOpeningisClosed() const;
    bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

    double airMassFlowExponentWhenOpeningisClosed() const;
    bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
    bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
    void resetAirMassFlowExponentWhenOpeningisClosed();

    double minimumDensityDifferenceforTwoWayFlow() const;
    bool setMinimumDensityDifferenceforTwoWayFlow(double minimumDensityDifferenceforTwoWayFlow);

    double dischargeCoefficient() const;
    bool setDischargeCoefficient(double dischargeCoefficient);

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneComponentSimpleOpening(std::shared_ptr<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
