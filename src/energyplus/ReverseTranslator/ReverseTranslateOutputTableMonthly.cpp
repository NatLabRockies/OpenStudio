/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/OutputTableMonthly.hpp"

#include "../../utilities/idf/IdfExtensibleGroup.hpp"

#include <utilities/idd/Output_Table_Monthly_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateOutputTableMonthly(const WorkspaceObject& workspaceObject) {

    openstudio::model::OutputTableMonthly modelObject(m_model);

    // Name
    modelObject.setName(workspaceObject.nameString());

    // Digits After Decimal: Optional Integer
    if (boost::optional<int> digitsAfterDecimal_ = workspaceObject.getInt(Output_Table_MonthlyFields::DigitsAfterDecimal)) {
      modelObject.setDigitsAfterDecimal(digitsAfterDecimal_.get());
    }

    // Extensible groups
    for (const IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
      auto variableorMeterName = eg.getString(Output_Table_MonthlyExtensibleFields::VariableorMeterName).get();
      if (variableorMeterName.empty()) {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) has an empty Variable or Meter Name field, skipping group");
        continue;
      }
      auto aggregationType = eg.getString(Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter).get();
      if (aggregationType.empty()) {
        LOG(Warn,
            "Extensible group " << eg.groupIndex() << "(0-indexed) has an empty Aggregation Type for VariableorMeter field, assuming SumOrAverage.");
        aggregationType = "SumOrAverage";
      } else if (!OutputTableMonthly::isAggregationTypeValid(aggregationType)) {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) has an Aggregation Type = '" << aggregationType
                                      << "' that is invalid. Skipping group.");
        continue;
      }

      if (!modelObject.addMonthlyVariableGroup(variableorMeterName, aggregationType)) {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) is already present, not adding it twice");
      }
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
