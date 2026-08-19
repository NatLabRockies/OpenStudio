/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXMULTISPEED_HPP
#define EPMODEL_COILCOOLINGDXMULTISPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXMultiSpeed_Impl;
  }

  /** \brief Represents a multispeed direct-expansion cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxmultispeed,Coil:Cooling:DX:MultiSpeed}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported stage-control relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDXMultiSpeed</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code>. <b>Not yet available:</b> the Model stage-data ownership and extensible stage-list methods such as <code>addStage()</code>, <code>setStages()</code>, and <code>removeStage()</code>.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilCoolingDXMultiSpeed : public StraightComponent
  {
   public:
    explicit CoilCoolingDXMultiSpeed(const Model& model);

    virtual ~CoilCoolingDXMultiSpeed() override = default;
    CoilCoolingDXMultiSpeed(const CoilCoolingDXMultiSpeed& other) = default;
    CoilCoolingDXMultiSpeed(CoilCoolingDXMultiSpeed&& other) = default;
    CoilCoolingDXMultiSpeed& operator=(const CoilCoolingDXMultiSpeed&) = default;
    CoilCoolingDXMultiSpeed& operator=(CoilCoolingDXMultiSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> fuelTypeValues();

    bool addToNode(Node& node);

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

   protected:
    using ImplType = detail::CoilCoolingDXMultiSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXMultiSpeed(std::shared_ptr<detail::CoilCoolingDXMultiSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
