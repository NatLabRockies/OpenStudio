/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsCrossVentilation.hpp"
#include "RoomAirSettingsCrossVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoomAirSettings_CrossVentilation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirSettingsCrossVentilation::RoomAirSettingsCrossVentilation(const Model& model)
    : ModelObject(RoomAirSettingsCrossVentilation::iddObjectType(), model) {}

  RoomAirSettingsCrossVentilation::RoomAirSettingsCrossVentilation(std::shared_ptr<detail::RoomAirSettingsCrossVentilation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirSettingsCrossVentilation::iddObjectType() {
    return IddObjectType::RoomAirSettings_CrossVentilation;
  }

  std::vector<std::string> RoomAirSettingsCrossVentilation::airflowRegionUsedforThermalComfortEvaluationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::RoomAirSettings_CrossVentilationFields::AirflowRegionUsedforThermalComfortEvaluation);
  }

  boost::optional<std::string> RoomAirSettingsCrossVentilation::airflowRegionUsedforThermalComfortEvaluation() const {
    return getImpl<detail::RoomAirSettingsCrossVentilation_Impl>()->airflowRegionUsedforThermalComfortEvaluation();
  }

  bool RoomAirSettingsCrossVentilation::setAirflowRegionUsedforThermalComfortEvaluation(
    const std::string& airflowRegionUsedforThermalComfortEvaluation) {
    return getImpl<detail::RoomAirSettingsCrossVentilation_Impl>()->setAirflowRegionUsedforThermalComfortEvaluation(
      airflowRegionUsedforThermalComfortEvaluation);
  }

  void RoomAirSettingsCrossVentilation::resetAirflowRegionUsedforThermalComfortEvaluation() {
    getImpl<detail::RoomAirSettingsCrossVentilation_Impl>()->resetAirflowRegionUsedforThermalComfortEvaluation();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> RoomAirSettingsCrossVentilation_Impl::airflowRegionUsedforThermalComfortEvaluation() const {
      return getString(openstudio::RoomAirSettings_CrossVentilationFields::AirflowRegionUsedforThermalComfortEvaluation, true);
    }

    bool RoomAirSettingsCrossVentilation_Impl::setAirflowRegionUsedforThermalComfortEvaluation(
      const std::string& airflowRegionUsedforThermalComfortEvaluation) {
      return setString(openstudio::RoomAirSettings_CrossVentilationFields::AirflowRegionUsedforThermalComfortEvaluation,
                       airflowRegionUsedforThermalComfortEvaluation);
    }

    void RoomAirSettingsCrossVentilation_Impl::resetAirflowRegionUsedforThermalComfortEvaluation() {
      const bool result = setString(openstudio::RoomAirSettings_CrossVentilationFields::AirflowRegionUsedforThermalComfortEvaluation, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> RoomAirSettingsCrossVentilation_Impl::airflowRegionUsedforThermalComfortEvaluationValues() const {
      return openstudio::epmodel::RoomAirSettingsCrossVentilation::airflowRegionUsedforThermalComfortEvaluationValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
