/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEHUMIDIFIERDESICCANTNOFANS_IMPL_HPP
#define EPMODEL_DEHUMIDIFIERDESICCANTNOFANS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DehumidifierDesiccantNoFans_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DehumidifierDesiccantNoFans_Impl() override = default;

      boost::optional<std::string> controlType() const;
      bool setControlType(const std::string& controlType);
      void resetControlType();

      boost::optional<double> leavingMaximumHumidityRatioSetpoint() const;
      bool setLeavingMaximumHumidityRatioSetpoint(double leavingMaximumHumidityRatioSetpoint);
      void resetLeavingMaximumHumidityRatioSetpoint();

      boost::optional<double> nominalProcessAirFlowRate() const;
      bool setNominalProcessAirFlowRate(double nominalProcessAirFlowRate);
      void resetNominalProcessAirFlowRate();

      boost::optional<double> nominalProcessAirVelocity() const;
      bool setNominalProcessAirVelocity(double nominalProcessAirVelocity);
      void resetNominalProcessAirVelocity();

      boost::optional<double> rotorPower() const;
      bool setRotorPower(double rotorPower);
      void resetRotorPower();

      boost::optional<std::string> regenerationCoilObjectType() const;
      bool setRegenerationCoilObjectType(const std::string& regenerationCoilObjectType);
      void resetRegenerationCoilObjectType();

      boost::optional<std::string> regenerationFanObjectType() const;
      bool setRegenerationFanObjectType(const std::string& regenerationFanObjectType);
      void resetRegenerationFanObjectType();

      boost::optional<std::string> performanceModelType() const;
      bool setPerformanceModelType(const std::string& performanceModelType);
      void resetPerformanceModelType();

      boost::optional<double> nominalRegenerationTemperature() const;
      bool setNominalRegenerationTemperature(double nominalRegenerationTemperature);
      void resetNominalRegenerationTemperature();

      std::vector<std::string> controlTypeValues() const;
      std::vector<std::string> regenerationCoilObjectTypeValues() const;
      std::vector<std::string> regenerationFanObjectTypeValues() const;
      std::vector<std::string> performanceModelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
