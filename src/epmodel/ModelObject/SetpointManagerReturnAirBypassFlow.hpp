/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERRETURNAIRBYPASSFLOW_HPP
#define EPMODEL_SETPOINTMANAGERRETURNAIRBYPASSFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerReturnAirBypassFlow_Impl;
  }

  class EPMODEL_API SetpointManagerReturnAirBypassFlow : public ModelObject
  {
   public:
    explicit SetpointManagerReturnAirBypassFlow(const Model& model);

    virtual ~SetpointManagerReturnAirBypassFlow() override = default;
    SetpointManagerReturnAirBypassFlow(const SetpointManagerReturnAirBypassFlow& other) = default;
    SetpointManagerReturnAirBypassFlow(SetpointManagerReturnAirBypassFlow&& other) = default;
    SetpointManagerReturnAirBypassFlow& operator=(const SetpointManagerReturnAirBypassFlow&) = default;
    SetpointManagerReturnAirBypassFlow& operator=(SetpointManagerReturnAirBypassFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SetpointManager:ReturnAirBypassFlow fields.
    // - Field Mapping: HVAC Air Loop Name and Temperature Setpoint Schedule Name are relationship
    //   fields and are excluded from scalar-only scaffold scope.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    /** @name Control Variable */
    //@{
    std::string controlVariable() const;
    bool isControlVariableDefaulted() const;
    bool setControlVariable(const std::string& controlVariable);
    void resetControlVariable();
    //@}

   protected:
    using ImplType = detail::SetpointManagerReturnAirBypassFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerReturnAirBypassFlow(std::shared_ptr<detail::SetpointManagerReturnAirBypassFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
