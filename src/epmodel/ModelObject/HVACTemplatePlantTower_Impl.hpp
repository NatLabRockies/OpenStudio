/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWER_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplatePlantTower_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplatePlantTower_Impl() override = default;

  std::string towerType() const;
  boost::optional<double> highSpeedNominalCapacity() const;
  boost::optional<double> highSpeedFanPower() const;
  boost::optional<double> lowSpeedNominalCapacity() const;
  boost::optional<double> lowSpeedFanPower() const;
  boost::optional<double> freeConvectionCapacity() const;
  boost::optional<std::string> priority() const;
  double sizingFactor() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isHighSpeedNominalCapacityDefaulted() const;
  bool isHighSpeedNominalCapacityAutosized() const;
  bool isHighSpeedFanPowerDefaulted() const;
  bool isHighSpeedFanPowerAutosized() const;
  bool isLowSpeedNominalCapacityDefaulted() const;
  bool isLowSpeedNominalCapacityAutosized() const;
  bool isLowSpeedFanPowerDefaulted() const;
  bool isLowSpeedFanPowerAutosized() const;
  bool isFreeConvectionCapacityDefaulted() const;
  bool isFreeConvectionCapacityAutosized() const;
  bool isSizingFactorDefaulted() const;

  bool setTowerType(const std::string& towerType);
  bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);
  bool setHighSpeedFanPower(double highSpeedFanPower);
  bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
  bool setLowSpeedFanPower(double lowSpeedFanPower);
  bool setFreeConvectionCapacity(double freeConvectionCapacity);
  bool setPriority(const std::string& priority);
  bool setSizingFactor(double sizingFactor);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetHighSpeedNominalCapacity();
  void autosizeHighSpeedNominalCapacity();
  void resetHighSpeedFanPower();
  void autosizeHighSpeedFanPower();
  void resetLowSpeedNominalCapacity();
  void autosizeLowSpeedNominalCapacity();
  void resetLowSpeedFanPower();
  void autosizeLowSpeedFanPower();
  void resetFreeConvectionCapacity();
  void autosizeFreeConvectionCapacity();
  void resetPriority();
  void resetSizingFactor();
  void resetTemplatePlantLoopType();

  std::vector<std::string> towerTypeValues() const;
  std::vector<std::string> templatePlantLoopTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
