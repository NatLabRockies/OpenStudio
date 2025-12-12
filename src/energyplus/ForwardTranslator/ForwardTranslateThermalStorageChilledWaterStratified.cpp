/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/ThermalStorageChilledWaterStratified.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/WaterHeaterSizing.hpp"

#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/core/Compare.hpp"

#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/OS_ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject>
    ForwardTranslator::translateThermalStorageChilledWaterStratified(model::ThermalStorageChilledWaterStratified& modelObject) {

    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::ThermalStorage_ChilledWater_Stratified, modelObject);

    // Trigger translation of the WaterHeater:Sizing object, if any
    bool hasWaterHeaterSizing = true;
    try {
      auto siz = modelObject.waterHeaterSizing();
      translateAndMapModelObject(siz);
    } catch (...) {
      hasWaterHeaterSizing = false;
    }

    // Tank Volume
    const double tankVolume = modelObject.tankVolume();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::TankVolume, tankVolume);

    // Tank Height
    const double tankHeight = modelObject.tankHeight();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::TankHeight, tankHeight);

    // Tank Shape
    const std::string tankShape = modelObject.tankShape();
    idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::TankShape, tankShape);

    // Tank Perimeter
    if (auto tankPerimeter_ = modelObject.tankPerimeter()) {
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter, tankPerimeter_.get());
    }

    // Setpoint Temperature Schedule Name
    if (auto setpointTemperatureSchedule_ = modelObject.setpointTemperatureSchedule()) {
      if (auto wo_ = translateAndMapModelObject(setpointTemperatureSchedule_.get())) {
        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SetpointTemperatureScheduleName, wo_->nameString());
      }
    }

    // Deadband Temperature Difference
    const double deadbandTemperatureDifference = modelObject.deadbandTemperatureDifference();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::DeadbandTemperatureDifference, deadbandTemperatureDifference);

    // Temperature Sensor Height
    if (auto temperatureSensorHeight_ = modelObject.temperatureSensorHeight()) {
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight, temperatureSensorHeight_.get());
    }

    // Minimum Temperature Limit
    if (auto minimumTemperatureLimit_ = modelObject.minimumTemperatureLimit()) {
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit, minimumTemperatureLimit_.get());
    }

    // Nominal Cooling Capacity
    if (auto nominalCoolingCapacity_ = modelObject.nominalCoolingCapacity()) {
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, nominalCoolingCapacity_.get());
    }

    // Ambient Temperature Indicator
    std::string ambientTemperatureIndicator = modelObject.ambientTemperatureIndicator();
    if (openstudio::istringEqual(ambientTemperatureIndicator, "ThermalZone")) {
      ambientTemperatureIndicator = "Zone";
    }
    idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator, ambientTemperatureIndicator);

    // Ambient Temperature Schedule Name
    if (auto ambientTemperatureSchedule_ = modelObject.ambientTemperatureSchedule()) {
      if (auto wo_ = translateAndMapModelObject(ambientTemperatureSchedule_.get())) {
        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureScheduleName, wo_->nameString());
      }
    }

    // Ambient Temperature Zone Name
    if (auto ambientTemperatureZone_ = modelObject.ambientTemperatureThermalZone()) {
      if (auto wo_ = translateAndMapModelObject(ambientTemperatureZone_.get())) {
        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureZoneName, wo_->nameString());
      }
    }

    // Ambient Temperature Outdoor Air Node Name
    if (auto ambientTemperatureOutdoorAirNodeName_ = modelObject.ambientTemperatureOutdoorAirNodeName();
        ambientTemperatureOutdoorAirNodeName_ && !ambientTemperatureOutdoorAirNodeName_->empty()) {
      idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName, *ambientTemperatureOutdoorAirNodeName_);
    } else if (istringEqual(ambientTemperatureIndicator, "Outdoors")) {
      auto name = modelObject.name().get() + " OA Node";
      IdfObject oaNodeListIdf(openstudio::IddObjectType::OutdoorAir_NodeList);
      oaNodeListIdf.setString(0, name);
      m_idfObjects.push_back(oaNodeListIdf);

      idfObject.setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName, name);
    }

    // Uniform Skin Loss Coefficient per Unit Area to Ambient Temperature
    if (auto uniformSkinLossCoefficientperUnitAreatoAmbientTemperature_ = modelObject.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature()) {
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature,
                          uniformSkinLossCoefficientperUnitAreatoAmbientTemperature_.get());
    }

    // Use Side Inlet Node Name
    if (auto mo_ = modelObject.supplyInletModelObject()) {
      if (auto node = mo_->optionalCast<Node>()) {
        translateAndMapModelObject(node.get());

        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::UseSideInletNodeName, node->name().get());
      }
    }

    // Use Side Outlet Node Name
    if (auto mo_ = modelObject.supplyOutletModelObject()) {
      if (auto node = mo_->optionalCast<Node>()) {
        translateAndMapModelObject(node.get());

        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletNodeName, node->name().get());
      }
    }

    // Use Side Heat Transfer Effectiveness
    const double useSideHeatTransferEffectiveness = modelObject.useSideHeatTransferEffectiveness();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness, useSideHeatTransferEffectiveness);

    // Use Side Availability Schedule Name
    if (auto useSideAvailabilitySchedule_ = modelObject.useSideAvailabilitySchedule()) {
      if (auto wo_ = translateAndMapModelObject(useSideAvailabilitySchedule_.get())) {
        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::UseSideAvailabilityScheduleName, wo_->nameString());
      }
    }

    // Use Side Inlet Height
    if (modelObject.isUseSideInletHeightAutocalculated()) {
      idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, "Autocalculate");
    } else {
      if (auto useSideInletHeight_ = modelObject.useSideInletHeight()) {
        idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, useSideInletHeight_.get());
      }
    }

    // Use Side Outlet Height
    const double useSideOutletHeight = modelObject.useSideOutletHeight();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletHeight, useSideOutletHeight);

    // Use Side Design Flow Rate
    if (modelObject.isUseSideDesignFlowRateAutosized()) {
      idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, "Autosize");
      if (!hasWaterHeaterSizing) {
        LOG(Error, modelObject.briefDescription() << " has its Tank Volume autosized but it does not have a WaterHeaterSizing object attached");
      }
    } else {
      if (auto useSideDesignFlowRate_ = modelObject.useSideDesignFlowRate()) {
        idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, useSideDesignFlowRate_.get());
      }
    }

    // Source Side Inlet Node Name
    if (auto mo_ = modelObject.demandInletModelObject()) {
      if (auto node = mo_->optionalCast<Node>()) {
        translateAndMapModelObject(node.get());

        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName, node->name().get());
      }
    }

    // Source Side Outlet Node Name
    if (auto mo_ = modelObject.demandOutletModelObject()) {
      if (auto node = mo_->optionalCast<Node>()) {
        translateAndMapModelObject(node.get());

        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName, node->name().get());
      }
    }

    // Source Side Heat Transfer Effectiveness
    const double sourceSideHeatTransferEffectiveness = modelObject.sourceSideHeatTransferEffectiveness();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness, sourceSideHeatTransferEffectiveness);

    // Source Side Availability Schedule Name
    if (auto sourceSideAvailabilitySchedule_ = modelObject.sourceSideAvailabilitySchedule()) {
      if (auto wo_ = translateAndMapModelObject(sourceSideAvailabilitySchedule_.get())) {
        idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideAvailabilityScheduleName, wo_->nameString());
      }
    }

    // Source Side Inlet Height
    const double sourceSideInletHeight = modelObject.sourceSideInletHeight();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletHeight, sourceSideInletHeight);

    // Source Side Outlet Height
    if (modelObject.isSourceSideOutletHeightAutocalculated()) {
      idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, "Autocalculate");
    } else {
      if (auto sourceSideOutletHeight_ = modelObject.sourceSideOutletHeight()) {
        idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, sourceSideOutletHeight_.get());
      }
    }

    // Source Side Design Flow Rate
    if (modelObject.isSourceSideDesignFlowRateAutosized()) {
      idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, "Autosize");
      if (!hasWaterHeaterSizing) {
        LOG(Error, modelObject.briefDescription() << " has its Tank Volume autosized but it does not have a WaterHeaterSizing object attached");
      }
    } else {
      if (auto sourceSideDesignFlowRate_ = modelObject.sourceSideDesignFlowRate()) {
        idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, sourceSideDesignFlowRate_.get());
      }
    }

    // Tank Recovery Time
    const double tankRecoveryTime = modelObject.tankRecoveryTime();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime, tankRecoveryTime);

    // Inlet Mode
    const std::string inletMode = modelObject.inletMode();
    idfObject.setString(ThermalStorage_ChilledWater_StratifiedFields::InletMode, inletMode);

    // Number of Nodes
    const int numberofNodes = modelObject.numberofNodes();
    idfObject.setInt(ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes, numberofNodes);

    // Additional Destratification Conductivity
    const double additionalDestratificationConductivity = modelObject.additionalDestratificationConductivity();
    idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::AdditionalDestratificationConductivity, additionalDestratificationConductivity);

    // Node 1-10 Additional Loss Coefficient
    // Avoid a warning by only setting up to number of nodes
    for (unsigned i = 0; i < static_cast<unsigned>(numberofNodes); ++i) {
      const double os_value =
        modelObject.getDouble(OS_ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient + i, true).value_or(0.0);
      idfObject.setDouble(ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient + i, os_value);
    }

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
