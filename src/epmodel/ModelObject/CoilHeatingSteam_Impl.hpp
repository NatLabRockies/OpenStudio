/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGSTEAM_IMPL_HPP
#define EPMODEL_COILHEATINGSTEAM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilHeatingSteam_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilHeatingSteam_Impl() override = default;

  boost::optional<double> maximumSteamFlowRate() const;
  bool isMaximumSteamFlowRateAutosized() const;
  bool setMaximumSteamFlowRate(double maximumSteamFlowRate);
  void resetMaximumSteamFlowRate();
  void autosizeMaximumSteamFlowRate();

  boost::optional<double> degreeofSubCooling() const;
  bool setDegreeofSubCooling(double degreeofSubCooling);
  void resetDegreeofSubCooling();

  double degreeofLoopSubCooling() const;
  bool isDegreeofLoopSubCoolingDefaulted() const;
  bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
  void resetDegreeofLoopSubCooling();

  boost::optional<std::string> coilControlType() const;
  bool setCoilControlType(const std::string& coilControlType);
  void resetCoilControlType();

  std::vector<std::string> coilControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
