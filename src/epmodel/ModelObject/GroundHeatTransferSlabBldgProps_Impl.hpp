/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABBLDGPROPS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABBLDGPROPS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabBldgProps_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabBldgProps_Impl() override = default;

  double iyrsNumberofyearstoiterate() const;
  boost::optional<double> shapeSlabshape() const;
  boost::optional<double> hbldgBuildingheight() const;
  double tin1JanuaryIndoorAverageTemperatureSetpoint() const;
  double tin2FebruaryIndoorAverageTemperatureSetpoint() const;
  double tin3MarchIndoorAverageTemperatureSetpoint() const;
  double tin4AprilIndoorAverageTemperatureSetpoint() const;
  double tin5MayIndoorAverageTemperatureSetpoint() const;
  double tin6JuneIndoorAverageTemperatureSetpoint() const;
  double tin7JulyIndoorAverageTemperatureSetpoint() const;
  double tin8AugustIndoorAverageTemperatureSetpoint() const;
  double tin9SeptemberIndoorAverageTemperatureSetpoint() const;
  double tin10OctoberIndoorAverageTemperatureSetpoint() const;
  double tin11NovemberIndoorAverageTemperatureSetpoint() const;
  double tin12DecemberIndoorAverageTemperatureSetpoint() const;
  double tinAmpDailyIndoorsinewavevariationamplitude() const;
  double convTolConvergenceTolerance() const;

  bool isIyrsNumberofyearstoiterateDefaulted() const;
  bool isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin2FebruaryIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin3MarchIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin4AprilIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin5MayIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin6JuneIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin7JulyIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin8AugustIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin9SeptemberIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin10OctoberIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin11NovemberIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTin12DecemberIndoorAverageTemperatureSetpointDefaulted() const;
  bool isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted() const;
  bool isConvTolConvergenceToleranceDefaulted() const;

  bool setIyrsNumberofyearstoiterate(double iyrsNumberofyearstoiterate);
  bool setShapeSlabshape(double shapeSlabshape);
  bool setHbldgBuildingheight(double hbldgBuildingheight);
  bool setTin1JanuaryIndoorAverageTemperatureSetpoint(double tin1JanuaryIndoorAverageTemperatureSetpoint);
  bool setTin2FebruaryIndoorAverageTemperatureSetpoint(double tin2FebruaryIndoorAverageTemperatureSetpoint);
  bool setTin3MarchIndoorAverageTemperatureSetpoint(double tin3MarchIndoorAverageTemperatureSetpoint);
  bool setTin4AprilIndoorAverageTemperatureSetpoint(double tin4AprilIndoorAverageTemperatureSetpoint);
  bool setTin5MayIndoorAverageTemperatureSetpoint(double tin5MayIndoorAverageTemperatureSetpoint);
  bool setTin6JuneIndoorAverageTemperatureSetpoint(double tin6JuneIndoorAverageTemperatureSetpoint);
  bool setTin7JulyIndoorAverageTemperatureSetpoint(double tin7JulyIndoorAverageTemperatureSetpoint);
  bool setTin8AugustIndoorAverageTemperatureSetpoint(double tin8AugustIndoorAverageTemperatureSetpoint);
  bool setTin9SeptemberIndoorAverageTemperatureSetpoint(double tin9SeptemberIndoorAverageTemperatureSetpoint);
  bool setTin10OctoberIndoorAverageTemperatureSetpoint(double tin10OctoberIndoorAverageTemperatureSetpoint);
  bool setTin11NovemberIndoorAverageTemperatureSetpoint(double tin11NovemberIndoorAverageTemperatureSetpoint);
  bool setTin12DecemberIndoorAverageTemperatureSetpoint(double tin12DecemberIndoorAverageTemperatureSetpoint);
  bool setTinAmpDailyIndoorsinewavevariationamplitude(double tinAmpDailyIndoorsinewavevariationamplitude);
  bool setConvTolConvergenceTolerance(double convTolConvergenceTolerance);

  void resetIyrsNumberofyearstoiterate();
  void resetShapeSlabshape();
  void resetHbldgBuildingheight();
  void resetTin1JanuaryIndoorAverageTemperatureSetpoint();
  void resetTin2FebruaryIndoorAverageTemperatureSetpoint();
  void resetTin3MarchIndoorAverageTemperatureSetpoint();
  void resetTin4AprilIndoorAverageTemperatureSetpoint();
  void resetTin5MayIndoorAverageTemperatureSetpoint();
  void resetTin6JuneIndoorAverageTemperatureSetpoint();
  void resetTin7JulyIndoorAverageTemperatureSetpoint();
  void resetTin8AugustIndoorAverageTemperatureSetpoint();
  void resetTin9SeptemberIndoorAverageTemperatureSetpoint();
  void resetTin10OctoberIndoorAverageTemperatureSetpoint();
  void resetTin11NovemberIndoorAverageTemperatureSetpoint();
  void resetTin12DecemberIndoorAverageTemperatureSetpoint();
  void resetTinAmpDailyIndoorsinewavevariationamplitude();
  void resetConvTolConvergenceTolerance();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
