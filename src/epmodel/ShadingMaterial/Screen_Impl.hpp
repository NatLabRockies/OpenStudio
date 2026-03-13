/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCREEN_IMPL_HPP
#define EPMODEL_SCREEN_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Screen_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Screen_Impl() override = default;

      double thermalConductivity() const;
      bool setThermalConductivity(double value);

      double thermalConductance() const;

      double thermalResistivity() const;
      bool setThermalResistivity(double value);

      double thermalResistance() const;

      std::string reflectedBeamTransmittanceAccountingMethod() const;
      bool isReflectedBeamTransmittanceAccountingMethodDefaulted() const;
      bool setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod);
      void resetReflectedBeamTransmittanceAccountingMethod();

      double diffuseSolarReflectance() const;
      bool setDiffuseSolarReflectance(double diffuseSolarReflectance);

      double diffuseVisibleReflectance() const;
      bool setDiffuseVisibleReflectance(double diffuseVisibleReflectance);

      double thermalHemisphericalEmissivity() const;
      bool isThermalHemisphericalEmissivityDefaulted() const;
      bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
      void resetThermalHemisphericalEmissivity();

      double conductivity() const;
      bool isConductivityDefaulted() const;
      bool setConductivity(double conductivity);
      void resetConductivity();

      double screenMaterialSpacing() const;
      bool setScreenMaterialSpacing(double screenMaterialSpacing);

      double screenMaterialDiameter() const;
      bool setScreenMaterialDiameter(double screenMaterialDiameter);

      double screentoGlassDistance() const;
      bool isScreentoGlassDistanceDefaulted() const;
      bool setScreentoGlassDistance(double screentoGlassDistance);
      void resetScreentoGlassDistance();

      double topOpeningMultiplier() const;
      bool isTopOpeningMultiplierDefaulted() const;
      bool setTopOpeningMultiplier(double topOpeningMultiplier);
      void resetTopOpeningMultiplier();

      double bottomOpeningMultiplier() const;
      bool isBottomOpeningMultiplierDefaulted() const;
      bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
      void resetBottomOpeningMultiplier();

      double leftSideOpeningMultiplier() const;
      bool isLeftSideOpeningMultiplierDefaulted() const;
      bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
      void resetLeftSideOpeningMultiplier();

      double rightSideOpeningMultiplier() const;
      bool isRightSideOpeningMultiplierDefaulted() const;
      bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
      void resetRightSideOpeningMultiplier();

      std::string angleofResolutionforScreenTransmittanceOutputMap() const;
      bool isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const;
      bool setAngleofResolutionforScreenTransmittanceOutputMap(const std::string& angleofResolutionforScreenTransmittanceOutputMap);
      void resetAngleofResolutionforScreenTransmittanceOutputMap();

      std::vector<std::string> reflectedBeamTransmittanceAccountingMethodValues() const;
      std::vector<std::string> angleofResolutionforScreenTransmittanceOutputMapValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
