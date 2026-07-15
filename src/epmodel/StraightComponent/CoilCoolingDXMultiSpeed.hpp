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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar DX-coil surface plus the current epmodel schedule / crankcase-curve relationship slice and
    //   supply-side air-loop insertion path are present, while stage-data, AFN, and tank-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXMultiSpeed.
    // - Implemented Parity: The scalar condenser, fuel, basin-heater, and compressor/capacity helpers preserve the canonical naming, defaults,
    //   and autosize behavior; `availabilitySchedule`, `basinHeaterOperatingSchedule`, and
    //   `crankcaseHeaterCapacityFunctionofTemperatureCurve` preserve the bounded relationship slice; `addToNode` preserves the current epmodel
    //   supply-side air-loop insertion path.
    // - Documented Delta: Stage data, AFN, tank-link helpers, and broader node-link topology from canonical `openstudio::model::CoilCoolingDXMultiSpeed`
    //   are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and the bounded relationship slice map directly to EnergyPlus `Coil:Cooling:DX:MultiSpeed` fields.
    // - Evidence: `src/model/CoilCoolingDXMultiSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXMultiSpeed.cpp`, and `src/epmodel/test/CoilCoolingDXMultiSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add stage-data, AFN, tank-link, and broader topology helpers without changing the preserved scalar signatures.
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
