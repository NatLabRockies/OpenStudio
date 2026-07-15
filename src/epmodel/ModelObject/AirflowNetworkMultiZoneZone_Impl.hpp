/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEZONE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneZone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneZone_Impl() override = default;

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

      std::vector<std::string> ventilationControlModeValues() const;
      std::vector<std::string> singleSidedWindPressureCoefficientAlgorithmValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
