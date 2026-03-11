/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERSURFACE_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERSURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatExchangerSurface_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatExchangerSurface_Impl() override = default;

  boost::optional<double> hydronicTubingInsideDiameter() const;
  boost::optional<int> numberofTubingCircuits() const;
  boost::optional<double> hydronicTubeSpacing() const;
  boost::optional<double> surfaceLength() const;
  boost::optional<double> surfaceWidth() const;
  std::string lowerSurfaceEnvironment() const;
  bool isLowerSurfaceEnvironmentDefaulted() const;

  bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
  bool setNumberofTubingCircuits(int numberofTubingCircuits);
  bool setHydronicTubeSpacing(double hydronicTubeSpacing);
  bool setSurfaceLength(double surfaceLength);
  bool setSurfaceWidth(double surfaceWidth);
  bool setLowerSurfaceEnvironment(const std::string& lowerSurfaceEnvironment);

  void resetHydronicTubingInsideDiameter();
  void resetNumberofTubingCircuits();
  void resetHydronicTubeSpacing();
  void resetSurfaceLength();
  void resetSurfaceWidth();
  void resetLowerSurfaceEnvironment();

  std::vector<std::string> lowerSurfaceEnvironmentValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
