/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEEXTERNALNODE_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEEXTERNALNODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneExternalNode_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneExternalNode : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneExternalNode(const Model& model);

  virtual ~AirflowNetworkMultiZoneExternalNode() override = default;
  AirflowNetworkMultiZoneExternalNode(const AirflowNetworkMultiZoneExternalNode& other) = default;
  AirflowNetworkMultiZoneExternalNode(AirflowNetworkMultiZoneExternalNode&& other) = default;
  AirflowNetworkMultiZoneExternalNode& operator=(const AirflowNetworkMultiZoneExternalNode&) = default;
  AirflowNetworkMultiZoneExternalNode& operator=(AirflowNetworkMultiZoneExternalNode&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> windAngleTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: externalNodeHeight, symmetricWindPressureCoefficientCurve, and windAngleType
  //   map directly to EnergyPlus AirflowNetwork:MultiZone:ExternalNode scalar fields.
  // - Field Mapping: Wind Pressure Coefficient Curve Name is an object-list target-link field and
  //   is intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkExternalNode writes these same scalar
  //   fields directly to the EnergyPlus object.
  // - TODO(parity): Add typed relationship APIs for curve linkage after scalar scaffold saturation.
  double externalNodeHeight() const;
  bool isExternalNodeHeightDefaulted() const;
  bool setExternalNodeHeight(double externalNodeHeight);
  void resetExternalNodeHeight();

  bool symmetricWindPressureCoefficientCurve() const;
  bool isSymmetricWindPressureCoefficientCurveDefaulted() const;
  bool setSymmetricWindPressureCoefficientCurve(bool symmetricWindPressureCoefficientCurve);
  void resetSymmetricWindPressureCoefficientCurve();

  std::string windAngleType() const;
  bool isWindAngleTypeDefaulted() const;
  bool setWindAngleType(const std::string& windAngleType);
  void resetWindAngleType();

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneExternalNode_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneExternalNode(std::shared_ptr<detail::AirflowNetworkMultiZoneExternalNode_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
