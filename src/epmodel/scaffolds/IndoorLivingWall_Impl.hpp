/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INDOORLIVINGWALL_IMPL_HPP
#define EPMODEL_INDOORLIVINGWALL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API IndoorLivingWall_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~IndoorLivingWall_Impl() override = default;

      std::vector<std::string> evapotranspirationCalculationMethodValues() const;
      std::vector<std::string> lightingMethodValues() const;

      std::string evapotranspirationCalculationMethod() const;
      bool setEvapotranspirationCalculationMethod(const std::string& evapotranspirationCalculationMethod);
      bool isEvapotranspirationCalculationMethodDefaulted() const;
      void resetEvapotranspirationCalculationMethod();

      boost::optional<std::string> lightingMethod() const;
      bool setLightingMethod(const std::string& lightingMethod);
      void resetLightingMethod();

      boost::optional<std::string> daylightingControlName() const;
      bool setDaylightingControlName(const std::string& daylightingControlName);
      void resetDaylightingControlName();

      boost::optional<double> totalLeafArea() const;
      bool setTotalLeafArea(double totalLeafArea);
      void resetTotalLeafArea();

      boost::optional<double> lEDNominalIntensity() const;
      bool setLEDNominalIntensity(double lEDNominalIntensity);
      void resetLEDNominalIntensity();

      boost::optional<double> lEDNominalPower() const;
      bool setLEDNominalPower(double lEDNominalPower);
      void resetLEDNominalPower();

      double radiantFractionofLEDLights() const;
      bool setRadiantFractionofLEDLights(double radiantFractionofLEDLights);
      bool isRadiantFractionofLEDLightsDefaulted() const;
      void resetRadiantFractionofLEDLights();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
