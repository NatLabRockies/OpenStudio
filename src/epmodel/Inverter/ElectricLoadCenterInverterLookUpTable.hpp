/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterInverterLookUpTable_Impl;
  }

  /** \brief Represents an inverter whose efficiency is specified at several operating points.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#electricloadcenterinverterlookuptable,ElectricLoadCenter:Inverter:LookUpTable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ElectricLoadCenterInverterLookUpTable</code>.
   *
   * - <b>Not yet available:</b> <code>availabilitySchedule()</code>,
   *   <code>setAvailabilitySchedule(...)</code>, and
   *   <code>resetAvailabilitySchedule()</code>.
   * - <b>Not yet available:</b> The Model Inverter relationship methods
   *   <code>electricLoadCenterDistribution()</code>, <code>thermalZone()</code>,
   *   <code>setThermalZone(...)</code>, and <code>resetThermalZone()</code>.
   *
   * \par Known limitations
   * Assign schedule, zone, and electric-load-center relationships through
   * lower-level object references when needed.
   */
  class EPMODEL_API ElectricLoadCenterInverterLookUpTable : public ModelObject
  {
   public:
    explicit ElectricLoadCenterInverterLookUpTable(const Model& model);

    virtual ~ElectricLoadCenterInverterLookUpTable() override = default;
    ElectricLoadCenterInverterLookUpTable(const ElectricLoadCenterInverterLookUpTable& other) = default;
    ElectricLoadCenterInverterLookUpTable(ElectricLoadCenterInverterLookUpTable&& other) = default;
    ElectricLoadCenterInverterLookUpTable& operator=(const ElectricLoadCenterInverterLookUpTable&) = default;
    ElectricLoadCenterInverterLookUpTable& operator=(ElectricLoadCenterInverterLookUpTable&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> radiativeFraction() const;
    bool setRadiativeFraction(double radiativeFraction);
    void resetRadiativeFraction();

    boost::optional<double> ratedMaximumContinuousOutputPower() const;
    bool setRatedMaximumContinuousOutputPower(double ratedMaximumContinuousOutputPower);
    void resetRatedMaximumContinuousOutputPower();

    boost::optional<double> nightTareLossPower() const;
    bool setNightTareLossPower(double nightTareLossPower);
    void resetNightTareLossPower();

    boost::optional<double> nominalVoltageInput() const;
    bool setNominalVoltageInput(double nominalVoltageInput);
    void resetNominalVoltageInput();

    boost::optional<double> efficiencyAt10PowerAndNominalVoltage() const;
    bool setEfficiencyAt10PowerAndNominalVoltage(double efficiencyAt10PowerAndNominalVoltage);
    void resetEfficiencyAt10PowerAndNominalVoltage();

    boost::optional<double> efficiencyAt20PowerAndNominalVoltage() const;
    bool setEfficiencyAt20PowerAndNominalVoltage(double efficiencyAt20PowerAndNominalVoltage);
    void resetEfficiencyAt20PowerAndNominalVoltage();

    boost::optional<double> efficiencyAt30PowerAndNominalVoltage() const;
    bool setEfficiencyAt30PowerAndNominalVoltage(double efficiencyAt30PowerAndNominalVoltage);
    void resetEfficiencyAt30PowerAndNominalVoltage();

    boost::optional<double> efficiencyAt50PowerAndNominalVoltage() const;
    bool setEfficiencyAt50PowerAndNominalVoltage(double efficiencyAt50PowerAndNominalVoltage);
    void resetEfficiencyAt50PowerAndNominalVoltage();

    boost::optional<double> efficiencyAt75PowerAndNominalVoltage() const;
    bool setEfficiencyAt75PowerAndNominalVoltage(double efficiencyAt75PowerAndNominalVoltage);
    void resetEfficiencyAt75PowerAndNominalVoltage();

    boost::optional<double> efficiencyAt100PowerAndNominalVoltage() const;
    bool setEfficiencyAt100PowerAndNominalVoltage(double efficiencyAt100PowerAndNominalVoltage);
    void resetEfficiencyAt100PowerAndNominalVoltage();

   protected:
    using ImplType = detail::ElectricLoadCenterInverterLookUpTable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterInverterLookUpTable(std::shared_ptr<detail::ElectricLoadCenterInverterLookUpTable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
