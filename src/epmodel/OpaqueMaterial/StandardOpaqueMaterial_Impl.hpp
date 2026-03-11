/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDOPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_STANDARDOPAQUEMATERIAL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API StandardOpaqueMaterial_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~StandardOpaqueMaterial_Impl() override = default;

  double thermalConductivity() const;
  double thermalConductance() const;
  double thermalResistivity() const;
  double thermalResistance() const;

  boost::optional<double> thermalReflectance() const;
  boost::optional<double> solarReflectance() const;
  boost::optional<double> visibleReflectance() const;

  std::string roughness() const;
  double thickness() const;
  double conductivity() const;
  double density() const;
  double specificHeat() const;

  double thermalAbsorptance() const;
  bool isThermalAbsorptanceDefaulted() const;

  double solarAbsorptance() const;
  bool isSolarAbsorptanceDefaulted() const;

  double visibleAbsorptance() const;
  bool isVisibleAbsorptanceDefaulted() const;

  bool setThermalConductivity(double value);
  bool setThermalConductance(double value);
  bool setThermalResistivity(double value);
  bool setThermalResistance(double value);

  bool setThermalAbsorptance(boost::optional<double> value);
  bool setThermalReflectance(boost::optional<double> value);

  bool setSolarAbsorptance(boost::optional<double> value);
  bool setSolarReflectance(boost::optional<double> value);

  bool setVisibleAbsorptance(boost::optional<double> value);
  bool setVisibleReflectance(boost::optional<double> value);

  bool setRoughness(const std::string& roughness);
  bool setThickness(double thickness);
  bool setConductivity(double conductivity);
  bool setDensity(double density);
  bool setSpecificHeat(double specificHeat);

  bool setThermalAbsorptance(double thermalAbsorptance);
  void resetThermalAbsorptance();

  bool setSolarAbsorptance(double solarAbsorptance);
  void resetSolarAbsorptance();

  bool setVisibleAbsorptance(double visibleAbsorptance);
  void resetVisibleAbsorptance();

  boost::optional<double> heatCapacity() const;

  std::vector<std::string> roughnessValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
