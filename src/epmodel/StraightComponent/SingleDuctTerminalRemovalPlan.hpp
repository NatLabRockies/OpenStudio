/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SINGLEDUCTTERMINALREMOVALPLAN_HPP
#define EPMODEL_SINGLEDUCTTERMINALREMOVALPLAN_HPP

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {
  class StraightComponent;

  namespace detail {

    // Preflights the common external topology for one childless single-duct
    // terminal removal. After prepare(), commit() contains only invariant
    // mutations and cannot report a partially completed teardown.
    class SingleDuctTerminalRemovalPlan
    {
     public:
      static std::unique_ptr<SingleDuctTerminalRemovalPlan> prepare(StraightComponent& terminal);

      SingleDuctTerminalRemovalPlan(const SingleDuctTerminalRemovalPlan&) = delete;
      SingleDuctTerminalRemovalPlan& operator=(const SingleDuctTerminalRemovalPlan&) = delete;
      SingleDuctTerminalRemovalPlan(SingleDuctTerminalRemovalPlan&&) = delete;
      SingleDuctTerminalRemovalPlan& operator=(SingleDuctTerminalRemovalPlan&&) = delete;

      void commit();

     private:
      SingleDuctTerminalRemovalPlan(ModelObject terminal, unsigned inletPort, unsigned outletPort,
                                    std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation,
                                    boost::optional<ModelObject> inletNode, boost::optional<ModelObject> outletNode,
                                    boost::optional<ModelObject> equipmentList, boost::optional<ModelObject> airDistributionUnit);

      ModelObject m_terminal;
      unsigned m_inletPort;
      unsigned m_outletPort;
      std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> m_branchReservation;
      boost::optional<ModelObject> m_inletNode;
      boost::optional<ModelObject> m_outletNode;
      boost::optional<ModelObject> m_equipmentList;
      boost::optional<ModelObject> m_airDistributionUnit;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
