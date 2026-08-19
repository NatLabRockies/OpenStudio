/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORWINDTURBINE_HPP
#define EPMODEL_GENERATORWINDTURBINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorWindTurbine_Impl;
  }

  /** \brief Represents a wind-turbine generator.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorwindturbine,Generator:WindTurbine}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::GeneratorWindTurbine</code>.
   *
   * - <b>Not yet available:</b> <code>setAvailabilitySchedule(...)</code> and
   *   the inherited <code>availabilitySchedule()</code> getter.
   * - <b>Added:</b> <code>rotorTypeValues()</code> and
   *   <code>powerControlValues()</code> expose the valid EnergyPlus choice keys.
   * - <b>Not yet available:</b> The Model Generator metadata methods
   *   <code>generatorObjectType()</code>, <code>ratedElectricPowerOutput()</code>,
   *   <code>ratedThermaltoElectricalPowerRatio()</code>, and
   *   <code>electricLoadCenterDistribution()</code>.
   *
   * \par Known limitations
   * If availability scheduling is needed, assign it through a lower-level
   * object reference; the turbine-performance scalar fields are available.
   */
  class EPMODEL_API GeneratorWindTurbine : public ModelObject
  {
   public:
    explicit GeneratorWindTurbine(const Model& model);

    virtual ~GeneratorWindTurbine() override = default;
    GeneratorWindTurbine(const GeneratorWindTurbine& other) = default;
    GeneratorWindTurbine(GeneratorWindTurbine&& other) = default;
    GeneratorWindTurbine& operator=(const GeneratorWindTurbine&) = default;
    GeneratorWindTurbine& operator=(GeneratorWindTurbine&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> rotorTypeValues();
    static std::vector<std::string> powerControlValues();

    std::string rotorType() const;
    bool setRotorType(const std::string& rotorType);

    std::string powerControl() const;
    bool setPowerControl(const std::string& powerControl);

    double ratedRotorSpeed() const;
    bool setRatedRotorSpeed(double ratedRotorSpeed);

    double rotorDiameter() const;
    bool setRotorDiameter(double rotorDiameter);

    double overallHeight() const;
    bool setOverallHeight(double overallHeight);

    int numberofBlades() const;
    bool setNumberofBlades(int numberofBlades);

    double ratedPower() const;
    bool setRatedPower(double ratedPower);

    double ratedWindSpeed() const;
    bool setRatedWindSpeed(double ratedWindSpeed);

    double cutInWindSpeed() const;
    bool setCutInWindSpeed(double cutInWindSpeed);

    double cutOutWindSpeed() const;
    bool setCutOutWindSpeed(double cutOutWindSpeed);

    double fractionSystemEfficiency() const;
    bool setFractionSystemEfficiency(double fractionSystemEfficiency);

    double maximumTipSpeedRatio() const;
    bool setMaximumTipSpeedRatio(double maximumTipSpeedRatio);

    double maximumPowerCoefficient() const;
    bool setMaximumPowerCoefficient(double maximumPowerCoefficient);

    boost::optional<double> annualLocalAverageWindSpeed() const;
    bool setAnnualLocalAverageWindSpeed(double annualLocalAverageWindSpeed);
    void resetAnnualLocalAverageWindSpeed();

    double heightforLocalAverageWindSpeed() const;
    bool setHeightforLocalAverageWindSpeed(double heightforLocalAverageWindSpeed);

    double bladeChordArea() const;
    bool setBladeChordArea(double bladeChordArea);

    double bladeDragCoefficient() const;
    bool setBladeDragCoefficient(double bladeDragCoefficient);

    double bladeLiftCoefficient() const;
    bool setBladeLiftCoefficient(double bladeLiftCoefficient);

    double powerCoefficientC1() const;
    bool setPowerCoefficientC1(double powerCoefficientC1);

    double powerCoefficientC2() const;
    bool setPowerCoefficientC2(double powerCoefficientC2);

    double powerCoefficientC3() const;
    bool setPowerCoefficientC3(double powerCoefficientC3);

    double powerCoefficientC4() const;
    bool setPowerCoefficientC4(double powerCoefficientC4);

    double powerCoefficientC5() const;
    bool setPowerCoefficientC5(double powerCoefficientC5);

    double powerCoefficientC6() const;
    bool setPowerCoefficientC6(double powerCoefficientC6);

   protected:
    using ImplType = detail::GeneratorWindTurbine_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorWindTurbine(std::shared_ptr<detail::GeneratorWindTurbine_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
