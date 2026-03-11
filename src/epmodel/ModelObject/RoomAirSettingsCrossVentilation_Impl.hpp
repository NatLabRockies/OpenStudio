/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSCROSSVENTILATION_IMPL_HPP
#define EPMODEL_ROOMAIRSETTINGSCROSSVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API RoomAirSettingsCrossVentilation_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RoomAirSettingsCrossVentilation_Impl() override = default;

  boost::optional<std::string> airflowRegionUsedforThermalComfortEvaluation() const;

  bool setAirflowRegionUsedforThermalComfortEvaluation(const std::string& airflowRegionUsedforThermalComfortEvaluation);
  void resetAirflowRegionUsedforThermalComfortEvaluation();

  std::vector<std::string> airflowRegionUsedforThermalComfortEvaluationValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
