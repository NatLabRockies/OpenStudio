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

  /** \brief OutputControlTimestamp.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputcontrol_timestamp,OutputControl:Timestamp}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputControlTimestamp</code>. The two boolean settings map to EnergyPlus yes/no fields. The EPModel setter is named <code>setISO8601Format()</code>.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputControlTimestamp : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputControlTimestamp() override = default;
    OutputControlTimestamp(const OutputControlTimestamp& other) = default;
    OutputControlTimestamp(OutputControlTimestamp&& other) = default;
    OutputControlTimestamp& operator=(const OutputControlTimestamp&) = default;
    OutputControlTimestamp& operator=(OutputControlTimestamp&&) = default;

    static IddObjectType iddObjectType();
    bool iso8601Format() const;
    bool setISO8601Format(bool iso8601Format);

    bool timestampAtBeginningOfInterval() const;
    bool setTimestampAtBeginningOfInterval(bool timestampAtBeginningOfInterval);

   protected:
    explicit OutputControlTimestamp(const Model& model);

    using ImplType = detail::OutputControlTimestamp_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlTimestamp(std::shared_ptr<detail::OutputControlTimestamp_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
