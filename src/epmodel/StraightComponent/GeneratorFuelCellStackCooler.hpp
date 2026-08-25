/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLSTACKCOOLER_HPP
#define EPMODEL_GENERATORFUELCELLSTACKCOOLER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class GeneratorFuelCell;
  class Node;

  namespace detail {
    class GeneratorFuelCellStackCooler_Impl;
  }

/** \brief A fuel-cell stack cooler.
 *
 * \par EnergyPlus object
 * \epobject{group-electric-load-center-generator.html#generatorfuelcellstackcooler,Generator:FuelCell:StackCooler}
 *
 * \par Important behavior
 * The scalar fields and plant-side topology map directly to the EnergyPlus generator object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::GeneratorFuelCellStackCooler</code>.
 *
 * \par Known limitations
 * Fuel-cell generator ownership and broader generator-system relationships are not exposed here.
 */
  class EPMODEL_API GeneratorFuelCellStackCooler : public StraightComponent
  {
   public:
    explicit GeneratorFuelCellStackCooler(const Model& model);

    virtual ~GeneratorFuelCellStackCooler() override = default;
    GeneratorFuelCellStackCooler(const GeneratorFuelCellStackCooler& other) = default;
    GeneratorFuelCellStackCooler(GeneratorFuelCellStackCooler&& other) = default;
    GeneratorFuelCellStackCooler& operator=(const GeneratorFuelCellStackCooler&) = default;
    GeneratorFuelCellStackCooler& operator=(GeneratorFuelCellStackCooler&&) = default;

    static IddObjectType iddObjectType();

    double nominalStackTemperature() const;
    bool setNominalStackTemperature(double nominalStackTemperature);
    void resetNominalStackTemperature();

    double actualStackTemperature() const;
    bool setActualStackTemperature(double actualStackTemperature);
    void resetActualStackTemperature();

    double coefficientr0() const;
    bool setCoefficientr0(double coefficientr0);
    void resetCoefficientr0();

    double coefficientr1() const;
    bool setCoefficientr1(double coefficientr1);
    void resetCoefficientr1();

    double coefficientr2() const;
    bool setCoefficientr2(double coefficientr2);
    void resetCoefficientr2();

    double coefficientr3() const;
    bool setCoefficientr3(double coefficientr3);
    void resetCoefficientr3();

    double stackCoolantFlowRate() const;
    bool setStackCoolantFlowRate(double stackCoolantFlowRate);
    void resetStackCoolantFlowRate();

    double stackCoolerUFactorTimesAreaValue() const;
    bool setStackCoolerUFactorTimesAreaValue(double stackCoolerUFactorTimesAreaValue);
    void resetStackCoolerUFactorTimesAreaValue();

    double fscogenAdjustmentFactor() const;
    bool setFscogenAdjustmentFactor(double fscogenAdjustmentFactor);
    void resetFscogenAdjustmentFactor();

    double stackCogenerationExchangerArea() const;
    bool setStackCogenerationExchangerArea(double stackCogenerationExchangerArea);
    void resetStackCogenerationExchangerArea();

    double stackCogenerationExchangerNominalFlowRate() const;
    bool setStackCogenerationExchangerNominalFlowRate(double stackCogenerationExchangerNominalFlowRate);
    void resetStackCogenerationExchangerNominalFlowRate();

    double stackCogenerationExchangerNominalHeatTransferCoefficient() const;
    bool setStackCogenerationExchangerNominalHeatTransferCoefficient(double stackCogenerationExchangerNominalHeatTransferCoefficient);
    void resetStackCogenerationExchangerNominalHeatTransferCoefficient();

    double stackCogenerationExchangerNominalHeatTransferCoefficientExponent() const;
    bool setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(double stackCogenerationExchangerNominalHeatTransferCoefficientExponent);
    void resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent();

    double stackCoolerPumpPower() const;
    bool setStackCoolerPumpPower(double stackCoolerPumpPower);
    void resetStackCoolerPumpPower();

    double stackCoolerPumpHeatLossFraction() const;
    bool setStackCoolerPumpHeatLossFraction(double stackCoolerPumpHeatLossFraction);
    void resetStackCoolerPumpHeatLossFraction();

    double stackAirCoolerFanCoefficientf0() const;
    bool setStackAirCoolerFanCoefficientf0(double stackAirCoolerFanCoefficientf0);
    void resetStackAirCoolerFanCoefficientf0();

    double stackAirCoolerFanCoefficientf1() const;
    bool setStackAirCoolerFanCoefficientf1(double stackAirCoolerFanCoefficientf1);
    void resetStackAirCoolerFanCoefficientf1();

    double stackAirCoolerFanCoefficientf2() const;
    bool setStackAirCoolerFanCoefficientf2(double stackAirCoolerFanCoefficientf2);
    void resetStackAirCoolerFanCoefficientf2();

    boost::optional<GeneratorFuelCell> fuelCell() const;

   protected:
    using ImplType = detail::GeneratorFuelCellStackCooler_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellStackCooler(std::shared_ptr<detail::GeneratorFuelCellStackCooler_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
