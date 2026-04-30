/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ReportingMeasure.hpp"

#include "OSArgument.hpp"
#include "OSOutput.hpp"
#include "OSRunner.hpp"

#include <vector>

namespace openstudio {
namespace measure {

  ReportingMeasure::ReportingMeasure() : OSMeasure(MeasureType::ReportingMeasure){};

  std::vector<OSArgument> ReportingMeasure::arguments(const openstudio::epmodel::Model& /*model*/) const {
    return {};
  }

  std::vector<OSOutput> ReportingMeasure::outputs() const {
    return {};
  }

  bool ReportingMeasure::run(OSRunner& runner, const std::map<std::string, OSArgument>& /*user_arguments*/) const {
    runner.prepareForMeasureRun(*this);
    return true;
  }

  bool ReportingMeasure::modelOutputRequests(openstudio::epmodel::Model& /*model*/, OSRunner& /*runner*/,
                                             const std::map<std::string, OSArgument>& /*user_arguments*/) const {
    return true;
  }

  std::vector<IdfObject> ReportingMeasure::energyPlusOutputRequests(OSRunner& /*runner*/,
                                                                    const std::map<std::string, OSArgument>& /*user_arguments*/) const {
    return {};
  }

}  // namespace measure
}  // namespace openstudio
