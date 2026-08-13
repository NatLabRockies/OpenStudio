/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPLENUM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPLENUM_IMPL_HPP

#include "Splitter/Splitter_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Node;
  class ThermalZone;
  class AirLoopHVAC;

  namespace detail {

    class EPMODEL_API AirLoopHVACSupplyPlenum_Impl : public Splitter_Impl
    {
     public:
      using Splitter_Impl::Splitter_Impl;
      virtual ~AirLoopHVACSupplyPlenum_Impl() override = default;

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone() const;
      bool setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      bool bindThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void clearThermalZoneConditioning();
      void resetThermalZone();
      bool addToNode(openstudio::epmodel::Node& node) override;
      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const override;

      unsigned inletPort() const override;
      unsigned outletPort(unsigned branchIndex) const override;
      void removePortForBranch(unsigned branchIndex) override;
      bool setInletModelObject(const openstudio::epmodel::ModelObject& modelObject);
      void resetInletModelObject();
      bool setOutletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
