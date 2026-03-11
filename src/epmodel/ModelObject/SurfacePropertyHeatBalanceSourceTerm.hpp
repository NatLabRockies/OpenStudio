/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATBALANCESOURCETERM_HPP
#define EPMODEL_SURFACEPROPERTYHEATBALANCESOURCETERM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyHeatBalanceSourceTerm_Impl;
  }

  class EPMODEL_API SurfacePropertyHeatBalanceSourceTerm : public ModelObject
  {
   public:
    explicit SurfacePropertyHeatBalanceSourceTerm(const Model& model);

    virtual ~SurfacePropertyHeatBalanceSourceTerm() override = default;
    SurfacePropertyHeatBalanceSourceTerm(const SurfacePropertyHeatBalanceSourceTerm& other) = default;
    SurfacePropertyHeatBalanceSourceTerm(SurfacePropertyHeatBalanceSourceTerm&& other) = default;
    SurfacePropertyHeatBalanceSourceTerm& operator=(const SurfacePropertyHeatBalanceSourceTerm&) = default;
    SurfacePropertyHeatBalanceSourceTerm& operator=(SurfacePropertyHeatBalanceSourceTerm&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the IDD-derived SurfacePropertyHeatBalanceSourceTerm naming is preserved for
    //   this scalar-facing class.
    // - Field Mapping: Surface Name, Inside Face Heat Source Term Schedule Name, and Outside Face Heat Source Term Schedule Name
    //   are object-list references (SurfaceNames and ScheduleNames) and therefore excluded from scalar accessor generation.
    // - Field Mapping: Any additional scalar metadata is handled through the ModelObject base class when future parity demands it.
    // - TODO(parity): Introduce explicit surface/schedule helper APIs once relationship wiring matures.

   protected:
    using ImplType = detail::SurfacePropertyHeatBalanceSourceTerm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyHeatBalanceSourceTerm(std::shared_ptr<detail::SurfacePropertyHeatBalanceSourceTerm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
