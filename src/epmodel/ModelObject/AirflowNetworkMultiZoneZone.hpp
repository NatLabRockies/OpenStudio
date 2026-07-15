/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEZONE_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneZone_Impl;
  }

  class EPMODEL_API AirflowNetworkMultiZoneZone : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneZone(const Model& model);

    virtual ~AirflowNetworkMultiZoneZone() override = default;
    AirflowNetworkMultiZoneZone(const AirflowNetworkMultiZoneZone& other) = default;
    AirflowNetworkMultiZoneZone(AirflowNetworkMultiZoneZone&& other) = default;
    AirflowNetworkMultiZoneZone& operator=(const AirflowNetworkMultiZoneZone&) = default;
    AirflowNetworkMultiZoneZone& operator=(AirflowNetworkMultiZoneZone&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> ventilationControlModeValues();
    static std::vector<std::string> singleSidedWindPressureCoefficientAlgorithmValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: ventilationControlMode, minimumVentingOpenFactor,
    //   indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor,
    //   indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor,
    //   indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor,
    //   indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor,
    //   singleSidedWindPressureCoefficientAlgorithm, and facadeWidth map directly to
    //   EnergyPlus AirflowNetwork:MultiZone:Zone scalar fields.
    // - Field Mapping: Zone Name, Ventilation Control Zone Temperature Setpoint Schedule Name,
    //   Venting Availability Schedule Name, and Occupant Ventilation Control Name are
    //   relationship-like object-list fields and are intentionally excluded from scalar accessors.
    // - ForwardTranslator evidence: ForwardTranslateAirflowNetwork.cpp writes these same scalar
    //   fields directly on AirflowNetwork:MultiZone:Zone.
    // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.
    std::string ventilationControlMode() const;
    bool isVentilationControlModeDefaulted() const;
    bool setVentilationControlMode(const std::string& ventilationControlMode);
    void resetVentilationControlMode();

    double minimumVentingOpenFactor() const;
    bool isMinimumVentingOpenFactorDefaulted() const;
    bool setMinimumVentingOpenFactor(double minimumVentingOpenFactor);
    void resetMinimumVentingOpenFactor();

    double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const;
    bool isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const;
    bool setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
      double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
    void resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();

    double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const;
    bool isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const;
    bool setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
      double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
    void resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();

    double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const;
    bool isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const;
    bool setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
      double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
    void resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();

    double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const;
    bool isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const;
    bool setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
      double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
    void resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();

    std::string singleSidedWindPressureCoefficientAlgorithm() const;
    bool isSingleSidedWindPressureCoefficientAlgorithmDefaulted() const;
    bool setSingleSidedWindPressureCoefficientAlgorithm(const std::string& singleSidedWindPressureCoefficientAlgorithm);
    void resetSingleSidedWindPressureCoefficientAlgorithm();

    double facadeWidth() const;
    bool isFacadeWidthDefaulted() const;
    bool setFacadeWidth(double facadeWidth);
    void resetFacadeWidth();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneZone_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneZone(std::shared_ptr<detail::AirflowNetworkMultiZoneZone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
