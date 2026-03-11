/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORPVWATTS_IMPL_HPP
#define EPMODEL_GENERATORPVWATTS_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorPVWatts_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorPVWatts_Impl() override = default;

  std::string pvWattsVersion() const;

  double dcSystemCapacity() const;
  bool setDCSystemCapacity(double dcSystemCapacity);

  std::string moduleType() const;
  bool isModuleTypeDefaulted() const;
  bool setModuleType(const std::string& moduleType);
  void resetModuleType();

  std::string arrayType() const;
  bool isArrayTypeDefaulted() const;
  bool setArrayType(const std::string& arrayType);
  void resetArrayType();

  double systemLosses() const;
  bool isSystemLossesDefaulted() const;
  bool setSystemLosses(double systemLosses);
  void resetSystemLosses();

  double tiltAngle() const;
  bool isTiltAngleDefaulted() const;
  bool setTiltAngle(double tiltAngle);
  void resetTiltAngle();

  double azimuthAngle() const;
  bool isAzimuthAngleDefaulted() const;
  bool setAzimuthAngle(double azimuthAngle);
  void resetAzimuthAngle();

  double groundCoverageRatio() const;
  bool isGroundCoverageRatioDefaulted() const;
  bool setGroundCoverageRatio(double groundCoverageRatio);
  void resetGroundCoverageRatio();

  std::vector<std::string> pvWattsVersionValues() const;
  std::vector<std::string> moduleTypeValues() const;
  std::vector<std::string> arrayTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
