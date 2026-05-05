/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ControllerOutdoorAir;

  namespace detail {
    class ControllerMechanicalVentilation_Impl;
  }

  class EPMODEL_API ControllerMechanicalVentilation : public ModelObject
  {
   public:
    explicit ControllerMechanicalVentilation(const Model& model);

    virtual ~ControllerMechanicalVentilation() override = default;
    ControllerMechanicalVentilation(const ControllerMechanicalVentilation& other) = default;
    ControllerMechanicalVentilation(ControllerMechanicalVentilation&& other) = default;
    ControllerMechanicalVentilation& operator=(const ControllerMechanicalVentilation&) = default;
    ControllerMechanicalVentilation& operator=(ControllerMechanicalVentilation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemOutdoorAirMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ControllerMechanicalVentilation scalar accessor names/signatures.
    // - Field Mapping: DemandControlledVentilation and SystemOutdoorAirMethod map directly to same-named E+ fields.
    // - Field Mapping: Availability schedule and extensible zone/DSOA links are relationship-like and excluded from scalar API generation.
    // - ForwardTranslator evidence: ForwardTranslateControllerMechanicalVentilation.cpp writes these scalar fields directly.
    // - TODO(parity): Add remaining relationship API parity incrementally without changing preserved scalar signatures.
    bool demandControlledVentilation() const;
    bool isDemandControlledVentilationDefaulted() const;
    bool setDemandControlledVentilation(bool value);
    void setDemandControlledVentilationNoFail(bool value);
    void resetDemandControlledVentilation();

    std::string systemOutdoorAirMethod() const;
    bool isSystemOutdoorAirMethodDefaulted() const;
    bool setSystemOutdoorAirMethod(const std::string& value);
    void resetSystemOutdoorAirMethod();

    boost::optional<ControllerOutdoorAir> controllerOutdoorAir() const;

   protected:
    using ImplType = detail::ControllerMechanicalVentilation_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ControllerMechanicalVentilation(std::shared_ptr<detail::ControllerMechanicalVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
