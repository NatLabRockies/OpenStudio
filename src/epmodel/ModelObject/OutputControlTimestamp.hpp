/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLTIMESTAMP_HPP
#define EPMODEL_OUTPUTCONTROLTIMESTAMP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputControlTimestamp_Impl;
  }

  class EPMODEL_API OutputControlTimestamp : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    explicit OutputControlTimestamp(const Model& model);

    virtual ~OutputControlTimestamp() override = default;
    OutputControlTimestamp(const OutputControlTimestamp& other) = default;
    OutputControlTimestamp(OutputControlTimestamp&& other) = default;
    OutputControlTimestamp& operator=(const OutputControlTimestamp&) = default;
    OutputControlTimestamp& operator=(OutputControlTimestamp&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputControlTimestamp scalar accessor names/signatures.
    // - Field Mapping: iso8601Format/timestampAtBeginningOfInterval map directly to E+ OutputControl:Timestamp
    //   ISO8601 Format / Timestamp at Beginning of Interval.
    // - ForwardTranslator evidence: model ForwardTranslateOutputControlTimestamp.cpp writes these preserved APIs
    //   directly to matching E+ fields with Yes/No conversion.
    // - TODO(parity): Keep scalar API stable while adding broader parity behavior in future passes.
    bool iso8601Format() const;
    bool setISO8601Format(bool iso8601Format);

    bool timestampAtBeginningOfInterval() const;
    bool setTimestampAtBeginningOfInterval(bool timestampAtBeginningOfInterval);

   protected:
    using ImplType = detail::OutputControlTimestamp_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlTimestamp(std::shared_ptr<detail::OutputControlTimestamp_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
