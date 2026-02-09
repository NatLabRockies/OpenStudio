/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/CoilCoolingWater.hpp"

#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"

#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"

// #include "../../model/WaterStorageTank.hpp"
#include "utilities/core/Compare.hpp"

#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateCoilCoolingWater(const WorkspaceObject& workspaceObject) {

    openstudio::model::CoilCoolingWater modelObject(m_model);

    // Name
    if (boost::optional<std::string> name_ = workspaceObject.name()) {
      modelObject.setName(name_.get());
    }

    // Availability Schedule Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(Coil_Cooling_WaterFields::AvailabilityScheduleName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> availabilitySchedule_ = mo_->optionalCast<Schedule>()) {
          modelObject.setAvailabilitySchedule(availabilitySchedule_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Availability Schedule Name'");
        }
      }
    }
    // Design Water Flow Rate: Optional Double, autosizable, defaults autosize
    if (boost::optional<double> designWaterFlowRate_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignWaterFlowRate)) {
      modelObject.setDesignWaterFlowRate(designWaterFlowRate_.get());
    }

    // Design Air Flow Rate: Optional Double
    if (boost::optional<double> designAirFlowRate_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignAirFlowRate)) {
      modelObject.setDesignAirFlowRate(designAirFlowRate_.get());
    }

    // Design Inlet Water Temperature: Optional Double
    if (boost::optional<double> designInletWaterTemperature_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignInletWaterTemperature)) {
      modelObject.setDesignInletWaterTemperature(designInletWaterTemperature_.get());
    }

    // Design Inlet Air Temperature: Optional Double
    if (boost::optional<double> designInletAirTemperature_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignInletAirTemperature)) {
      modelObject.setDesignInletAirTemperature(designInletAirTemperature_.get());
    }

    // Design Outlet Air Temperature: Optional Double
    if (boost::optional<double> designOutletAirTemperature_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignOutletAirTemperature)) {
      modelObject.setDesignOutletAirTemperature(designOutletAirTemperature_.get());
    }

    // Design Inlet Air Humidity Ratio: Optional Double
    if (boost::optional<double> designInletAirHumidityRatio_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignInletAirHumidityRatio)) {
      modelObject.setDesignInletAirHumidityRatio(designInletAirHumidityRatio_.get());
    }

    // Design Outlet Air Humidity Ratio: Optional Double
    if (boost::optional<double> designOutletAirHumidityRatio_ = workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio)) {
      modelObject.setDesignOutletAirHumidityRatio(designOutletAirHumidityRatio_.get());
    }

    // Water Inlet Node Name: Required Node
    if (workspaceObject.isEmpty(Coil_Cooling_WaterFields::WaterInletNodeName)) {
      LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot find required object 'Water Inlet Node Name'");
      return boost::none;
    }
    // Water Outlet Node Name: Required Node
    if (workspaceObject.isEmpty(Coil_Cooling_WaterFields::WaterOutletNodeName)) {
      LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot find required object 'Water Outlet Node Name'");
      return boost::none;
    }
    // Air Inlet Node Name: Required Node
    if (workspaceObject.isEmpty(Coil_Cooling_WaterFields::AirInletNodeName)) {
      LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot find required object 'Air Inlet Node Name'");
      return boost::none;
    }
    // Air Outlet Node Name: Required Node
    if (workspaceObject.isEmpty(Coil_Cooling_WaterFields::AirOutletNodeName)) {
      LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot find required object 'Air Outlet Node Name'");
      return boost::none;
    }
    // Type of Analysis: Optional String
    if (boost::optional<std::string> typeofAnalysis_ = workspaceObject.getString(Coil_Cooling_WaterFields::TypeofAnalysis)) {
      if (openstudio::istringEqual(typeofAnalysis_.get(), "SimpleAnalysis")) {
        modelObject.setTypeOfAnalysis(typeofAnalysis_.get());
      } else if (openstudio::istringEqual(typeofAnalysis_.get(), "DetailedAnalysis")) {
        modelObject.setTypeOfAnalysis(typeofAnalysis_.get());
      } else {
        LOG(Warn, workspaceObject.briefDescription() << " has an unsupported 'Type of Analysis': " << typeofAnalysis_.get());
      }
    }

    // Heat Exchanger Configuration: Optional String
    if (boost::optional<std::string> heatExchangerConfiguration_ = workspaceObject.getString(Coil_Cooling_WaterFields::HeatExchangerConfiguration)) {
      modelObject.setHeatExchangerConfiguration(heatExchangerConfiguration_.get());
    }

    // Condensate Collection Water Storage Tank Name: Optional Object
    if (!workspaceObject.isEmpty(Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName)) {
      LOG(Warn, workspaceObject.briefDescription() << " has a 'Condensate Collection Water Storage Tank Name' field, but it is not supported in OpenStudio. Ignoring.");
    }

    // Design Water Temperature Difference: Optional Double
    if (boost::optional<double> designWaterTemperatureDifference_ =
          workspaceObject.getDouble(Coil_Cooling_WaterFields::DesignWaterTemperatureDifference)) {
     LOG(Warn, workspaceObject.briefDescription() << " has a 'Design Water Temperature Difference' field, but it is not supported in OpenStudio. Ignoring.");
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
