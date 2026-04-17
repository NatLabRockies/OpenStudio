/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCOMPRESSORRACK_IMPL_HPP
#define EPMODEL_REFRIGERATIONCOMPRESSORRACK_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API RefrigerationCompressorRack_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~RefrigerationCompressorRack_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      std::string heatRejectionLocation() const;
      bool setHeatRejectionLocation(const std::string& heatRejectionLocation);

      double designCompressorRackCOP() const;
      bool setDesignCompressorRackCOP(double designCompressorRackCOP);

      Curve compressorRackCOPFunctionofTemperatureCurve() const;
      bool setCompressorRackCOPFunctionofTemperatureCurve(const Curve& curve);

      double designCondenserFanPower() const;
      bool setDesignCondenserFanPower(double designCondenserFanPower);

      boost::optional<Curve> condenserFanPowerFunctionofTemperatureCurve() const;
      bool setCondenserFanPowerFunctionofTemperatureCurve(const Curve& curve);
      void resetCondenserFanPowerFunctionofTemperatureCurve();

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      std::string waterCooledLoopFlowType() const;
      bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);

      boost::optional<Schedule> waterCooledCondenserOutletTemperatureSchedule() const;
      bool setWaterCooledCondenserOutletTemperatureSchedule(Schedule& schedule);
      void resetWaterCooledCondenserOutletTemperatureSchedule();

      boost::optional<double> waterCooledCondenserDesignFlowRate() const;
      bool setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate);
      void resetWaterCooledCondenserDesignFlowRate();

      boost::optional<double> waterCooledCondenserMaximumFlowRate() const;
      bool setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate);
      void resetWaterCooledCondenserMaximumFlowRate();

      double waterCooledCondenserMaximumWaterOutletTemperature() const;
      bool setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature);

      double waterCooledCondenserMinimumWaterInletTemperature() const;
      bool setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature);

      boost::optional<Schedule> evaporativeCondenserAvailabilitySchedule() const;
      bool setEvaporativeCondenserAvailabilitySchedule(Schedule& schedule);
      void resetEvaporativeCondenserAvailabilitySchedule();

      double evaporativeCondenserEffectiveness() const;
      bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

      boost::optional<double> evaporativeCondenserAirFlowRate() const;
      bool isEvaporativeCondenserAirFlowRateAutocalculated() const;
      bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
      bool autocalculateEvaporativeCondenserAirFlowRate();

      double basinHeaterCapacity() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);

      double basinHeaterSetpointTemperature() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

      boost::optional<double> designEvaporativeCondenserWaterPumpPower() const;
      bool isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const;
      bool setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower);
      bool autocalculateDesignEvaporativeCondenserWaterPumpPower();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      boost::optional<ThermalZone> heatRejectionZone() const;
      bool setHeatRejectionZone(const ThermalZone& thermalZone);
      void resetHeatRejectionZone();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
