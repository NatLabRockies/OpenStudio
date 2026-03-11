/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWER_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantTower_Impl;
}

class EPMODEL_API HVACTemplatePlantTower : public ModelObject
{
 public:
  explicit HVACTemplatePlantTower(const Model& model);

  virtual ~HVACTemplatePlantTower() override = default;
  HVACTemplatePlantTower(const HVACTemplatePlantTower& other) = default;
  HVACTemplatePlantTower(HVACTemplatePlantTower&& other) = default;
  HVACTemplatePlantTower& operator=(const HVACTemplatePlantTower&) = default;
  HVACTemplatePlantTower& operator=(HVACTemplatePlantTower&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> towerTypeValues();
  static std::vector<std::string> templatePlantLoopTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:Tower non-name scalar fields.
  // - Field Mapping: No object-list/reference/node fields are exposed in this scalar scaffold.
  // - TODO(parity): Add object-reference linkage behavior in a later parity pass.
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

 protected:
  using ImplType = detail::HVACTemplatePlantTower_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantTower(std::shared_ptr<detail::HVACTemplatePlantTower_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
