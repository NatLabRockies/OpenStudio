/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class CoilCoolingDXCurveFitSpeed;
  class Model;

  namespace detail {
    class CoilCoolingDXCurveFitOperatingMode_Impl;
  }

  class EPMODEL_API CoilCoolingDXCurveFitOperatingMode : public ModelObject
  {
   public:
    explicit CoilCoolingDXCurveFitOperatingMode(const Model& model);

    virtual ~CoilCoolingDXCurveFitOperatingMode() override = default;
    CoilCoolingDXCurveFitOperatingMode(const CoilCoolingDXCurveFitOperatingMode& other) = default;
    CoilCoolingDXCurveFitOperatingMode(CoilCoolingDXCurveFitOperatingMode&& other) = default;
    CoilCoolingDXCurveFitOperatingMode& operator=(const CoilCoolingDXCurveFitOperatingMode&) = default;
    CoilCoolingDXCurveFitOperatingMode& operator=(CoilCoolingDXCurveFitOperatingMode&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXCurveFitOperatingMode.
    // - Implemented Parity: Canonical constructor defaults, scalar fields, and ordered speed lookup, insertion, reordering, replacement, and
    //   removal use the canonical public signatures. Invalid cross-model speed mutations leave the stored list unchanged.
    // - Field/Storage Mapping: Scalar values and ordered `CoilCoolingDXCurveFitSpeed` relationships map directly to
    //   `Coil:Cooling:DX:CurveFit:OperatingMode` fields and extensible speed-name rows.
    // - Evidence: `src/model/CoilCoolingDXCurveFitOperatingMode.hpp` and
    //   `src/epmodel/test/CoilCoolingDXCurveFitOperatingMode_GTest.cpp`.
    // - Remaining Parity Work: Add performance reverse navigation, sizing-result helpers, clone/removal equivalence, and broader scripting
    //   evidence outside the curve-fit air-loop workflow.
    boost::optional<double> ratedGrossTotalCoolingCapacity() const;
    bool isRatedGrossTotalCoolingCapacityAutosized() const;
    bool setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity);
    void autosizeRatedGrossTotalCoolingCapacity();

    boost::optional<double> ratedEvaporatorAirFlowRate() const;
    bool isRatedEvaporatorAirFlowRateAutosized() const;
    bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
    void autosizeRatedEvaporatorAirFlowRate();

    boost::optional<double> ratedCondenserAirFlowRate() const;
    bool isRatedCondenserAirFlowRateAutosized() const;
    bool setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate);
    void autosizeRatedCondenserAirFlowRate();

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
    bool
      setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    double nominalTimeforCondensateRemovaltoBegin() const;
    bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

    bool applyLatentDegradationtoSpeedsGreaterthan1() const;
    bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    boost::optional<double> nominalEvaporativeCondenserPumpPower() const;
    bool isNominalEvaporativeCondenserPumpPowerAutosized() const;
    bool setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower);
    void autosizeNominalEvaporativeCondenserPumpPower();

    unsigned nominalSpeedNumber() const;
    bool isNominalSpeedNumberDefaulted() const;
    bool setNominalSpeedNumber(unsigned nominalSpeedNumber);
    void resetNominalSpeedNumber();

    std::vector<CoilCoolingDXCurveFitSpeed> speeds() const;
    unsigned numberOfSpeeds() const;
    boost::optional<unsigned> speedIndex(const CoilCoolingDXCurveFitSpeed& speed) const;
    bool addSpeed(const CoilCoolingDXCurveFitSpeed& speed);
    bool addSpeed(const CoilCoolingDXCurveFitSpeed& speed, unsigned index);
    bool setSpeedIndex(const CoilCoolingDXCurveFitSpeed& speed, unsigned index);
    bool setSpeeds(const std::vector<CoilCoolingDXCurveFitSpeed>& speeds);
    void removeAllSpeeds();
    bool removeSpeed(const CoilCoolingDXCurveFitSpeed& speed);
    bool removeSpeed(unsigned index);

   protected:
    using ImplType = detail::CoilCoolingDXCurveFitOperatingMode_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXCurveFitOperatingMode(std::shared_ptr<detail::CoilCoolingDXCurveFitOperatingMode_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
