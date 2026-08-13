/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPLENUM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACRETURNPLENUM_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Node;
  class ThermalZone;

  namespace detail {

    class ThermalZone_Impl;

    class EPMODEL_API AirLoopHVACReturnPlenum_Impl : public Mixer_Impl
    {
     public:
      using Mixer_Impl::Mixer_Impl;
      virtual ~AirLoopHVACReturnPlenum_Impl() override = default;

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone() const;
      bool setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void resetThermalZone();
      bool addToNode(openstudio::epmodel::Node& node) override;

      unsigned outletPort() const override;
      unsigned inletPort(unsigned branchIndex) const override;
      void removePortForBranch(unsigned branchIndex) override;
      bool setInletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) override;

     private:
      friend class ThermalZone_Impl;
      bool bindThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void clearThermalZoneConditioning();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
