/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLESUMMARYREPORTS_HPP
#define EPMODEL_OUTPUTTABLESUMMARYREPORTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputTableSummaryReports_Impl;
  }

  /** \brief OutputTableSummaryReports.
   *
   * \par EnergyPlus object
   * \epobject{output-table-summaryreports.html#outputtablesummaryreports,Output:Table:SummaryReports}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputTableSummaryReports</code>. This object contains extensible report-name rows. EPModel exposes no public summary-report list mutation or query methods.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputTableSummaryReports : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputTableSummaryReports() override = default;
    OutputTableSummaryReports(const OutputTableSummaryReports& other) = default;
    OutputTableSummaryReports(OutputTableSummaryReports&& other) = default;
    OutputTableSummaryReports& operator=(const OutputTableSummaryReports&) = default;
    OutputTableSummaryReports& operator=(OutputTableSummaryReports&&) = default;

    static IddObjectType iddObjectType();

   protected:
    explicit OutputTableSummaryReports(const Model& model);

    using ImplType = detail::OutputTableSummaryReports_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputTableSummaryReports(std::shared_ptr<detail::OutputTableSummaryReports_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
