/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterInverterSimple_Impl;
  }

  /** \brief Represents a simple inverter with scalar efficiency and heat-gain fields.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#electricloadcenterinvertersimple,ElectricLoadCenter:Inverter:Simple}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ElectricLoadCenterInverterSimple</code>.
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
  class EPMODEL_API ElectricLoadCenterInverterSimple : public ModelObject
  {
   public:
    explicit ElectricLoadCenterInverterSimple(const Model& model);

    virtual ~ElectricLoadCenterInverterSimple() override = default;
    ElectricLoadCenterInverterSimple(const ElectricLoadCenterInverterSimple& other) = default;
    ElectricLoadCenterInverterSimple(ElectricLoadCenterInverterSimple&& other) = default;
    ElectricLoadCenterInverterSimple& operator=(const ElectricLoadCenterInverterSimple&) = default;
    ElectricLoadCenterInverterSimple& operator=(ElectricLoadCenterInverterSimple&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> radiativeFraction() const;
    bool setRadiativeFraction(double radiativeFraction);
    void resetRadiativeFraction();

    boost::optional<double> inverterEfficiency() const;
    bool setInverterEfficiency(double inverterEfficiency);
    void resetInverterEfficiency();

   protected:
    using ImplType = detail::ElectricLoadCenterInverterSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterInverterSimple(std::shared_ptr<detail::ElectricLoadCenterInverterSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
