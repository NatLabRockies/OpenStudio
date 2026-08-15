/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class CoilCoolingDXCurveFitOperatingMode;
  class Curve;
  class Model;
  class Schedule;

  namespace detail {
    class CoilCoolingDXCurveFitPerformance_Impl;
  }

  class EPMODEL_API CoilCoolingDXCurveFitPerformance : public ModelObject
  {
   public:
    explicit CoilCoolingDXCurveFitPerformance(const Model& model);
    explicit CoilCoolingDXCurveFitPerformance(const Model& model, const CoilCoolingDXCurveFitOperatingMode& baseOperatingMode);

    virtual ~CoilCoolingDXCurveFitPerformance() override = default;
    CoilCoolingDXCurveFitPerformance(const CoilCoolingDXCurveFitPerformance& other) = default;
    CoilCoolingDXCurveFitPerformance(CoilCoolingDXCurveFitPerformance&& other) = default;
    CoilCoolingDXCurveFitPerformance& operator=(const CoilCoolingDXCurveFitPerformance&) = default;
    CoilCoolingDXCurveFitPerformance& operator=(CoilCoolingDXCurveFitPerformance&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> capacityControlMethodValues();
    static std::vector<std::string> compressorFuelTypeValues();
    static std::vector<std::string> validCapacityControlMethodValues();
    static std::vector<std::string> validCompressorFuelTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXCurveFitPerformance.
    // - Implemented Parity: Scalar fields, the required base operating mode, the optional crankcase-heater temperature curve, and the required
    //   evaporative-condenser basin-heater schedule preserve their canonical public API and configured EnergyPlus relationship constraints.
    // - Documented Delta: The existing one-argument constructor remains available for internal/default EPModel construction.
    // - Field/Storage Mapping: Scalars and relationships map directly to `Coil:Cooling:DX:CurveFit:Performance` fields; constructors and
    //   blank-only load repair attach the always-on basin-heater schedule without changing unresolved nonblank imports.
    // - Evidence: `src/model/CoilCoolingDXCurveFitPerformance.hpp` and
    //   `src/epmodel/test/CoilCoolingDXCurveFitPerformance_GTest.cpp`.
    // - Remaining Parity Work: Add optional operating modes, reverse navigation, and removal/clone equivalence.
    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

    double unitInternalStaticAirPressure() const;
    bool setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure);

    std::string capacityControlMethod() const;
    bool setCapacityControlMethod(const std::string& capacityControlMethod);

    double evaporativeCondenserBasinHeaterCapacity() const;
    bool setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity);

    double evaporativeCondenserBasinHeaterSetpointTemperature() const;
    bool setEvaporativeCondenserBasinHeaterSetpointTemperature(double evaporativeCondenserBasinHeaterSetpointTemperature);

    Schedule evaporativeCondenserBasinHeaterOperatingSchedule() const;
    bool setEvaporativeCondenserBasinHeaterOperatingSchedule(Schedule& schedule);

    std::string compressorFuelType() const;
    bool setCompressorFuelType(const std::string& compressorFuelType);

    CoilCoolingDXCurveFitOperatingMode baseOperatingMode() const;
    bool setBaseOperatingMode(const CoilCoolingDXCurveFitOperatingMode& baseOperatingMode);

   protected:
    using ImplType = detail::CoilCoolingDXCurveFitPerformance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXCurveFitPerformance(std::shared_ptr<detail::CoilCoolingDXCurveFitPerformance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
