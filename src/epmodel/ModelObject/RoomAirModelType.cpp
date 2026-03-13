/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirModelType.hpp"
#include "RoomAirModelType_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoomAirModelType_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirModelType::RoomAirModelType(const Model& model) : ModelObject(RoomAirModelType::iddObjectType(), model) {}

  RoomAirModelType::RoomAirModelType(std::shared_ptr<detail::RoomAirModelType_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirModelType::iddObjectType() {
    return IddObjectType::RoomAirModelType;
  }

  std::vector<std::string> RoomAirModelType::roomAirModelingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoomAirModelTypeFields::RoomAirModelingType);
  }

  std::vector<std::string> RoomAirModelType::airTemperatureCouplingStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::RoomAirModelTypeFields::AirTemperatureCouplingStrategy);
  }

  std::string RoomAirModelType::roomAirModelingType() const {
    return getImpl<detail::RoomAirModelType_Impl>()->roomAirModelingType();
  }

  bool RoomAirModelType::isRoomAirModelingTypeDefaulted() const {
    return getImpl<detail::RoomAirModelType_Impl>()->isRoomAirModelingTypeDefaulted();
  }

  bool RoomAirModelType::setRoomAirModelingType(const std::string& roomAirModelingType) {
    return getImpl<detail::RoomAirModelType_Impl>()->setRoomAirModelingType(roomAirModelingType);
  }

  void RoomAirModelType::resetRoomAirModelingType() {
    getImpl<detail::RoomAirModelType_Impl>()->resetRoomAirModelingType();
  }

  std::string RoomAirModelType::airTemperatureCouplingStrategy() const {
    return getImpl<detail::RoomAirModelType_Impl>()->airTemperatureCouplingStrategy();
  }

  bool RoomAirModelType::isAirTemperatureCouplingStrategyDefaulted() const {
    return getImpl<detail::RoomAirModelType_Impl>()->isAirTemperatureCouplingStrategyDefaulted();
  }

  bool RoomAirModelType::setAirTemperatureCouplingStrategy(const std::string& airTemperatureCouplingStrategy) {
    return getImpl<detail::RoomAirModelType_Impl>()->setAirTemperatureCouplingStrategy(airTemperatureCouplingStrategy);
  }

  void RoomAirModelType::resetAirTemperatureCouplingStrategy() {
    getImpl<detail::RoomAirModelType_Impl>()->resetAirTemperatureCouplingStrategy();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RoomAirModelType_Impl::roomAirModelingType() const {
      const auto value = getString(openstudio::RoomAirModelTypeFields::RoomAirModelingType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirModelType_Impl::isRoomAirModelingTypeDefaulted() const {
      return isEmpty(openstudio::RoomAirModelTypeFields::RoomAirModelingType);
    }

    bool RoomAirModelType_Impl::setRoomAirModelingType(const std::string& roomAirModelingType) {
      return setString(openstudio::RoomAirModelTypeFields::RoomAirModelingType, roomAirModelingType);
    }

    void RoomAirModelType_Impl::resetRoomAirModelingType() {
      OS_ASSERT(setString(openstudio::RoomAirModelTypeFields::RoomAirModelingType, ""));
    }

    std::string RoomAirModelType_Impl::airTemperatureCouplingStrategy() const {
      const auto value = getString(openstudio::RoomAirModelTypeFields::AirTemperatureCouplingStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirModelType_Impl::isAirTemperatureCouplingStrategyDefaulted() const {
      return isEmpty(openstudio::RoomAirModelTypeFields::AirTemperatureCouplingStrategy);
    }

    bool RoomAirModelType_Impl::setAirTemperatureCouplingStrategy(const std::string& airTemperatureCouplingStrategy) {
      return setString(openstudio::RoomAirModelTypeFields::AirTemperatureCouplingStrategy, airTemperatureCouplingStrategy);
    }

    void RoomAirModelType_Impl::resetAirTemperatureCouplingStrategy() {
      OS_ASSERT(setString(openstudio::RoomAirModelTypeFields::AirTemperatureCouplingStrategy, ""));
    }

    std::vector<std::string> RoomAirModelType_Impl::roomAirModelingTypeValues() const {
      return openstudio::epmodel::RoomAirModelType::roomAirModelingTypeValues();
    }

    std::vector<std::string> RoomAirModelType_Impl::airTemperatureCouplingStrategyValues() const {
      return openstudio::epmodel::RoomAirModelType::airTemperatureCouplingStrategyValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
