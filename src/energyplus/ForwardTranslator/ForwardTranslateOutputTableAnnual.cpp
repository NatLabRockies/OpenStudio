/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/OutputTableAnnual.hpp"

#include "../../model/Schedule.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"

#include <utilities/idd/Output_Table_Annual_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateOutputTableAnnual(model::OutputTableAnnual& modelObject) {

    if (modelObject.numberofAnnualVariableGroups() == 0) {
      return boost::none;
    }

    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::Output_Table_Annual, modelObject);

    // Filter: boost::optional<std::string>
    if (boost::optional<std::string> filter_ = modelObject.filter()) {
      idfObject.setString(Output_Table_AnnualFields::Filter, filter_.get());
    }

    // Schedule Name: Optional Object
    if (boost::optional<Schedule> schedule_ = modelObject.schedule()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(schedule_.get())) {
        idfObject.setString(Output_Table_AnnualFields::ScheduleName, wo_->nameString());
      }
    }

    for (const auto& group : modelObject.annualVariableGroups()) {
      IdfExtensibleGroup eg = idfObject.pushExtensibleGroup();
      eg.setString(Output_Table_AnnualExtensibleFields::VariableorMeterorEMSVariableorFieldName, group.variableorMeterorEMSVariableorField());
      eg.setString(Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter, group.aggregationType());
      eg.setInt(Output_Table_AnnualExtensibleFields::DigitsAfterDecimal, group.digitsAfterDecimal());
    }

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
