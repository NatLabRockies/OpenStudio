/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SHADE_IMPL_HPP
#define EPMODEL_SHADE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Shade_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Shade_Impl() override = default;

      double thermalConductivity() const;
      bool setThermalConductivity(double value);

      double thermalConductance() const;
      bool setThermalConductance(double value);

      double thermalResistivity() const;
      bool setThermalResistivity(double value);

      double thermalResistance() const;
      bool setThermalResistance(double value);

      double solarTransmittance() const;
      bool setSolarTransmittance(double solarTransmittance);

      double solarReflectance() const;
      bool setSolarReflectance(double solarReflectance);

      double visibleTransmittance() const;
      bool setVisibleTransmittance(double visibleTransmittance);

      double visibleReflectance() const;
      bool setVisibleReflectance(double visibleReflectance);

      double thermalHemisphericalEmissivity() const;
      bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);

      double thermalTransmittance() const;
      bool setThermalTransmittance(double thermalTransmittance);

      double solarAbsorptance() const;
      double visibleAbsorptance() const;

      double thickness() const;
      bool setThickness(double thickness);

      double conductivity() const;
      bool setConductivity(double conductivity);

      double shadetoGlassDistance() const;
      bool isShadetoGlassDistanceDefaulted() const;
      bool setShadetoGlassDistance(double shadetoGlassDistance);
      void resetShadetoGlassDistance();

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

      double airflowPermeability() const;
      bool isAirflowPermeabilityDefaulted() const;
      bool setAirflowPermeability(double airflowPermeability);
      void resetAirflowPermeability();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
