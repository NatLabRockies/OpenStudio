/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BRANCH_HPP
#define EPMODEL_BRANCH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  namespace detail {
    class Branch_Impl;
  }

  class EPMODEL_API Branch : public ModelObject
  {
   public:
    explicit Branch(const Model& model);

    virtual ~Branch() override = default;
    Branch(const Branch& other) = default;
    Branch(Branch&& other) = default;
    Branch& operator=(const Branch&) = default;
    Branch& operator=(Branch&&) = default;

    std::vector<ModelObject> components() const;
    boost::optional<Node> componentInletNode(unsigned index) const;
    boost::optional<Node> componentOutletNode(unsigned index) const;

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Pressure Drop Curve Name and extensible component/node fields are relationship-like link fields and are excluded from scalar accessors.
    // - ForwardTranslator evidence: ForwardTranslatePlantLoop and ForwardTranslateAirLoopHVAC populate Branch as a connectivity/linkage object.
    // - TODO(parity): Add explicit relationship APIs incrementally after scalar scaffold saturation.

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::Branch_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Branch(std::shared_ptr<detail::Branch_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
