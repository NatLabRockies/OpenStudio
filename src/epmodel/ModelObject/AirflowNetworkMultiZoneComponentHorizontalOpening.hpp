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

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus
  //   AirflowNetwork:MultiZone:Component:HorizontalOpening fields N1/N2/N3/N4.
  // - ForwardTranslator evidence: translateAirflowNetworkHorizontalOpening writes these scalar fields directly.
  // - TODO(parity): Align with model-level semantics once deeper airflow-network parity work is scheduled.
  double airMassFlowCoefficientWhenOpeningisClosed() const;
  bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

  double airMassFlowExponentWhenOpeningisClosed() const;
  bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
  bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
  void resetAirMassFlowExponentWhenOpeningisClosed();

  double slopingPlaneAngle() const;
  bool isSlopingPlaneAngleDefaulted() const;
  bool setSlopingPlaneAngle(double slopingPlaneAngle);
  void resetSlopingPlaneAngle();

  double dischargeCoefficient() const;
  bool setDischargeCoefficient(double dischargeCoefficient);

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneComponentHorizontalOpening(
    std::shared_ptr<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
