/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORLIGHTS_HPP
#define EPMODEL_EXTERIORLIGHTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExteriorLights_Impl;
  }

  class EPMODEL_API ExteriorLights : public ModelObject
  {
   public:
    explicit ExteriorLights(const Model& model);

    virtual ~ExteriorLights() override = default;
    ExteriorLights(const ExteriorLights& other) = default;
    ExteriorLights(ExteriorLights&& other) = default;
    ExteriorLights& operator=(const ExteriorLights&) = default;
    ExteriorLights& operator=(ExteriorLights&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlOptionValues();
    static std::vector<std::string> validControlOptionValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExteriorLights scalar accessor names/signatures.
    // - Field Mapping: controlOption/endUseSubcategory map directly to E+ Exterior:Lights Control Option/End-Use Subcategory.
    // - Field Mapping: multiplier API currently delegates to E+ Exterior:Lights Design Level (no direct E+ multiplier field).
    // - Field Mapping: Schedule Name is excluded as a relationship field in this scalar-only scaffold pass.
    // - ForwardTranslator evidence: ForwardTranslateExteriorLights.cpp writes Design Level from
    //   definition.designLevel() * modelObject.multiplier(), and maps controlOption/endUseSubcategory directly.
    // - TODO(parity): Add relationship/definition graph parity without changing preserved scalar signatures.
    std::string controlOption() const;
    bool isControlOptionDefaulted() const;
    bool setControlOption(const std::string& controlOption);
    void resetControlOption();

    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::ExteriorLights_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExteriorLights(std::shared_ptr<detail::ExteriorLights_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
