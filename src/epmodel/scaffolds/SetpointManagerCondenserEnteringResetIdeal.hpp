/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESETIDEAL_HPP
#define EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESETIDEAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerCondenserEnteringResetIdeal_Impl;
  }

  class EPMODEL_API SetpointManagerCondenserEnteringResetIdeal : public ModelObject
  {
   public:
    explicit SetpointManagerCondenserEnteringResetIdeal(const Model& model);

    virtual ~SetpointManagerCondenserEnteringResetIdeal() override = default;
    SetpointManagerCondenserEnteringResetIdeal(const SetpointManagerCondenserEnteringResetIdeal& other) = default;
    SetpointManagerCondenserEnteringResetIdeal(SetpointManagerCondenserEnteringResetIdeal&& other) = default;
    SetpointManagerCondenserEnteringResetIdeal& operator=(const SetpointManagerCondenserEnteringResetIdeal&) = default;
    SetpointManagerCondenserEnteringResetIdeal& operator=(SetpointManagerCondenserEnteringResetIdeal&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SetpointManager:CondenserEnteringReset:Ideal fields.
    // - Field Mapping: Setpoint Node or NodeList Name is a relationship field and is excluded.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    std::string controlVariable() const;
    bool isControlVariableDefaulted() const;
    bool setControlVariable(const std::string& controlVariable);
    void resetControlVariable();

    double minimumLift() const;
    bool isMinimumLiftDefaulted() const;
    bool setMinimumLift(double minimumLift);
    void resetMinimumLift();

    double maximumCondenserEnteringWaterTemperature() const;
    bool isMaximumCondenserEnteringWaterTemperatureDefaulted() const;
    bool setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature);
    void resetMaximumCondenserEnteringWaterTemperature();

   protected:
    using ImplType = detail::SetpointManagerCondenserEnteringResetIdeal_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerCondenserEnteringResetIdeal(std::shared_ptr<detail::SetpointManagerCondenserEnteringResetIdeal_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
