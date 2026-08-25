/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTHORIZONTALOPENING_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTHORIZONTALOPENING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneComponentHorizontalOpening_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Component:HorizontalOpening object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonecomponenthorizontalopening,AirflowNetwork:MultiZone:Component:HorizontalOpening}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneComponentHorizontalOpening : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneComponentHorizontalOpening(const Model& model);

    virtual ~AirflowNetworkMultiZoneComponentHorizontalOpening() override = default;
    AirflowNetworkMultiZoneComponentHorizontalOpening(const AirflowNetworkMultiZoneComponentHorizontalOpening& other) = default;
    AirflowNetworkMultiZoneComponentHorizontalOpening(AirflowNetworkMultiZoneComponentHorizontalOpening&& other) = default;
    AirflowNetworkMultiZoneComponentHorizontalOpening& operator=(const AirflowNetworkMultiZoneComponentHorizontalOpening&) = default;
    AirflowNetworkMultiZoneComponentHorizontalOpening& operator=(AirflowNetworkMultiZoneComponentHorizontalOpening&&) = default;

    static IddObjectType iddObjectType();

    double airMassFlowCoefficientWhenOpeningisClosed() const;
    bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

    double airMassFlowExponentWhenOpeningisClosed() const;
    bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
    bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
    void resetAirMassFlowExponentWhenOpeningisClosed();

    double slopingPlaneAngle() const;
    bool setSlopingPlaneAngle(double slopingPlaneAngle);
    bool isSlopingPlaneAngleDefaulted() const;
    void resetSlopingPlaneAngle();

    double dischargeCoefficient() const;
    bool setDischargeCoefficient(double dischargeCoefficient);

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneComponentHorizontalOpening(std::shared_ptr<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
