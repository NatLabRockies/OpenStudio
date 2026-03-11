/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSEWELL_HPP
#define EPMODEL_WATERUSEWELL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class WaterUseWell_Impl;
}

class EPMODEL_API WaterUseWell : public ModelObject
{
 public:
  explicit WaterUseWell(const Model& model);

  virtual ~WaterUseWell() override = default;
  WaterUseWell(const WaterUseWell& other) = default;
  WaterUseWell(WaterUseWell&& other) = default;
  WaterUseWell& operator=(const WaterUseWell&) = default;
  WaterUseWell& operator=(WaterUseWell&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> waterTableDepthModeValues();

  // Schema Alignment Notes:
  // - API: Name is inherited from ModelObject while pump/well/water-table scalars expose WaterUse:Well simple fields.
  // - Field Mapping: pumpDepth, pumpRatedFlowRate, pumpRatedHead, pumpRatedPowerConsumption, pumpEfficiency, wellRecoveryRate,
  //   nominalWellStorageVolume, and waterTableDepth map directly to the EnergyPlus WaterUse_WellFields enum values.
  // - Field Mapping: waterTableDepthMode is a non-boolean choice backed by WaterUse_WellFields::WaterTableDepthMode and has a values helper.
  // - Field Mapping: Storage Tank Name and Water Table Depth Schedule Name are object-list relationships and excluded from scalar accessors per the contract.
  // - TODO(parity): Add storage tank and schedule relationship helpers after scalar saturation is complete.
  boost::optional<double> pumpDepth() const;
  bool setPumpDepth(double pumpDepth);

  boost::optional<double> pumpRatedFlowRate() const;
  bool setPumpRatedFlowRate(double pumpRatedFlowRate);

  boost::optional<double> pumpRatedHead() const;
  bool setPumpRatedHead(double pumpRatedHead);

  boost::optional<double> pumpRatedPowerConsumption() const;
  bool setPumpRatedPowerConsumption(double pumpRatedPowerConsumption);

  boost::optional<double> pumpEfficiency() const;
  bool setPumpEfficiency(double pumpEfficiency);

  boost::optional<double> wellRecoveryRate() const;
  bool setWellRecoveryRate(double wellRecoveryRate);

  boost::optional<double> nominalWellStorageVolume() const;
  bool setNominalWellStorageVolume(double nominalWellStorageVolume);

  boost::optional<std::string> waterTableDepthMode() const;
  bool setWaterTableDepthMode(const std::string& waterTableDepthMode);

  boost::optional<double> waterTableDepth() const;
  bool setWaterTableDepth(double waterTableDepth);

 protected:
  using ImplType = detail::WaterUseWell_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit WaterUseWell(std::shared_ptr<detail::WaterUseWell_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
