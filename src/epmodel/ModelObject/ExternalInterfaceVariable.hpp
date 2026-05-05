/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceVariable_Impl;
  }

  class EPMODEL_API ExternalInterfaceVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceVariable(const Model& model, const std::string& variableName, double initialValue);

    virtual ~ExternalInterfaceVariable() override = default;
    ExternalInterfaceVariable(const ExternalInterfaceVariable& other) = default;
    ExternalInterfaceVariable(ExternalInterfaceVariable&& other) = default;
    ExternalInterfaceVariable& operator=(const ExternalInterfaceVariable&) = default;
    ExternalInterfaceVariable& operator=(ExternalInterfaceVariable&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceVariable scalar accessor names/signatures.
    // - Field Mapping: initialValue -> ExternalInterface:Variable, Initial Value.
    // - Field Mapping: exportToBCVTB APIs are OS-only (OS:ExternalInterface:Variable) and not present on
    //   EnergyPlus ExternalInterface:Variable; ForwardTranslator evidence confirms only Initial Value is written.
    // - TODO(parity): Add OS-only/export behavior only when epmodel supports OS-level schema parity.
    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceVariable(std::shared_ptr<detail::ExternalInterfaceVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
