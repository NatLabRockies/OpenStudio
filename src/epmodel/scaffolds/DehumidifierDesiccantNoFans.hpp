/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEHUMIDIFIERDESICCANTNOFANS_HPP
#define EPMODEL_DEHUMIDIFIERDESICCANTNOFANS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DehumidifierDesiccantNoFans_Impl;
  }

  class EPMODEL_API DehumidifierDesiccantNoFans : public ModelObject
  {
   public:
    explicit DehumidifierDesiccantNoFans(const Model& model);

    virtual ~DehumidifierDesiccantNoFans() override = default;
    DehumidifierDesiccantNoFans(const DehumidifierDesiccantNoFans& other) = default;
    DehumidifierDesiccantNoFans(DehumidifierDesiccantNoFans&& other) = default;
    DehumidifierDesiccantNoFans& operator=(const DehumidifierDesiccantNoFans&) = default;
    DehumidifierDesiccantNoFans& operator=(DehumidifierDesiccantNoFans&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> regenerationCoilObjectTypeValues();
    static std::vector<std::string> regenerationFanObjectTypeValues();
    static std::vector<std::string> performanceModelTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to Dehumidifier:Desiccant:NoFans numeric/choice fields.
    // - Field Mapping: Availability schedule, node names, and linked object-list name fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
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

   protected:
    using ImplType = detail::DehumidifierDesiccantNoFans_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DehumidifierDesiccantNoFans(std::shared_ptr<detail::DehumidifierDesiccantNoFans_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
