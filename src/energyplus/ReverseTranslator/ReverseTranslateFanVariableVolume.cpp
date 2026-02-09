/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/FanVariableVolume.hpp"

// TODO: Check the following class names against object getters and setters.
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"

#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"

#include <utilities/idd/Fan_VariableVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateFanVariableVolume(const WorkspaceObject& workspaceObject) {

    // Instantiate an object of the class to store the values,
    // but we don't return it until we know it's ok
    openstudio::model::FanVariableVolume modelObject(m_model);
    // Name
    if (boost::optional<std::string> name_ = workspaceObject.name()) {
      modelObject.setName(name_.get());
    }

    // Availability Schedule Name: Optional Object
    if (boost::optional<WorkspaceObject> wo_ = workspaceObject.getTarget(Fan_VariableVolumeFields::AvailabilityScheduleName)) {
      if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(wo_.get())) {
        if (boost::optional<Schedule> availabilitySchedule_ = mo_->optionalCast<Schedule>()) {
          modelObject.setAvailabilitySchedule(availabilitySchedule_.get());
        } else {
          LOG(Warn, workspaceObject.briefDescription() << " has a wrong type for 'Availability Schedule Name'");
        }
      }
    }
    // Fan Total Efficiency: Optional Double
    if (boost::optional<double> fanTotalEfficiency_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanTotalEfficiency)) {
      modelObject.setFanTotalEfficiency(fanTotalEfficiency_.get());
    }

    // Pressure Rise: Required Double
    if (boost::optional<double> pressureRise_ = workspaceObject.getDouble(Fan_VariableVolumeFields::PressureRise)) {
      modelObject.setPressureRise(pressureRise_.get());
    } else {
      LOG(Error, "For " << workspaceObject.briefDescription() << ", cannot find required property 'Pressure Rise'");
      return boost::none;
    }

    // Maximum Flow Rate: Optional Double
    if (boost::optional<double> maximumFlowRate_ = workspaceObject.getDouble(Fan_VariableVolumeFields::MaximumFlowRate)) {
      modelObject.setMaximumFlowRate(maximumFlowRate_.get());
    }

    // Fan Power Minimum Flow Rate Input Method: Optional String
    if (boost::optional<std::string> fanPowerMinimumFlowRateInputMethod_ =
          workspaceObject.getString(Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod)) {
      modelObject.setFanPowerMinimumFlowRateInputMethod(fanPowerMinimumFlowRateInputMethod_.get());
    }

    // Fan Power Minimum Flow Fraction: Optional Double
    if (boost::optional<double> fanPowerMinimumFlowFraction_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerMinimumFlowFraction)) {
      modelObject.setFanPowerMinimumFlowFraction(fanPowerMinimumFlowFraction_.get());
    }

    // Fan Power Minimum Air Flow Rate: Optional Double
    if (boost::optional<double> fanPowerMinimumAirFlowRate_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate)) {
      modelObject.setFanPowerMinimumAirFlowRate(fanPowerMinimumAirFlowRate_.get());
    }

    // Motor Efficiency: Optional Double
    if (boost::optional<double> motorEfficiency_ = workspaceObject.getDouble(Fan_VariableVolumeFields::MotorEfficiency)) {
      modelObject.setMotorEfficiency(motorEfficiency_.get());
    }

    // Motor In Airstream Fraction: Optional Double
    if (boost::optional<double> motorInAirstreamFraction_ = workspaceObject.getDouble(Fan_VariableVolumeFields::MotorInAirstreamFraction)) {
      modelObject.setMotorInAirstreamFraction(motorInAirstreamFraction_.get());
    }

    // Fan Power Coefficient 1: Optional Double
    if (boost::optional<double> fanPowerCoefficient1_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerCoefficient1)) {
      modelObject.setFanPowerCoefficient1(fanPowerCoefficient1_.get());
    }

    // Fan Power Coefficient 2: Optional Double
    if (boost::optional<double> fanPowerCoefficient2_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerCoefficient2)) {
      modelObject.setFanPowerCoefficient2(fanPowerCoefficient2_.get());
    }

    // Fan Power Coefficient 3: Optional Double
    if (boost::optional<double> fanPowerCoefficient3_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerCoefficient3)) {
      modelObject.setFanPowerCoefficient3(fanPowerCoefficient3_.get());
    }

    // Fan Power Coefficient 4: Optional Double
    if (boost::optional<double> fanPowerCoefficient4_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerCoefficient4)) {
      modelObject.setFanPowerCoefficient4(fanPowerCoefficient4_.get());
    }

    // Fan Power Coefficient 5: Optional Double
    if (boost::optional<double> fanPowerCoefficient5_ = workspaceObject.getDouble(Fan_VariableVolumeFields::FanPowerCoefficient5)) {
      modelObject.setFanPowerCoefficient5(fanPowerCoefficient5_.get());
    }

    // Air Inlet Node Name: Required Node

    // Air Outlet Node Name: Required Node

    // End-Use Subcategory: Optional String
    if (boost::optional<std::string> endUseSubcategory_ = workspaceObject.getString(Fan_VariableVolumeFields::EndUseSubcategory)) {
      modelObject.setEndUseSubcategory(endUseSubcategory_.get());
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
