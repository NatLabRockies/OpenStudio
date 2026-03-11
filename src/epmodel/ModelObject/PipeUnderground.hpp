/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEUNDERGROUND_HPP
#define EPMODEL_PIPEUNDERGROUND_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipeUnderground_Impl;
}

class EPMODEL_API PipeUnderground : public ModelObject
{
 public:
  explicit PipeUnderground(const Model& model);

  virtual ~PipeUnderground() override = default;
  PipeUnderground(const PipeUnderground& other) = default;
  PipeUnderground(PipeUnderground&& other) = default;
  PipeUnderground& operator=(const PipeUnderground&) = default;
  PipeUnderground& operator=(PipeUnderground&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> sunExposureValues();
  static std::vector<std::string> undisturbedGroundTemperatureModelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: sunExposure, pipeInsideDiameter, pipeLength, soilMaterialName, and
  //   undisturbedGroundTemperatureModelType map directly to E+ Pipe:Underground scalar fields.
  // - Field Mapping: Construction Name, Fluid Inlet/Outlet Node Name, and Undisturbed Ground
  //   Temperature Model Name are relationship-like link fields and are excluded from scalar APIs.
  // - TODO(parity): Add typed relationship/link APIs after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::PipeUnderground_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipeUnderground(std::shared_ptr<detail::PipeUnderground_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
