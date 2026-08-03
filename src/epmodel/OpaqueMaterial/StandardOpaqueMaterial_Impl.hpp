/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDOPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_STANDARDOPAQUEMATERIAL_IMPL_HPP

#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API StandardOpaqueMaterial_Impl : public OpaqueMaterial_Impl
    {
     public:
      using OpaqueMaterial_Impl::OpaqueMaterial_Impl;
      virtual ~StandardOpaqueMaterial_Impl() override = default;

      double thermalConductivity() const;
      bool setThermalConductivity(double value);

      double thermalConductance() const;
      bool setThermalConductance(double value);

      double thermalResistivity() const;
      bool setThermalResistivity(double value);

      double thermalResistance() const override;
      bool setThermalResistance(double value) override;

      boost::optional<double> thermalReflectance() const;
      bool setThermalReflectance(boost::optional<double> value);

      boost::optional<double> solarReflectance() const;
      bool setSolarReflectance(boost::optional<double> value);

      boost::optional<double> visibleReflectance() const;
      bool setVisibleReflectance(boost::optional<double> value);

      std::string roughness() const;
      bool setRoughness(const std::string& roughness);
      std::vector<std::string> roughnessValues() const;

      double thickness() const;
      bool setThickness(double thickness);

      double conductivity() const;
      bool setConductivity(double conductivity);

      double density() const;
      bool setDensity(double density);

      double specificHeat() const;
      bool setSpecificHeat(double specificHeat);

      double thermalAbsorptance() const;
      bool isThermalAbsorptanceDefaulted() const;
      bool setThermalAbsorptance(boost::optional<double> value);
      bool setThermalAbsorptance(double thermalAbsorptance);
      void resetThermalAbsorptance();

      double solarAbsorptance() const;
      bool isSolarAbsorptanceDefaulted() const;
      bool setSolarAbsorptance(boost::optional<double> value);
      bool setSolarAbsorptance(double solarAbsorptance);
      void resetSolarAbsorptance();

      double visibleAbsorptance() const;
      bool isVisibleAbsorptanceDefaulted() const;
      bool setVisibleAbsorptance(boost::optional<double> value);
      bool setVisibleAbsorptance(double visibleAbsorptance);
      void resetVisibleAbsorptance();

      boost::optional<double> heatCapacity() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
