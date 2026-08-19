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

  /** \brief Defines the performance and operating-mode relationships for a curve-fit DX cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-coil-cooling-dx.html#coilcoolingdxcurvefitperformance,Coil:Cooling:DX:CurveFit:Performance}.
   *
   * \par Important behavior
   * A newly created object and a loaded object with a blank basin-heater
   * schedule are assigned the model's always-on discrete schedule. A nonblank
   * unresolved schedule name is not guessed or replaced.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingDXCurveFitPerformance</code>.
   * EPModel also keeps a one-argument constructor for creating an initially
   * unlinked performance object. The Model reverse-navigation method
   * <code>coilCoolingDXs()</code> is not available.
   *
   * \par Known limitations
   * Reverse navigation to the DX coils that reference this performance object
   * is not available.
   */
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

    boost::optional<CoilCoolingDXCurveFitOperatingMode> alternativeOperatingMode1() const;
    bool setAlternativeOperatingMode1(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode1);
    void resetAlternativeOperatingMode1();

    boost::optional<CoilCoolingDXCurveFitOperatingMode> alternativeOperatingMode2() const;
    bool setAlternativeOperatingMode2(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode2);
    void resetAlternativeOperatingMode2();

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
