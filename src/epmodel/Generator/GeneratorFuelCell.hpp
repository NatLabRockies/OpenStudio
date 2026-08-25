/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELL_HPP
#define EPMODEL_GENERATORFUELCELL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCell_Impl;
  }

  /** \brief Represents a fuel-cell generator assembly.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorfuelcell,Generator:FuelCell}. Its object-list fields refer to companion
   * <code>Generator:FuelCell:*</code> objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::GeneratorFuelCell</code>.
   *
   * - <b>Changed:</b> The Model constructor can accept the eight companion
   *   fuel-cell objects; the EPModel constructor accepts only the model.
   * - <b>Not yet available:</b> The typed companion-object accessors and
   *   mutators, including <code>powerModule()</code>, <code>airSupply()</code>,
   *   <code>fuelSupply()</code>, <code>waterSupply()</code>,
   *   <code>auxiliaryHeater()</code>, <code>heatExchanger()</code>,
   *   <code>electricalStorage()</code>, <code>inverter()</code>,
   *   <code>stackCooler()</code>, and their setters/resetter.
   * - <b>Not yet available:</b> The Model Generator metadata methods
   *   <code>generatorObjectType()</code>, <code>ratedElectricPowerOutput()</code>,
   *   <code>availabilitySchedule()</code>,
   *   <code>ratedThermaltoElectricalPowerRatio()</code>, and
   *   <code>electricLoadCenterDistribution()</code>.
   *
   * \par Known limitations
   * A complete fuel-cell assembly must be assembled through companion wrappers
   * or lower-level object references before simulation.
   */
  class EPMODEL_API GeneratorFuelCell : public ModelObject
  {
   public:
    explicit GeneratorFuelCell(const Model& model);

    virtual ~GeneratorFuelCell() override = default;
    GeneratorFuelCell(const GeneratorFuelCell& other) = default;
    GeneratorFuelCell(GeneratorFuelCell&& other) = default;
    GeneratorFuelCell& operator=(const GeneratorFuelCell&) = default;
    GeneratorFuelCell& operator=(GeneratorFuelCell&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::GeneratorFuelCell_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCell(std::shared_ptr<detail::GeneratorFuelCell_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
