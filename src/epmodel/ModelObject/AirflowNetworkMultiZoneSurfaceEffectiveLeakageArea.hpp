/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonesurfaceeffectiveleakagearea,AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(const Model& model);

    virtual ~AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea() override = default;
    AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(const AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& other) = default;
    AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&& other) = default;
    AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& operator=(const AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&) = default;
    AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& operator=(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&&) = default;

    static IddObjectType iddObjectType();

    double effectiveLeakageArea() const;
    bool setEffectiveLeakageArea(double effectiveLeakageArea);

    double dischargeCoefficient() const;
    bool isDischargeCoefficientDefaulted() const;
    bool setDischargeCoefficient(double dischargeCoefficient);
    void resetDischargeCoefficient();

    double referencePressureDifference() const;
    bool isReferencePressureDifferenceDefaulted() const;
    bool setReferencePressureDifference(double referencePressureDifference);
    void resetReferencePressureDifference();

    double airMassFlowExponent() const;
    bool isAirMassFlowExponentDefaulted() const;
    bool setAirMassFlowExponent(double airMassFlowExponent);
    void resetAirMassFlowExponent();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(
      std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
