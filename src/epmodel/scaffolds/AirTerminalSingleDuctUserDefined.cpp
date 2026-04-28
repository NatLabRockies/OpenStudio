/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirTerminalSingleDuctUserDefined.hpp"
#include "AirTerminalSingleDuctUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_UserDefined_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirTerminalSingleDuctUserDefined::AirTerminalSingleDuctUserDefined(const Model& model)
    : ModelObject(AirTerminalSingleDuctUserDefined::iddObjectType(), model) {}

  AirTerminalSingleDuctUserDefined::AirTerminalSingleDuctUserDefined(std::shared_ptr<detail::AirTerminalSingleDuctUserDefined_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctUserDefined::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_UserDefined;
  }

  int AirTerminalSingleDuctUserDefined::numberofPlantLoopConnections() const {
    return getImpl<detail::AirTerminalSingleDuctUserDefined_Impl>()->numberofPlantLoopConnections();
  }

  bool AirTerminalSingleDuctUserDefined::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
    return getImpl<detail::AirTerminalSingleDuctUserDefined_Impl>()->setNumberofPlantLoopConnections(numberofPlantLoopConnections);
  }

  // Detail implementations for the scalar accessors
  namespace detail {

    int AirTerminalSingleDuctUserDefined_Impl::numberofPlantLoopConnections() const {
      const auto value = getInt(openstudio::AirTerminal_SingleDuct_UserDefinedFields::NumberofPlantLoopConnections, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctUserDefined_Impl::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
      return setInt(openstudio::AirTerminal_SingleDuct_UserDefinedFields::NumberofPlantLoopConnections, numberofPlantLoopConnections);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
