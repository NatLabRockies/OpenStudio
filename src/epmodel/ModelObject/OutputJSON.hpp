/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTJSON_HPP
#define EPMODEL_OUTPUTJSON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputJSON_Impl;
  }

  class EPMODEL_API OutputJSON : public ModelObject
  {
   public:
    virtual ~OutputJSON() override = default;
    OutputJSON(const OutputJSON& other) = default;
    OutputJSON(OutputJSON&& other) = default;
    OutputJSON& operator=(const OutputJSON&) = default;
    OutputJSON& operator=(OutputJSON&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> optionTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputJSON scalar accessor names/signatures.
    // - Field Mapping: optionType/outputJSON/outputCBOR/outputMessagePack map directly to E+ Output:JSON Option Type/Output JSON/Output CBOR/Output MessagePack.
    // - ForwardTranslator evidence: ForwardTranslateOutputJSON.cpp writes these preserved APIs directly to Output:JSON fields.
    // - TODO(parity): Keep scalar API stable while extending any non-scalar parity behavior in future passes.

    // optionType
    std::string optionType() const;
    bool setOptionType(const std::string& optionType);

    // outputJSON
    bool outputJSON() const;
    bool setOutputJSON(bool outputJSON);

    // outputCBOR
    bool outputCBOR() const;
    bool setOutputCBOR(bool outputCBOR);

    // outputMessagePack
    bool outputMessagePack() const;
    bool setOutputMessagePack(bool outputMessagePack);

   protected:
    explicit OutputJSON(const Model& model);

    using ImplType = detail::OutputJSON_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputJSON(std::shared_ptr<detail::OutputJSON_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
