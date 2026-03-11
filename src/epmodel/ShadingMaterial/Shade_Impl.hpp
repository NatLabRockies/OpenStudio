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
      double thermalConductance() const;
      double thermalResistivity() const;
      double thermalResistance() const;

      double solarTransmittance() const;
      double solarReflectance() const;
      double visibleTransmittance() const;
      double visibleReflectance() const;
      double thermalHemisphericalEmissivity() const;
      double thermalTransmittance() const;
      double solarAbsorptance() const;
      double visibleAbsorptance() const;

      double thickness() const;
      double conductivity() const;

      double shadetoGlassDistance() const;
      bool isShadetoGlassDistanceDefaulted() const;

      double topOpeningMultiplier() const;
      bool isTopOpeningMultiplierDefaulted() const;

      double bottomOpeningMultiplier() const;
      bool isBottomOpeningMultiplierDefaulted() const;

      double leftSideOpeningMultiplier() const;
      bool isLeftSideOpeningMultiplierDefaulted() const;

      double rightSideOpeningMultiplier() const;
      bool isRightSideOpeningMultiplierDefaulted() const;

      double airflowPermeability() const;
      bool isAirflowPermeabilityDefaulted() const;

      bool setThermalConductivity(double value);
      bool setThermalConductance(double value);
      bool setThermalResistivity(double value);
      bool setThermalResistance(double value);

      bool setThermalTransmittance(double thermalTransmittance);
      bool setSolarTransmittance(double solarTransmittance);
      bool setSolarReflectance(double solarReflectance);
      bool setVisibleTransmittance(double visibleTransmittance);
      bool setVisibleReflectance(double visibleReflectance);
      bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
      bool setThickness(double thickness);
      bool setConductivity(double conductivity);

      bool setShadetoGlassDistance(double shadetoGlassDistance);
      void resetShadetoGlassDistance();

      bool setTopOpeningMultiplier(double topOpeningMultiplier);
      void resetTopOpeningMultiplier();

      bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
      void resetBottomOpeningMultiplier();

      bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
      void resetLeftSideOpeningMultiplier();

      bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
      void resetRightSideOpeningMultiplier();

      bool setAirflowPermeability(double airflowPermeability);
      void resetAirflowPermeability();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
