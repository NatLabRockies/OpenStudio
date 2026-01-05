/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/OutputTableAnnual.hpp"

#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"

#include "../../utilities/idf/IdfExtensibleGroup.hpp"

#include <utilities/idd/Output_Table_Annual_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateOutputTableAnnual(const WorkspaceObject& workspaceObject) {

    openstudio::model::OutputTableAnnual modelObject(m_model);
    modelObject.setName(workspaceObject.nameString());

    // Filter: Optional String
    if (boost::optional<std::string> filter_ = workspaceObject.getString(Output_Table_AnnualFields::Filter)) {
      modelObject.setFilter(filter_.get());
    }

    // Schedule Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(Output_Table_AnnualFields::ScheduleName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> schedule_ = mo_->optionalCast<Schedule>()) {
          modelObject.setSchedule(schedule_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Schedule Name'");
        }
      }
    }

    // Extensible groups
    for (const IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
      auto variableorMeterorEMSVariableorField = eg.getString(Output_Table_AnnualExtensibleFields::VariableorMeterorEMSVariableorFieldName).get();
      if (variableorMeterorEMSVariableorField.empty()) {
        LOG(Warn, "Extensible group " << eg.groupIndex()
                                      << "(0-indexed) has an empty Variable or Meter or EMS Variable or Field Name field, skipping group");
        continue;
      }
      auto aggregationType = eg.getString(Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter).get();
      if (aggregationType.empty()) {
        LOG(Warn,
            "Extensible group " << eg.groupIndex() << "(0-indexed) has an empty Aggregation Type for VariableorMeter field, assuming SumOrAverage.");
        aggregationType = "SumOrAverage";
      } else if (!OutputTableAnnual::isAggregationTypeValid(aggregationType)) {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) has an Aggregation Type = '" << aggregationType
                                      << "' that is invalid. Skipping group.");
        continue;
      }
      const int num_digits = eg.getInt(Output_Table_AnnualExtensibleFields::DigitsAfterDecimal).value_or(2);

      modelObject.addAnnualVariableGroup(variableorMeterorEMSVariableorField, aggregationType, num_digits);
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
