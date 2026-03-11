/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctUserDefined_Impl;
}

class EPMODEL_API AirTerminalSingleDuctUserDefined : public ModelObject
{
 public:
  explicit AirTerminalSingleDuctUserDefined(const Model& model);

  virtual ~AirTerminalSingleDuctUserDefined() override = default;
  AirTerminalSingleDuctUserDefined(const AirTerminalSingleDuctUserDefined& other) = default;
  AirTerminalSingleDuctUserDefined(AirTerminalSingleDuctUserDefined&& other) = default;
  AirTerminalSingleDuctUserDefined& operator=(const AirTerminalSingleDuctUserDefined&) = default;
  AirTerminalSingleDuctUserDefined& operator=(AirTerminalSingleDuctUserDefined&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived naming for scalar accessors.
  // - Field Mapping: numberofPlantLoopConnections maps directly to E+ AirTerminal:SingleDuct:UserDefined Number of Plant Loop Connections.
  // - Field Mapping: Program calling manager names, node names, tank names, and Ambient Zone Name are relationship fields and intentionally excluded
  //   from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
  int numberofPlantLoopConnections() const;
  bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);

 protected:
  using ImplType = detail::AirTerminalSingleDuctUserDefined_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctUserDefined(std::shared_ptr<detail::AirTerminalSingleDuctUserDefined_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
