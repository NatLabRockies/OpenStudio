/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/OutputControlResilienceSummaries.hpp"
#include "../../model/OutputControlResilienceSummaries_Impl.hpp"

#include <utilities/idd/OutputControl_ResilienceSummaries_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateOutputControlResilienceSummaries(const WorkspaceObject& workspaceObject) {
    boost::optional<ModelObject> result;

    if (boost::optional<std::string> heatIndexAlgorithm_ =
          workspaceObject.getString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, false, true)) {
      // This is a Unique ModelObject
      auto modelObject = m_model.getUniqueModelObject<OutputControlResilienceSummaries>();
      modelObject.setHeatIndexAlgorithm(*heatIndexAlgorithm_);
      result = modelObject;
    }

    return result;
  }

}  // end namespace energyplus
}  // end namespace openstudio
