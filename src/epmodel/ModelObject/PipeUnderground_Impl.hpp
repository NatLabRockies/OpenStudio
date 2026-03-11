/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEUNDERGROUND_IMPL_HPP
#define EPMODEL_PIPEUNDERGROUND_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API PipeUnderground_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~PipeUnderground_Impl() override = default;

  std::string sunExposure() const;
  boost::optional<double> pipeInsideDiameter() const;
  boost::optional<double> pipeLength() const;
  std::string soilMaterialName() const;
  std::string undisturbedGroundTemperatureModelType() const;

  bool isPipeInsideDiameterDefaulted() const;
  bool isPipeLengthDefaulted() const;

  bool setSunExposure(const std::string& sunExposure);
  bool setPipeInsideDiameter(double pipeInsideDiameter);
  bool setPipeLength(double pipeLength);
  bool setSoilMaterialName(const std::string& soilMaterialName);
  bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);

  void resetPipeInsideDiameter();
  void resetPipeLength();

  std::vector<std::string> sunExposureValues() const;
  std::vector<std::string> undisturbedGroundTemperatureModelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
