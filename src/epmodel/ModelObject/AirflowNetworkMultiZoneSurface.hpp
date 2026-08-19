/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneSurface_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Surface object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonesurface,AirflowNetwork:MultiZone:Surface}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneSurface : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneSurface(const Model& model);

    virtual ~AirflowNetworkMultiZoneSurface() override = default;
    AirflowNetworkMultiZoneSurface(const AirflowNetworkMultiZoneSurface& other) = default;
    AirflowNetworkMultiZoneSurface(AirflowNetworkMultiZoneSurface&& other) = default;
    AirflowNetworkMultiZoneSurface& operator=(const AirflowNetworkMultiZoneSurface&) = default;
    AirflowNetworkMultiZoneSurface& operator=(AirflowNetworkMultiZoneSurface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> ventilationControlModeValues();
    static std::vector<std::string> equivalentRectangleMethodValues();

    double windowDoorOpeningFactororCrackFactor() const;
    bool isWindowDoorOpeningFactororCrackFactorDefaulted() const;
    bool setWindowDoorOpeningFactororCrackFactor(double windowDoorOpeningFactororCrackFactor);
    void resetWindowDoorOpeningFactororCrackFactor();

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

    std::string equivalentRectangleMethod() const;
    bool isEquivalentRectangleMethodDefaulted() const;
    bool setEquivalentRectangleMethod(const std::string& equivalentRectangleMethod);
    void resetEquivalentRectangleMethod();

    double equivalentRectangleAspectRatio() const;
    bool isEquivalentRectangleAspectRatioDefaulted() const;
    bool setEquivalentRectangleAspectRatio(double equivalentRectangleAspectRatio);
    void resetEquivalentRectangleAspectRatio();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneSurface(std::shared_ptr<detail::AirflowNetworkMultiZoneSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
