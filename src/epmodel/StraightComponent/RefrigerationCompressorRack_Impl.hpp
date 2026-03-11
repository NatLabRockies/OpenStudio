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
  namespace detail {

    class EPMODEL_API RefrigerationCompressorRack_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~RefrigerationCompressorRack_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::string heatRejectionLocation() const;
      double designCompressorRackCOP() const;
      double designCondenserFanPower() const;

      std::string condenserType() const;
      std::string waterCooledLoopFlowType() const;

      boost::optional<double> waterCooledCondenserDesignFlowRate() const;
      boost::optional<double> waterCooledCondenserMaximumFlowRate() const;
      double waterCooledCondenserMaximumWaterOutletTemperature() const;
      double waterCooledCondenserMinimumWaterInletTemperature() const;

      double evaporativeCondenserEffectiveness() const;
      boost::optional<double> evaporativeCondenserAirFlowRate() const;
      bool isEvaporativeCondenserAirFlowRateAutocalculated() const;

      double basinHeaterCapacity() const;
      double basinHeaterSetpointTemperature() const;

      boost::optional<double> designEvaporativeCondenserWaterPumpPower() const;
      bool isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const;

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;

      bool setHeatRejectionLocation(const std::string& heatRejectionLocation);
      bool setDesignCompressorRackCOP(double designCompressorRackCOP);
      bool setDesignCondenserFanPower(double designCondenserFanPower);
      bool setCondenserType(const std::string& condenserType);
      bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);

      bool setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate);
      void resetWaterCooledCondenserDesignFlowRate();

      bool setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate);
      void resetWaterCooledCondenserMaximumFlowRate();

      bool setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature);
      bool setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature);
      bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);
      bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
      bool autocalculateEvaporativeCondenserAirFlowRate();

      bool setBasinHeaterCapacity(double basinHeaterCapacity);
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

      bool setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower);
      bool autocalculateDesignEvaporativeCondenserWaterPumpPower();

      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
