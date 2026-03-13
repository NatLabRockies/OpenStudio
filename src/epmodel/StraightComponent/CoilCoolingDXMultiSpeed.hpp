/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXMULTISPEED_HPP
#define EPMODEL_COILCOOLINGDXMULTISPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilCoolingDXMultiSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXMultiSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXMultiSpeed(const Model& model);

  virtual ~CoilCoolingDXMultiSpeed() override = default;
  CoilCoolingDXMultiSpeed(const CoilCoolingDXMultiSpeed& other) = default;
  CoilCoolingDXMultiSpeed(CoilCoolingDXMultiSpeed&& other) = default;
  CoilCoolingDXMultiSpeed& operator=(const CoilCoolingDXMultiSpeed&) = default;
  CoilCoolingDXMultiSpeed& operator=(CoilCoolingDXMultiSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> fuelTypeValues();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilCoolingDXMultiSpeed scalar accessor names/signatures.
  // - Field Mapping: APIs below map directly to EnergyPlus Coil:Cooling:DX:MultiSpeed scalar fields.
  // - Field Mapping: relationship-like fields (schedules, nodes, curves, tank links, extensible stage links) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXMultiSpeed.cpp writes these fields directly.
  // - TODO(parity): Add relationship and stage/extensible APIs in a follow-up without changing preserved scalar signatures.
  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  bool applyPartLoadFractiontoSpeedsGreaterthan1() const;
  bool setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1);

  bool applyLatentDegradationtoSpeedsGreaterthan1() const;
  bool isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted() const;
  bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);
  void resetApplyLatentDegradationtoSpeedsGreaterthan1();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

 protected:
  using ImplType = detail::CoilCoolingDXMultiSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXMultiSpeed(std::shared_ptr<detail::CoilCoolingDXMultiSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
