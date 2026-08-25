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

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Zone object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonezone,AirflowNetwork:MultiZone:Zone}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
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
