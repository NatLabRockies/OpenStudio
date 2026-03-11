/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MasslessOpaqueMaterial_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MasslessOpaqueMaterial_Impl() override = default;

  std::string roughness() const;
  double thermalResistance() const;

  boost::optional<double> thermalAbsorptance() const;
  bool isThermalAbsorptanceDefaulted() const;

  boost::optional<double> solarAbsorptance() const;
  bool isSolarAbsorptanceDefaulted() const;

  boost::optional<double> visibleAbsorptance() const;
  bool isVisibleAbsorptanceDefaulted() const;

  bool setRoughness(const std::string& roughness);
  bool setThermalResistance(double thermalResistance);

  bool setThermalAbsorptance(double thermalAbsorptance);
  void resetThermalAbsorptance();

  bool setSolarAbsorptance(double solarAbsorptance);
  void resetSolarAbsorptance();

  bool setVisibleAbsorptance(double visibleAbsorptance);
  void resetVisibleAbsorptance();

  std::vector<std::string> roughnessValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
