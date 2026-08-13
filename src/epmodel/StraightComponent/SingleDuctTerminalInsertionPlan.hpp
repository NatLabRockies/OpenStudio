/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SINGLEDUCTTERMINALINSERTIONPLAN_HPP
#define EPMODEL_SINGLEDUCTTERMINALINSERTIONPLAN_HPP

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {
  class Node;
  class StraightComponent;

  namespace detail {

    // Owns the common external topology for one single-duct terminal
    // insertion. Terminal-specific contained equipment is prepared by the
    // caller between apply() and commit().
    class SingleDuctTerminalInsertionPlan
    {
     public:
      static std::unique_ptr<SingleDuctTerminalInsertionPlan> prepare(StraightComponent& terminal, Node& outletNode);

      SingleDuctTerminalInsertionPlan(const SingleDuctTerminalInsertionPlan&) = delete;
      SingleDuctTerminalInsertionPlan& operator=(const SingleDuctTerminalInsertionPlan&) = delete;
      SingleDuctTerminalInsertionPlan(SingleDuctTerminalInsertionPlan&&) = delete;
      SingleDuctTerminalInsertionPlan& operator=(SingleDuctTerminalInsertionPlan&&) = delete;
      ~SingleDuctTerminalInsertionPlan();

      bool apply(bool failAfterAirDistributionUnitUpdate = false);
      bool commit();

     private:
      SingleDuctTerminalInsertionPlan(ModelObject terminal, std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation,
                                      ModelObject outletNode, ModelObject inletNode, bool createdInletNode, unsigned inletPort, unsigned outletPort,
                                      boost::optional<ModelObject> airDistributionUnit, boost::optional<ModelObject> equipmentList,
                                      boost::optional<ModelObject> previousAirDistributionUnitOutletTarget,
                                      boost::optional<std::string> previousAirDistributionUnitOutletNodeName);

      bool setTerminalPointer(unsigned fieldIndex, const Handle& targetHandle);
      void rollback();

      ModelObject m_terminal;
      std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> m_branchReservation;
      ModelObject m_outletNode;
      ModelObject m_inletNode;
      unsigned m_inletPort;
      unsigned m_outletPort;
      boost::optional<ModelObject> m_airDistributionUnit;
      boost::optional<ModelObject> m_equipmentList;
      boost::optional<ModelObject> m_previousAirDistributionUnitOutletTarget;
      boost::optional<std::string> m_previousAirDistributionUnitOutletNodeName;
      bool m_createdInletNode = false;
      bool m_applyAttempted = false;
      bool m_applySucceeded = false;
      bool m_inletAssignmentAttempted = false;
      bool m_outletAssignmentAttempted = false;
      bool m_airDistributionUnitUpdateAttempted = false;
      bool m_zoneRegistered = false;
      bool m_committed = false;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
