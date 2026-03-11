/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_HPP
#define EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyOtherSideConditionsModel_Impl;
  }

  class EPMODEL_API SurfacePropertyOtherSideConditionsModel : public ModelObject
  {
   public:
    explicit SurfacePropertyOtherSideConditionsModel(const Model& model);

    virtual ~SurfacePropertyOtherSideConditionsModel() override = default;
    SurfacePropertyOtherSideConditionsModel(const SurfacePropertyOtherSideConditionsModel& other) = default;
    SurfacePropertyOtherSideConditionsModel(SurfacePropertyOtherSideConditionsModel&& other) = default;
    SurfacePropertyOtherSideConditionsModel& operator=(const SurfacePropertyOtherSideConditionsModel&) = default;
    SurfacePropertyOtherSideConditionsModel& operator=(SurfacePropertyOtherSideConditionsModel&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeOfModelingValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model API names/signatures for SurfacePropertyOtherSideConditionsModel.
    // - Field Mapping: `typeOfModeling` forwards directly to the EnergyPlus SurfaceProperty:OtherSideConditionsModel
    //   field (SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling).
    // - ForwardTranslator evidence: ForwardTranslateSurfacePropertyOtherSideConditionsModel.cpp writes the same field
    //   when translating the openstudio::model counterpart and confirms the default choice semantics.
    std::string typeOfModeling() const;
    bool isTypeOfModelingDefaulted() const;

    bool setTypeOfModeling(const std::string& typeOfModeling);
    void resetTypeOfModeling();

   protected:
    using ImplType = detail::SurfacePropertyOtherSideConditionsModel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyOtherSideConditionsModel(std::shared_ptr<detail::SurfacePropertyOtherSideConditionsModel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
