/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTBOILEROBJECTREFERENCE_HPP
#define EPMODEL_HVACTEMPLATEPLANTBOILEROBJECTREFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantBoilerObjectReference_Impl;
  }

  class EPMODEL_API HVACTemplatePlantBoilerObjectReference : public ModelObject
  {
   public:
    explicit HVACTemplatePlantBoilerObjectReference(const Model& model);

    virtual ~HVACTemplatePlantBoilerObjectReference() override = default;
    HVACTemplatePlantBoilerObjectReference(const HVACTemplatePlantBoilerObjectReference& other) = default;
    HVACTemplatePlantBoilerObjectReference(HVACTemplatePlantBoilerObjectReference&& other) = default;
    HVACTemplatePlantBoilerObjectReference& operator=(const HVACTemplatePlantBoilerObjectReference&) = default;
    HVACTemplatePlantBoilerObjectReference& operator=(HVACTemplatePlantBoilerObjectReference&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> boilerObjectTypeValues();
    static std::vector<std::string> templatePlantLoopTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map to HVACTemplate:Plant:Boiler:ObjectReference fields Boiler Object Type,
    //   Priority, and Template Plant Loop Type.
    // - Field Mapping: Boiler Name is an object-list relationship field and is intentionally excluded in scalar-only scaffold.
    // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
    std::string boilerObjectType() const;
    bool isBoilerObjectTypeDefaulted() const;
    bool setBoilerObjectType(const std::string& boilerObjectType);
    void resetBoilerObjectType();

    boost::optional<double> priority() const;
    bool setPriority(double priority);
    void resetPriority();

    boost::optional<std::string> templatePlantLoopType() const;
    bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
    void resetTemplatePlantLoopType();

   protected:
    using ImplType = detail::HVACTemplatePlantBoilerObjectReference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantBoilerObjectReference(std::shared_ptr<detail::HVACTemplatePlantBoilerObjectReference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
