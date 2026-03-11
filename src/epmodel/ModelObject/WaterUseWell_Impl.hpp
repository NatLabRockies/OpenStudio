/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSEWELL_IMPL_HPP
#define EPMODEL_WATERUSEWELL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API WaterUseWell_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~WaterUseWell_Impl() override = default;

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
  std::vector<std::string> waterTableDepthModeValues() const;

  boost::optional<double> waterTableDepth() const;
  bool setWaterTableDepth(double waterTableDepth);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
