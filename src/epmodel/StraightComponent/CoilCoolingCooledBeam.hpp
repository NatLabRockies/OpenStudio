/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGCOOLEDBEAM_HPP
#define EPMODEL_COILCOOLINGCOOLEDBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingCooledBeam_Impl;
  }

  /** \brief Represents a chilled-water coil used by a cooled-beam terminal.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel stores <code>OS:Coil:Cooling:CooledBeam</code> as a persisted OpenStudio extension child of \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumecooledbeam,AirTerminal:SingleDuct:ConstantVolume:CooledBeam}.
   *
   * \par Important behavior
   * The child provides water-side ports; plant connection follows the parent terminal and plant branch topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingCooledBeam</code>.
   * <b>Not yet available:</b> the beam cooling performance-modifier curves and rated-per-beam-length/
   * temperature-difference setters and default-state queries. The EPModel child remains a narrow plant-side view.
   *
   * \par Known limitations
   * Use the owning terminal for complete air-side and coil relationships.
   */
  class EPMODEL_API CoilCoolingCooledBeam : public StraightComponent
  {
   public:
    explicit CoilCoolingCooledBeam(const Model& model);

    virtual ~CoilCoolingCooledBeam() override = default;
    CoilCoolingCooledBeam(const CoilCoolingCooledBeam& other) = default;
    CoilCoolingCooledBeam(CoilCoolingCooledBeam&& other) = default;
    CoilCoolingCooledBeam& operator=(const CoilCoolingCooledBeam&) = default;
    CoilCoolingCooledBeam& operator=(CoilCoolingCooledBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilCoolingCooledBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingCooledBeam(std::shared_ptr<detail::CoilCoolingCooledBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
