/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_HPP
#define EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;
  class CoilPerformanceDXCooling;

  namespace detail {
    class CoilCoolingDXTwoStageWithHumidityControlMode_Impl;
  }

  /** \brief Represents a two-stage DX cooling coil with humidity-control mode.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxtwostagewithhumiditycontrolmode,Coil:Cooling:DX:TwoStageWithHumidityControlMode}.
   *
   * \par Important behavior
   * The persisted scalar and currently supported schedule, curve, and node relationships map directly to the EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDXTwoStageWithHumidityControlMode</code>.
   * Not yet available: broader AirflowNetwork, tank-link, and higher-level topology conveniences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilCoolingDXTwoStageWithHumidityControlMode : public StraightComponent
  {
   public:
    explicit CoilCoolingDXTwoStageWithHumidityControlMode(const Model& model);

    virtual ~CoilCoolingDXTwoStageWithHumidityControlMode() override = default;
    CoilCoolingDXTwoStageWithHumidityControlMode(const CoilCoolingDXTwoStageWithHumidityControlMode& other) = default;
    CoilCoolingDXTwoStageWithHumidityControlMode(CoilCoolingDXTwoStageWithHumidityControlMode&& other) = default;
    CoilCoolingDXTwoStageWithHumidityControlMode& operator=(const CoilCoolingDXTwoStageWithHumidityControlMode&) = default;
    CoilCoolingDXTwoStageWithHumidityControlMode& operator=(CoilCoolingDXTwoStageWithHumidityControlMode&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

    int numberofCapacityStages() const;
    bool setNumberofCapacityStages(int numberofCapacityStages);

    int numberofEnhancedDehumidificationModes() const;
    bool setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes);

    boost::optional<CoilPerformanceDXCooling> normalModeStage1CoilPerformance() const;
    bool setNormalModeStage1CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
    void resetNormalModeStage1CoilPerformance();

    boost::optional<CoilPerformanceDXCooling> normalModeStage1Plus2CoilPerformance() const;
    bool setNormalModeStage1Plus2CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
    void resetNormalModeStage1Plus2CoilPerformance();

    boost::optional<CoilPerformanceDXCooling> dehumidificationMode1Stage1CoilPerformance() const;
    bool setDehumidificationMode1Stage1CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
    void resetDehumidificationMode1Stage1CoilPerformance();

    boost::optional<CoilPerformanceDXCooling> dehumidificationMode1Stage1Plus2CoilPerformance() const;
    bool setDehumidificationMode1Stage1Plus2CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
    void resetDehumidificationMode1Stage1Plus2CoilPerformance();

    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& schedule);
    void resetBasinHeaterOperatingSchedule();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXTwoStageWithHumidityControlMode(std::shared_ptr<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
