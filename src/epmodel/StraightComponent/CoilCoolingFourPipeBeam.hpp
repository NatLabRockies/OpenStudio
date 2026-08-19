/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGFOURPIPEBEAM_HPP
#define EPMODEL_COILCOOLINGFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingFourPipeBeam_Impl;
  }

  /** \brief Represents a chilled-water coil used by a four-pipe beam terminal.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel stores <code>OS:Coil:Cooling:FourPipeBeam</code> as a persisted OpenStudio extension child of \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumefourpipebeam,AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam}.
   *
   * \par Important behavior
   * The child provides water-side ports; plant connection follows the parent terminal and plant branch topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingFourPipeBeam</code>. <b>Not yet available:</b> the beam cooling performance-modifier curves and rated-per-beam-length/temperature-difference setters and default-state queries. The EPModel child remains a narrow plant-side view.
   * \par Known limitations
   * Use the owning terminal for complete air-side and coil relationships.
   */
  class EPMODEL_API CoilCoolingFourPipeBeam : public StraightComponent
  {
   public:
    explicit CoilCoolingFourPipeBeam(const Model& model);

    virtual ~CoilCoolingFourPipeBeam() override = default;
    CoilCoolingFourPipeBeam(const CoilCoolingFourPipeBeam& other) = default;
    CoilCoolingFourPipeBeam(CoilCoolingFourPipeBeam&& other) = default;
    CoilCoolingFourPipeBeam& operator=(const CoilCoolingFourPipeBeam&) = default;
    CoilCoolingFourPipeBeam& operator=(CoilCoolingFourPipeBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilCoolingFourPipeBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingFourPipeBeam(std::shared_ptr<detail::CoilCoolingFourPipeBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
