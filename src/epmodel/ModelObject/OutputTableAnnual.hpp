/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEANNUAL_HPP
#define EPMODEL_OUTPUTTABLEANNUAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputTableAnnual_Impl;
  }

  /** \brief OutputTableAnnual.
   *
   * \par EnergyPlus object
   * \epobject{output-table-annual.html#outputtableannual,Output:Table:Annual}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputTableAnnual</code>. The filter field is exposed; extensible annual-table rows are not managed by EPModel.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputTableAnnual : public ModelObject
  {
   public:
    explicit OutputTableAnnual(const Model& model);

    virtual ~OutputTableAnnual() override = default;
    OutputTableAnnual(const OutputTableAnnual& other) = default;
    OutputTableAnnual(OutputTableAnnual&& other) = default;
    OutputTableAnnual& operator=(const OutputTableAnnual&) = default;
    OutputTableAnnual& operator=(OutputTableAnnual&&) = default;

    static IddObjectType iddObjectType();
    boost::optional<std::string> filter() const;

    bool setFilter(const std::string& filter);
    void resetFilter();

   protected:
    using ImplType = detail::OutputTableAnnual_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputTableAnnual(std::shared_ptr<detail::OutputTableAnnual_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
