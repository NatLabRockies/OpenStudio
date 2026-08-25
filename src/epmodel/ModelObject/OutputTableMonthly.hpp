/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEMONTHLY_HPP
#define EPMODEL_OUTPUTTABLEMONTHLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputTableMonthly_Impl;
  }

  /** \brief OutputTableMonthly.
   *
   * \par EnergyPlus object
   * \epobject{output-table-monthly.html#outputtablemonthly,Output:Table:Monthly}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputTableMonthly</code>. The digits-after-decimal setting is exposed. Model's extensible monthly-table row APIs are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputTableMonthly : public ModelObject
  {
   public:
    explicit OutputTableMonthly(const Model& model);

    virtual ~OutputTableMonthly() override = default;
    OutputTableMonthly(const OutputTableMonthly& other) = default;
    OutputTableMonthly(OutputTableMonthly&& other) = default;
    OutputTableMonthly& operator=(const OutputTableMonthly&) = default;
    OutputTableMonthly& operator=(OutputTableMonthly&&) = default;

    static IddObjectType iddObjectType();

    /** @name Digits After Decimal */
    //@{
    int digitsAfterDecimal() const;

    bool setDigitsAfterDecimal(int digitsAfterDecimal);
    //@}

   protected:
    using ImplType = detail::OutputTableMonthly_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputTableMonthly(std::shared_ptr<detail::OutputTableMonthly_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
