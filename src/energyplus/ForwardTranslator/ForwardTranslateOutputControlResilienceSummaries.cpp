/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/OutputControlResilienceSummaries.hpp"

#include <utilities/idd/OutputControl_ResilienceSummaries_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateOutputControlResilienceSummaries(model::OutputControlResilienceSummaries& modelObject) {

    IdfObject idfObject = createAndRegisterIdfObject(openstudio::IddObjectType::OutputControl_ResilienceSummaries, modelObject);

    idfObject.setString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, modelObject.heatIndexAlgorithm());

    return idfObject;
  }

}  // end namespace energyplus
}  // end namespace openstudio
