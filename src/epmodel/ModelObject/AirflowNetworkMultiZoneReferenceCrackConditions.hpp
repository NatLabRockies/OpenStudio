/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEREFERENCECRACKCONDITIONS_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEREFERENCECRACKCONDITIONS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneReferenceCrackConditions_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:ReferenceCrackConditions object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonereferencecrackconditions,AirflowNetwork:MultiZone:ReferenceCrackConditions}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneReferenceCrackConditions : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneReferenceCrackConditions(const Model& model);

    virtual ~AirflowNetworkMultiZoneReferenceCrackConditions() override = default;
    AirflowNetworkMultiZoneReferenceCrackConditions(const AirflowNetworkMultiZoneReferenceCrackConditions& other) = default;
    AirflowNetworkMultiZoneReferenceCrackConditions(AirflowNetworkMultiZoneReferenceCrackConditions&& other) = default;
    AirflowNetworkMultiZoneReferenceCrackConditions& operator=(const AirflowNetworkMultiZoneReferenceCrackConditions&) = default;
    AirflowNetworkMultiZoneReferenceCrackConditions& operator=(AirflowNetworkMultiZoneReferenceCrackConditions&&) = default;

    static IddObjectType iddObjectType();

    double referenceTemperature() const;
    bool setReferenceTemperature(double referenceTemperature);

    double referenceBarometricPressure() const;
    bool setReferenceBarometricPressure(double referenceBarometricPressure);
    bool isReferenceBarometricPressureDefaulted() const;
    void resetReferenceBarometricPressure();

    double referenceHumidityRatio() const;
    bool setReferenceHumidityRatio(double referenceHumidityRatio);
    bool isReferenceHumidityRatioDefaulted() const;
    void resetReferenceHumidityRatio();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneReferenceCrackConditions(std::shared_ptr<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
