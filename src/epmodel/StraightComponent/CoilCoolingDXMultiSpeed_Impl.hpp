/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXMULTISPEED_IMPL_HPP
#define EPMODEL_COILCOOLINGDXMULTISPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;
  class Schedule;
  class Curve;

  namespace detail {

    class EPMODEL_API CoilCoolingDXMultiSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDXMultiSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
      bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
      void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

      boost::optional<Schedule> basinHeaterOperatingSchedule() const;
      bool setBasinHeaterOperatingSchedule(Schedule& schedule);
      void resetBasinHeaterOperatingSchedule();

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      bool applyPartLoadFractiontoSpeedsGreaterthan1() const;
      bool setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1);

      bool applyLatentDegradationtoSpeedsGreaterthan1() const;
      bool isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted() const;
      bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);
      void resetApplyLatentDegradationtoSpeedsGreaterthan1();

      double crankcaseHeaterCapacity() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
      bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

      double basinHeaterCapacity() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);

      double basinHeaterSetpointTemperature() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

      std::string fuelType() const;
      bool setFuelType(const std::string& fuelType);

      double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
      bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
