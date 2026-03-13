/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLEROBJECTREFERENCE_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLEROBJECTREFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantChillerObjectReference_Impl;
  }

  class EPMODEL_API HVACTemplatePlantChillerObjectReference : public ModelObject
  {
   public:
    explicit HVACTemplatePlantChillerObjectReference(const Model& model);

    virtual ~HVACTemplatePlantChillerObjectReference() override = default;
    HVACTemplatePlantChillerObjectReference(const HVACTemplatePlantChillerObjectReference& other) = default;
    HVACTemplatePlantChillerObjectReference(HVACTemplatePlantChillerObjectReference&& other) = default;
    HVACTemplatePlantChillerObjectReference& operator=(const HVACTemplatePlantChillerObjectReference&) = default;
    HVACTemplatePlantChillerObjectReference& operator=(HVACTemplatePlantChillerObjectReference&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> chillerObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map to HVACTemplate:Plant:Chiller:ObjectReference fields Chiller Object Type and Priority.
    // - Field Mapping: Chiller Name is an object-list relationship field and is intentionally excluded in scalar-only scaffold.
    // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
    std::string chillerObjectType() const;
    bool isChillerObjectTypeDefaulted() const;
    bool setChillerObjectType(const std::string& chillerObjectType);
    void resetChillerObjectType();

    boost::optional<double> priority() const;
    bool setPriority(double priority);
    void resetPriority();

   protected:
    using ImplType = detail::HVACTemplatePlantChillerObjectReference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantChillerObjectReference(std::shared_ptr<detail::HVACTemplatePlantChillerObjectReference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
