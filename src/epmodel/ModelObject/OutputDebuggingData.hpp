/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDEBUGGINGDATA_HPP
#define EPMODEL_OUTPUTDEBUGGINGDATA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputDebuggingData_Impl;
  }

  /** \brief OutputDebuggingData.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#outputdebuggingdata,Output:DebuggingData}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputDebuggingData</code>. The two reporting switches map directly to EnergyPlus yes/no fields.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputDebuggingData : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputDebuggingData() override = default;
    OutputDebuggingData(const OutputDebuggingData& other) = default;
    OutputDebuggingData(OutputDebuggingData&& other) = default;
    OutputDebuggingData& operator=(const OutputDebuggingData&) = default;
    OutputDebuggingData& operator=(OutputDebuggingData&&) = default;

    static IddObjectType iddObjectType();
    bool reportDebuggingData() const;
    bool setReportDebuggingData(bool reportDebuggingData);

    bool reportDuringWarmup() const;
    bool setReportDuringWarmup(bool reportDuringWarmup);

   protected:
    explicit OutputDebuggingData(const Model& model);

    using ImplType = detail::OutputDebuggingData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputDebuggingData(std::shared_ptr<detail::OutputDebuggingData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
