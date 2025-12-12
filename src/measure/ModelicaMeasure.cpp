/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelicaMeasure.hpp"

#include "OSArgument.hpp"
#include "OSOutput.hpp"
#include "OSRunner.hpp"

namespace openstudio {
namespace measure {

  ModelicaMeasure::ModelicaMeasure() : OSMeasure(MeasureType::ModelicaMeasure){};

  std::vector<OSArgument> ModelicaMeasure::arguments(const openstudio::model::Model& /*model*/, const openstudio::Workspace& /*workspace*/) const {
    return {};
  }

  bool ModelicaMeasure::run(openstudio::modelica::ModelicaFile& /*modelicaFile*/, openstudio::model::Model& /*model*/,
                            const openstudio::Workspace& /*workspace*/, OSRunner& runner,
                            const std::map<std::string, OSArgument>& /*user_arguments*/) const {
    runner.prepareForMeasureRun(*this);
    return true;
  }

}  // namespace measure
}  // namespace openstudio
