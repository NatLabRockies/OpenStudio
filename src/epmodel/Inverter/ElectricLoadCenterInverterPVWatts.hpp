/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterInverterPVWatts_Impl;
  }

  /** \brief Represents a PVWatts inverter.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#electricloadcenterinverterpvwatts,ElectricLoadCenter:Inverter:PVWatts}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ElectricLoadCenterInverterPVWatts</code>.
   *
   * - <b>Not yet available:</b> The Model Inverter relationship methods
   *   <code>electricLoadCenterDistribution()</code>, <code>thermalZone()</code>,
   *   <code>setThermalZone(...)</code>, and <code>resetThermalZone()</code>.
   *
   * \par Known limitations
   * Connect the inverter to an electric-load-center distribution or zone with
   * lower-level object references when needed.
   */
  class EPMODEL_API ElectricLoadCenterInverterPVWatts : public ModelObject
  {
   public:
    explicit ElectricLoadCenterInverterPVWatts(const Model& model);

    virtual ~ElectricLoadCenterInverterPVWatts() override = default;
    ElectricLoadCenterInverterPVWatts(const ElectricLoadCenterInverterPVWatts& other) = default;
    ElectricLoadCenterInverterPVWatts(ElectricLoadCenterInverterPVWatts&& other) = default;
    ElectricLoadCenterInverterPVWatts& operator=(const ElectricLoadCenterInverterPVWatts&) = default;
    ElectricLoadCenterInverterPVWatts& operator=(ElectricLoadCenterInverterPVWatts&&) = default;

    static IddObjectType iddObjectType();

    /** @name DC to AC Size Ratio */
    //@{
    double dcToACSizeRatio() const;
    bool isDCToACSizeRatioDefaulted() const;
    bool setDCToACSizeRatio(double dcToACSizeRatio);
    void resetDCToACSizeRatio();
    //@}

    /** @name Inverter Efficiency */
    //@{
    double inverterEfficiency() const;
    bool isInverterEfficiencyDefaulted() const;
    bool setInverterEfficiency(double inverterEfficiency);
    void resetInverterEfficiency();
    //@}

   protected:
    using ImplType = detail::ElectricLoadCenterInverterPVWatts_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterInverterPVWatts(std::shared_ptr<detail::ElectricLoadCenterInverterPVWatts_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
