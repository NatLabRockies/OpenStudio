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

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: referenceTemperature, referenceBarometricPressure, and referenceHumidityRatio
    //   map directly to EnergyPlus AirflowNetwork:MultiZone:ReferenceCrackConditions scalar fields.
    // - Field Mapping: Name remains provided by base ModelObject naming APIs.
    // - ForwardTranslator evidence: translateAirflowNetworkReferenceCrackConditions writes Name,
    //   Reference Temperature, Reference Barometric Pressure, and Reference Humidity Ratio directly.
    // - TODO(parity): Add relationship APIs only if future schema evolution introduces linked fields.
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
