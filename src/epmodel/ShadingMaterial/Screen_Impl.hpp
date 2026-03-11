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
      double thermalConductance() const;
      double thermalResistivity() const;
      double thermalResistance() const;

      std::string reflectedBeamTransmittanceAccountingMethod() const;
      bool isReflectedBeamTransmittanceAccountingMethodDefaulted() const;

      double diffuseSolarReflectance() const;
      double diffuseVisibleReflectance() const;

      double thermalHemisphericalEmissivity() const;
      bool isThermalHemisphericalEmissivityDefaulted() const;

      double conductivity() const;
      bool isConductivityDefaulted() const;

      double screenMaterialSpacing() const;
      double screenMaterialDiameter() const;

      double screentoGlassDistance() const;
      bool isScreentoGlassDistanceDefaulted() const;

      double topOpeningMultiplier() const;
      bool isTopOpeningMultiplierDefaulted() const;

      double bottomOpeningMultiplier() const;
      bool isBottomOpeningMultiplierDefaulted() const;

      double leftSideOpeningMultiplier() const;
      bool isLeftSideOpeningMultiplierDefaulted() const;

      double rightSideOpeningMultiplier() const;
      bool isRightSideOpeningMultiplierDefaulted() const;

      std::string angleofResolutionforScreenTransmittanceOutputMap() const;
      bool isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const;

      bool setThermalConductivity(double value);
      bool setThermalResistivity(double value);

      bool setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod);
      void resetReflectedBeamTransmittanceAccountingMethod();

      bool setDiffuseSolarReflectance(double diffuseSolarReflectance);
      bool setDiffuseVisibleReflectance(double diffuseVisibleReflectance);

      bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
      void resetThermalHemisphericalEmissivity();

      bool setConductivity(double conductivity);
      void resetConductivity();

      bool setScreenMaterialSpacing(double screenMaterialSpacing);
      bool setScreenMaterialDiameter(double screenMaterialDiameter);

      bool setScreentoGlassDistance(double screentoGlassDistance);
      void resetScreentoGlassDistance();

      bool setTopOpeningMultiplier(double topOpeningMultiplier);
      void resetTopOpeningMultiplier();

      bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
      void resetBottomOpeningMultiplier();

      bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
      void resetLeftSideOpeningMultiplier();

      bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
      void resetRightSideOpeningMultiplier();

      bool setAngleofResolutionforScreenTransmittanceOutputMap(const std::string& angleofResolutionforScreenTransmittanceOutputMap);
      void resetAngleofResolutionforScreenTransmittanceOutputMap();

      std::vector<std::string> reflectedBeamTransmittanceAccountingMethodValues() const;
      std::vector<std::string> angleofResolutionforScreenTransmittanceOutputMapValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
