/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORT_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImport_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImport : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImport(const Model& model, const std::string& fmuName);

    virtual ~ExternalInterfaceFunctionalMockupUnitImport() override = default;
    ExternalInterfaceFunctionalMockupUnitImport(const ExternalInterfaceFunctionalMockupUnitImport& other) = default;
    ExternalInterfaceFunctionalMockupUnitImport(ExternalInterfaceFunctionalMockupUnitImport&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImport& operator=(const ExternalInterfaceFunctionalMockupUnitImport&) = default;
    ExternalInterfaceFunctionalMockupUnitImport& operator=(ExternalInterfaceFunctionalMockupUnitImport&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitImport scalar accessor names/signatures.
    // - Field Mapping: fMUFileName -> ExternalInterface:FunctionalMockupUnitImport, FMU File Name.
    // - Field Mapping: fMUTimeout -> ExternalInterface:FunctionalMockupUnitImport, FMU Timeout.
    // - Field Mapping: fMULoggingOn -> ExternalInterface:FunctionalMockupUnitImport, FMU LoggingOn.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitImport.cpp writes these fields directly.
    // - TODO(parity): Keep preserved scalar API stable while relationship-based FMU wiring is added in follow-up types.
    double fMUTimeout() const;
    bool isFMUTimeoutDefaulted() const;
    bool setFMUTimeout(double fMUTimeout);
    void resetFMUTimeout();

    int fMULoggingOn() const;
    bool isFMULoggingOnDefaulted() const;
    bool setFMULoggingOn(int fMULoggingOn);
    void resetFMULoggingOn();

    std::string fMUFileName() const;
    bool setFMUFileName(const std::string& fMUName);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImport_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImport(std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImport_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
