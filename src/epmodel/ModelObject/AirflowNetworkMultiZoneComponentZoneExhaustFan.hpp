/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Component:ZoneExhaustFan object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonecomponentzoneexhaustfan,AirflowNetwork:MultiZone:Component:ZoneExhaustFan}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneComponentZoneExhaustFan : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneComponentZoneExhaustFan(const Model& model);

    virtual ~AirflowNetworkMultiZoneComponentZoneExhaustFan() override = default;
    AirflowNetworkMultiZoneComponentZoneExhaustFan(const AirflowNetworkMultiZoneComponentZoneExhaustFan& other) = default;
    AirflowNetworkMultiZoneComponentZoneExhaustFan(AirflowNetworkMultiZoneComponentZoneExhaustFan&& other) = default;
    AirflowNetworkMultiZoneComponentZoneExhaustFan& operator=(const AirflowNetworkMultiZoneComponentZoneExhaustFan&) = default;
    AirflowNetworkMultiZoneComponentZoneExhaustFan& operator=(AirflowNetworkMultiZoneComponentZoneExhaustFan&&) = default;

    static IddObjectType iddObjectType();

    double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions() const;
    bool setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
      double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions);

    double airMassFlowExponentWhentheZoneExhaustFanisOff() const;
    bool isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted() const;
    bool setAirMassFlowExponentWhentheZoneExhaustFanisOff(double airMassFlowExponentWhentheZoneExhaustFanisOff);
    void resetAirMassFlowExponentWhentheZoneExhaustFanisOff();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneComponentZoneExhaustFan(std::shared_ptr<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
