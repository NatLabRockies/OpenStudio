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

      double thermalConductivity() const override;
      bool setThermalConductivity(double value) override;

      double thermalConductance() const override;
      bool setThermalConductance(double value) override;

      double thermalResistivity() const override;
      bool setThermalResistivity(double value) override;

      double thermalResistance() const override;
      bool setThermalResistance(double value) override;

      boost::optional<double> thermalReflectance() const override;
      bool setThermalReflectance(boost::optional<double> value) override;

      boost::optional<double> solarReflectance() const override;
      bool setSolarReflectance(boost::optional<double> value) override;

      boost::optional<double> visibleReflectance() const override;
      bool setVisibleReflectance(boost::optional<double> value) override;

      std::string roughness() const;
      bool setRoughness(const std::string& roughness);
      std::vector<std::string> roughnessValues() const;

      double thickness() const override;
      bool setThickness(double thickness) override;

      double conductivity() const;
      bool setConductivity(double conductivity);

      double density() const;
      bool setDensity(double density);

      double specificHeat() const;
      bool setSpecificHeat(double specificHeat);

      double thermalAbsorptance() const override;
      bool isThermalAbsorptanceDefaulted() const;
      bool setThermalAbsorptance(boost::optional<double> value);
      bool setThermalAbsorptance(double thermalAbsorptance) override;
      void resetThermalAbsorptance();

      double solarAbsorptance() const override;
      bool isSolarAbsorptanceDefaulted() const;
      bool setSolarAbsorptance(boost::optional<double> value) override;
      bool setSolarAbsorptance(double solarAbsorptance);
      void resetSolarAbsorptance();

      double visibleAbsorptance() const override;
      bool isVisibleAbsorptanceDefaulted() const;
      bool setVisibleAbsorptance(boost::optional<double> value) override;
      bool setVisibleAbsorptance(double visibleAbsorptance);
      void resetVisibleAbsorptance();

      boost::optional<double> heatCapacity() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
