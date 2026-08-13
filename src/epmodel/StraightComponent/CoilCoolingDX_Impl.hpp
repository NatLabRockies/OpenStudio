/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDX_IMPL_HPP
#define EPMODEL_COILCOOLINGDX_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class CoilSystemCoolingDX;
  class Schedule;
  class ThermalZone;
  class CoilCoolingDXCurveFitPerformance;
  class Node;

  namespace detail {

    class EPMODEL_API CoilCoolingDX_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDX_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      bool removeFromLoop() override;
      void disconnect() override;
      std::vector<IdfObject> remove() override;
      std::vector<ModelObject> children() const override;
      boost::optional<CoilSystemCoolingDX> coilSystemCoolingDX() const;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<ThermalZone> condenserZone() const;
      bool setCondenserZone(const ThermalZone& thermalZone);
      void resetCondenserZone();

      CoilCoolingDXCurveFitPerformance performanceObject() const;
      bool setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance);

      std::string condenserInletNodeName() const;
      bool setCondenserInletNodeName(const std::string& condenserInletNodeName);

      std::string condenserOutletNodeName() const;
      bool setCondenserOutletNodeName(const std::string& condenserOutletNodeName);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
