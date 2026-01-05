/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/OutputTableMonthly.hpp"

#include "../../utilities/idf/IdfExtensibleGroup.hpp"

#include <utilities/idd/Output_Table_Monthly_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateOutputTableMonthly(model::OutputTableMonthly& modelObject) {

    if (modelObject.numberofMonthlyVariableGroups() == 0) {
      return boost::none;
    }

    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::Output_Table_Monthly, modelObject);

    // Digits After Decimal: Optional Integer, we set it in ctor
    const int digitsAfterDecimal = modelObject.digitsAfterDecimal();
    idfObject.setInt(Output_Table_MonthlyFields::DigitsAfterDecimal, digitsAfterDecimal);

    for (const auto& group : modelObject.monthlyVariableGroups()) {
      IdfExtensibleGroup eg = idfObject.pushExtensibleGroup();
      eg.setString(Output_Table_MonthlyExtensibleFields::VariableorMeterName, group.variableOrMeterName());
      eg.setString(Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter, group.aggregationType());
    }

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
