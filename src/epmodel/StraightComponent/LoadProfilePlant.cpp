/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LoadProfilePlant.hpp"
#include "LoadProfilePlant_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleCompact.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/LoadProfile_Plant_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <vector>

namespace openstudio {
namespace epmodel {

  LoadProfilePlant::LoadProfilePlant(const Model& model) : StraightComponent(LoadProfilePlant::iddObjectType(), model) {
    ScheduleCompact loadSchedule(model);
    std::vector<std::string> fields(1);

    fields[0] = "Through: 12/31";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());

    fields[0] = "For: AllDays";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());

    fields[0] = "Until: 04:00";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());
    fields[0].clear();
    auto valueGroup = loadSchedule.pushExtensibleGroup(fields);
    OS_ASSERT(!valueGroup.empty());
    OS_ASSERT(valueGroup.setDouble(0u, 8000.0));

    fields[0] = "Until: 08:00";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());
    fields[0].clear();
    valueGroup = loadSchedule.pushExtensibleGroup(fields);
    OS_ASSERT(!valueGroup.empty());
    OS_ASSERT(valueGroup.setDouble(0u, 6000.0));

    fields[0] = "Until: 09:00";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());
    fields[0].clear();
    valueGroup = loadSchedule.pushExtensibleGroup(fields);
    OS_ASSERT(!valueGroup.empty());
    OS_ASSERT(valueGroup.setDouble(0u, 0.0));

    fields[0] = "Until: 12:00";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());
    fields[0].clear();
    valueGroup = loadSchedule.pushExtensibleGroup(fields);
    OS_ASSERT(!valueGroup.empty());
    OS_ASSERT(valueGroup.setDouble(0u, 6000.0));

    fields[0] = "Until: 24:00";
    OS_ASSERT(!loadSchedule.pushExtensibleGroup(fields).empty());
    fields[0].clear();
    valueGroup = loadSchedule.pushExtensibleGroup(fields);
    OS_ASSERT(!valueGroup.empty());
    OS_ASSERT(valueGroup.setDouble(0u, 10000.0));

    auto flowRateFractionSchedule = model.alwaysOnDiscreteSchedule();

    OS_ASSERT(setLoadSchedule(loadSchedule));
    OS_ASSERT(setPeakFlowRate(0.002));
    OS_ASSERT(setFlowRateFractionSchedule(flowRateFractionSchedule));
    OS_ASSERT(setPlantLoopFluidType("Water"));
    OS_ASSERT(setDegreeofSubCooling(5.0));
    OS_ASSERT(setDegreeofLoopSubCooling(20.0));
  }

  LoadProfilePlant::LoadProfilePlant(const Model& model, Schedule& loadSchedule, Schedule& flowRateFractionSchedule)
    : StraightComponent(LoadProfilePlant::iddObjectType(), model) {
    OS_ASSERT(setLoadSchedule(loadSchedule));
    OS_ASSERT(setPeakFlowRate(0.0));
    OS_ASSERT(setFlowRateFractionSchedule(flowRateFractionSchedule));
    OS_ASSERT(setPlantLoopFluidType("Water"));
    OS_ASSERT(setDegreeofSubCooling(5.0));
    OS_ASSERT(setDegreeofLoopSubCooling(20.0));
  }

  LoadProfilePlant::LoadProfilePlant(std::shared_ptr<detail::LoadProfilePlant_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType LoadProfilePlant::iddObjectType() {
    return IddObjectType::LoadProfile_Plant;
  }

  std::vector<std::string> LoadProfilePlant::plantLoopFluidTypeValues() {
    return {"Water", "Steam"};
  }

  Schedule LoadProfilePlant::loadSchedule() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->loadSchedule();
  }

  bool LoadProfilePlant::setLoadSchedule(Schedule& schedule) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setLoadSchedule(schedule);
  }

  double LoadProfilePlant::peakFlowRate() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->peakFlowRate();
  }

  bool LoadProfilePlant::setPeakFlowRate(double peakFlowRate) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setPeakFlowRate(peakFlowRate);
  }

  Schedule LoadProfilePlant::flowRateFractionSchedule() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->flowRateFractionSchedule();
  }

  bool LoadProfilePlant::setFlowRateFractionSchedule(Schedule& schedule) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setFlowRateFractionSchedule(schedule);
  }

  std::string LoadProfilePlant::plantLoopFluidType() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->plantLoopFluidType();
  }

  bool LoadProfilePlant::setPlantLoopFluidType(const std::string& plantLoopFluidType) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setPlantLoopFluidType(plantLoopFluidType);
  }

  bool LoadProfilePlant::isPlantLoopFluidTypeDefaulted() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->isPlantLoopFluidTypeDefaulted();
  }

  void LoadProfilePlant::resetPlantLoopFluidType() {
    getImpl<detail::LoadProfilePlant_Impl>()->resetPlantLoopFluidType();
  }

  double LoadProfilePlant::degreeofSubCooling() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->degreeofSubCooling();
  }

  bool LoadProfilePlant::setDegreeofSubCooling(double degreeofSubCooling) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setDegreeofSubCooling(degreeofSubCooling);
  }

  bool LoadProfilePlant::isDegreeofSubCoolingDefaulted() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->isDegreeofSubCoolingDefaulted();
  }

  void LoadProfilePlant::resetDegreeofSubCooling() {
    getImpl<detail::LoadProfilePlant_Impl>()->resetDegreeofSubCooling();
  }

  double LoadProfilePlant::degreeofLoopSubCooling() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->degreeofLoopSubCooling();
  }

  bool LoadProfilePlant::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
    return getImpl<detail::LoadProfilePlant_Impl>()->setDegreeofLoopSubCooling(degreeofLoopSubCooling);
  }

  bool LoadProfilePlant::isDegreeofLoopSubCoolingDefaulted() const {
    return getImpl<detail::LoadProfilePlant_Impl>()->isDegreeofLoopSubCoolingDefaulted();
  }

  void LoadProfilePlant::resetDegreeofLoopSubCooling() {
    getImpl<detail::LoadProfilePlant_Impl>()->resetDegreeofLoopSubCooling();
  }

  bool LoadProfilePlant::addToNode(Node& node) {
    return getImpl<detail::LoadProfilePlant_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned LoadProfilePlant_Impl::inletPort() const {
      return LoadProfile_PlantFields::InletNodeName;
    }

    unsigned LoadProfilePlant_Impl::outletPort() const {
      return LoadProfile_PlantFields::OutletNodeName;
    }

    bool LoadProfilePlant_Impl::addToNode(Node& node) {
      if (auto plant = node.plantLoop()) {
        if (plant->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    Schedule LoadProfilePlant_Impl::loadSchedule() const {
      auto value = optionalLoadSchedule();
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setLoadSchedule(Schedule& schedule) {
      return setSchedule(openstudio::LoadProfile_PlantFields::LoadScheduleName, "LoadProfilePlant", "Load", schedule);
    }

    double LoadProfilePlant_Impl::peakFlowRate() const {
      const auto value = getDouble(openstudio::LoadProfile_PlantFields::PeakFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setPeakFlowRate(double peakFlowRate) {
      const bool result = setDouble(openstudio::LoadProfile_PlantFields::PeakFlowRate, peakFlowRate);
      OS_ASSERT(result);
      return result;
    }

    Schedule LoadProfilePlant_Impl::flowRateFractionSchedule() const {
      auto value = optionalFlowRateFractionSchedule();
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setFlowRateFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::LoadProfile_PlantFields::FlowRateFractionScheduleName, "LoadProfilePlant", "Flow Rate Fraction", schedule);
    }

    std::string LoadProfilePlant_Impl::plantLoopFluidType() const {
      const auto value = getString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setPlantLoopFluidType(const std::string& plantLoopFluidType) {
      return setString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, plantLoopFluidType);
    }

    bool LoadProfilePlant_Impl::isPlantLoopFluidTypeDefaulted() const {
      return isEmpty(openstudio::LoadProfile_PlantFields::PlantLoopFluidType);
    }

    void LoadProfilePlant_Impl::resetPlantLoopFluidType() {
      const bool result = setString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, "");
      OS_ASSERT(result);
    }

    double LoadProfilePlant_Impl::degreeofSubCooling() const {
      const auto value = getDouble(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setDegreeofSubCooling(double degreeofSubCooling) {
      return setDouble(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, degreeofSubCooling);
    }

    bool LoadProfilePlant_Impl::isDegreeofSubCoolingDefaulted() const {
      return isEmpty(openstudio::LoadProfile_PlantFields::DegreeofSubCooling);
    }

    void LoadProfilePlant_Impl::resetDegreeofSubCooling() {
      const bool result = setString(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, "");
      OS_ASSERT(result);
    }

    double LoadProfilePlant_Impl::degreeofLoopSubCooling() const {
      const auto value = getDouble(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool LoadProfilePlant_Impl::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
      return setDouble(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, degreeofLoopSubCooling);
    }

    bool LoadProfilePlant_Impl::isDegreeofLoopSubCoolingDefaulted() const {
      return isEmpty(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling);
    }

    void LoadProfilePlant_Impl::resetDegreeofLoopSubCooling() {
      const bool result = setString(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> LoadProfilePlant_Impl::plantLoopFluidTypeValues() const {
      return openstudio::epmodel::LoadProfilePlant::plantLoopFluidTypeValues();
    }

    boost::optional<Schedule> LoadProfilePlant_Impl::optionalLoadSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::LoadProfile_PlantFields::LoadScheduleName);
    }

    boost::optional<Schedule> LoadProfilePlant_Impl::optionalFlowRateFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::LoadProfile_PlantFields::FlowRateFractionScheduleName);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
