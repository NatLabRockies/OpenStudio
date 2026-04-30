/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONSTRUCTIONS_HPP
#define EPMODEL_OUTPUTCONSTRUCTIONS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputConstructions_Impl;
  }

  class EPMODEL_API OutputConstructions : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    explicit OutputConstructions(const Model& model);

    virtual ~OutputConstructions() override = default;
    OutputConstructions(const OutputConstructions& other) = default;
    OutputConstructions(OutputConstructions&& other) = default;
    OutputConstructions& operator=(const OutputConstructions&) = default;
    OutputConstructions& operator=(OutputConstructions&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputConstructions scalar accessor names/signatures.
    // - Field Mapping: reportConstructions/reportMaterials map onto E+ Output:Constructions Details Type 1/2 key presence.
    // - ForwardTranslator evidence: ForwardTranslateOutputConstructions.cpp emits canonical key ordering based on these booleans.
    // - TODO(parity): Keep these boolean APIs stable while extending translator-parity behaviors.
    bool reportConstructions() const;
    bool setReportConstructions(bool reportConstructions);

    bool reportMaterials() const;
    bool setReportMaterials(bool reportMaterials);

   protected:
    using ImplType = detail::OutputConstructions_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputConstructions(std::shared_ptr<detail::OutputConstructions_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
