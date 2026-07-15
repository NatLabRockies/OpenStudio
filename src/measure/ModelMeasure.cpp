/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelMeasure.hpp"

#include "OSArgument.hpp"
#include "OSOutput.hpp"
#include "OSRunner.hpp"

namespace openstudio {
namespace measure {

  ModelMeasure::ModelMeasure() : OSMeasure(MeasureType::ModelMeasure){};

  std::vector<OSArgument> ModelMeasure::arguments(const openstudio::epmodel::Model& /*model*/) const {
    return {};
  }

  std::vector<OSOutput> ModelMeasure::outputs() const {
    return {};
  }

  bool ModelMeasure::run(openstudio::epmodel::Model& /*model*/, OSRunner& runner, const std::map<std::string, OSArgument>& /*user_arguments*/) const {
    runner.prepareForMeasureRun(*this);
    return true;
  }

}  // namespace measure
}  // namespace openstudio
