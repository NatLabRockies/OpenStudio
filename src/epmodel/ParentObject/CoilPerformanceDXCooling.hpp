/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILPERFORMANCEDXCOOLING_HPP
#define EPMODEL_COILPERFORMANCEDXCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilPerformanceDXCooling_Impl;
  }

/** \brief Stores performance data for a curve-fit DX cooling coil.
 *
 * \par EnergyPlus object
 * \epobject{group-heating-and-cooling-coils.html#coilperformancedxcooling,CoilPerformance:DX:Cooling}
 *
 * \par Important behavior
 * Rated-capacity, airflow, condenser, fan-power, and performance-curve fields are stored directly on the object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::CoilPerformanceDXCooling</code>.
 * <b>Not yet available:</b> Model's performance-curve relationships, condenser-air-inlet node, autosizing and SQL-result helpers, and reverse navigation to the referencing DX coil are not exposed.
 *
 * \par Known limitations
 * The performance object does not own the DX coil or its operating-mode relationships.
 */
  class EPMODEL_API CoilPerformanceDXCooling : public ParentObject
  {
   public:
    explicit CoilPerformanceDXCooling(const Model& model);

    virtual ~CoilPerformanceDXCooling() override = default;
    CoilPerformanceDXCooling(const CoilPerformanceDXCooling& other) = default;
    CoilPerformanceDXCooling(CoilPerformanceDXCooling&& other) = default;
    CoilPerformanceDXCooling& operator=(const CoilPerformanceDXCooling&) = default;
    CoilPerformanceDXCooling& operator=(CoilPerformanceDXCooling&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();

    boost::optional<double> grossRatedTotalCoolingCapacity() const;
    bool isGrossRatedTotalCoolingCapacityAutosized() const;
    bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
    void autosizeGrossRatedTotalCoolingCapacity();

    boost::optional<double> grossRatedSensibleHeatRatio() const;
    bool isGrossRatedSensibleHeatRatioAutosized() const;
    bool setGrossRatedSensibleHeatRatio(double grossRatedSensibleHeatRatio);
    void autosizeGrossRatedSensibleHeatRatio();

    double grossRatedCoolingCOP() const;
    bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void autosizeRatedAirFlowRate();

    double fractionofAirFlowBypassedAroundCoil() const;
    bool setFractionofAirFlowBypassedAroundCoil(double fractionofAirFlowBypassedAroundCoil);

    double nominalTimeforCondensateRemovaltoBegin() const;
    bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
    bool
      setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    double evaporativeCondenserEffectiveness() const;
    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    boost::optional<double> evaporativeCondenserAirFlowRate() const;
    bool isEvaporativeCondenserAirFlowRateAutosized() const;
    bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
    void autosizeEvaporativeCondenserAirFlowRate();

    boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
    bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
    void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

   protected:
    using ImplType = detail::CoilPerformanceDXCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilPerformanceDXCooling(std::shared_ptr<detail::CoilPerformanceDXCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
