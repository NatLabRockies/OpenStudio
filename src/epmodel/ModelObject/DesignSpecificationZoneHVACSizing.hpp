/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONZONEHVACSIZING_HPP
#define EPMODEL_DESIGNSPECIFICATIONZONEHVACSIZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DesignSpecificationZoneHVACSizing_Impl;
}

class EPMODEL_API DesignSpecificationZoneHVACSizing : public ModelObject
{
 public:
  explicit DesignSpecificationZoneHVACSizing(const Model& model);

  virtual ~DesignSpecificationZoneHVACSizing() override = default;
  DesignSpecificationZoneHVACSizing(const DesignSpecificationZoneHVACSizing& other) = default;
  DesignSpecificationZoneHVACSizing(DesignSpecificationZoneHVACSizing&& other) = default;
  DesignSpecificationZoneHVACSizing& operator=(const DesignSpecificationZoneHVACSizing&) = default;
  DesignSpecificationZoneHVACSizing& operator=(DesignSpecificationZoneHVACSizing&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> coolingSupplyAirFlowRateMethodValues();
  static std::vector<std::string> noLoadSupplyAirFlowRateMethodValues();
  static std::vector<std::string> heatingSupplyAirFlowRateMethodValues();
  static std::vector<std::string> coolingDesignCapacityMethodValues();
  static std::vector<std::string> heatingDesignCapacityMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type keeps IDD-derived class and accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus DesignSpecification:ZoneHVAC:Sizing fields.
  // - Field Mapping: Name is a reference field and remains available through base ModelObject naming API.
  // - TODO(parity): Revisit naming if a model-counterpart parity layer is introduced.
  std::string coolingSupplyAirFlowRateMethod() const;
  bool isCoolingSupplyAirFlowRateMethodDefaulted() const;
  bool setCoolingSupplyAirFlowRateMethod(const std::string& coolingSupplyAirFlowRateMethod);
  void resetCoolingSupplyAirFlowRateMethod();

  boost::optional<double> coolingSupplyAirFlowRate() const;
  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  void resetCoolingSupplyAirFlowRate();
  void autosizeCoolingSupplyAirFlowRate();

  boost::optional<double> coolingSupplyAirFlowRatePerFloorArea() const;
  bool setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea);
  void resetCoolingSupplyAirFlowRatePerFloorArea();

  boost::optional<double> coolingFractionofAutosizedCoolingSupplyAirFlowRate() const;
  bool setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate);
  void resetCoolingFractionofAutosizedCoolingSupplyAirFlowRate();

  boost::optional<double> coolingSupplyAirFlowRatePerUnitCoolingCapacity() const;
  bool setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity);
  void resetCoolingSupplyAirFlowRatePerUnitCoolingCapacity();

  std::string noLoadSupplyAirFlowRateMethod() const;
  bool isNoLoadSupplyAirFlowRateMethodDefaulted() const;
  bool setNoLoadSupplyAirFlowRateMethod(const std::string& noLoadSupplyAirFlowRateMethod);
  void resetNoLoadSupplyAirFlowRateMethod();

  boost::optional<double> noLoadSupplyAirFlowRate() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
  void resetNoLoadSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();

  boost::optional<double> noLoadSupplyAirFlowRatePerFloorArea() const;
  bool setNoLoadSupplyAirFlowRatePerFloorArea(double noLoadSupplyAirFlowRatePerFloorArea);
  void resetNoLoadSupplyAirFlowRatePerFloorArea();

  boost::optional<double> noLoadFractionofCoolingSupplyAirFlowRate() const;
  bool setNoLoadFractionofCoolingSupplyAirFlowRate(double noLoadFractionofCoolingSupplyAirFlowRate);
  void resetNoLoadFractionofCoolingSupplyAirFlowRate();

  boost::optional<double> noLoadFractionofHeatingSupplyAirFlowRate() const;
  bool setNoLoadFractionofHeatingSupplyAirFlowRate(double noLoadFractionofHeatingSupplyAirFlowRate);
  void resetNoLoadFractionofHeatingSupplyAirFlowRate();

  std::string heatingSupplyAirFlowRateMethod() const;
  bool isHeatingSupplyAirFlowRateMethodDefaulted() const;
  bool setHeatingSupplyAirFlowRateMethod(const std::string& heatingSupplyAirFlowRateMethod);
  void resetHeatingSupplyAirFlowRateMethod();

  boost::optional<double> heatingSupplyAirFlowRate() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  void resetHeatingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();

  boost::optional<double> heatingSupplyAirFlowRatePerFloorArea() const;
  bool setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea);
  void resetHeatingSupplyAirFlowRatePerFloorArea();

  boost::optional<double> heatingFractionofHeatingSupplyAirFlowRate() const;
  bool setHeatingFractionofHeatingSupplyAirFlowRate(double heatingFractionofHeatingSupplyAirFlowRate);
  void resetHeatingFractionofHeatingSupplyAirFlowRate();

  boost::optional<double> heatingSupplyAirFlowRatePerUnitHeatingCapacity() const;
  bool setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity);
  void resetHeatingSupplyAirFlowRatePerUnitHeatingCapacity();

  std::string coolingDesignCapacityMethod() const;
  bool isCoolingDesignCapacityMethodDefaulted() const;
  bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
  void resetCoolingDesignCapacityMethod();

  boost::optional<double> coolingDesignCapacity() const;
  bool isCoolingDesignCapacityAutosized() const;
  bool setCoolingDesignCapacity(double coolingDesignCapacity);
  void resetCoolingDesignCapacity();
  void autosizeCoolingDesignCapacity();

  boost::optional<double> coolingDesignCapacityPerFloorArea() const;
  bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
  void resetCoolingDesignCapacityPerFloorArea();

  boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
  bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);
  void resetFractionofAutosizedCoolingDesignCapacity();

  std::string heatingDesignCapacityMethod() const;
  bool isHeatingDesignCapacityMethodDefaulted() const;
  bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
  void resetHeatingDesignCapacityMethod();

  boost::optional<double> heatingDesignCapacity() const;
  bool isHeatingDesignCapacityAutosized() const;
  bool setHeatingDesignCapacity(double heatingDesignCapacity);
  void resetHeatingDesignCapacity();
  void autosizeHeatingDesignCapacity();

  boost::optional<double> heatingDesignCapacityPerFloorArea() const;
  bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
  void resetHeatingDesignCapacityPerFloorArea();

  boost::optional<double> fractionofAutosizedHeatingDesignCapacity() const;
  bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
  void resetFractionofAutosizedHeatingDesignCapacity();

 protected:
  using ImplType = detail::DesignSpecificationZoneHVACSizing_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DesignSpecificationZoneHVACSizing(std::shared_ptr<detail::DesignSpecificationZoneHVACSizing_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
