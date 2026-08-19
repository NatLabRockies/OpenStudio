/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGFOURPIPEBEAM_HPP
#define EPMODEL_COILHEATINGFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingFourPipeBeam_Impl;
  }

  /** \brief Represents a hot-water coil used by a four-pipe beam terminal.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel stores <code>OS:Coil:Heating:FourPipeBeam</code> as a persisted OpenStudio extension child of \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumefourpipebeam,AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam}.
   *
   * \par Important behavior
   * The child provides water-side ports; plant connection follows the parent terminal and plant branch topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingFourPipeBeam</code>. <b>Not yet available:</b> the beam heating performance-modifier curves and rated-per-beam-length/temperature-difference setters and default-state queries. The EPModel child remains a narrow plant-side view.
   * \par Known limitations
   * Use the owning terminal for complete air-side and coil relationships.
   */
  class EPMODEL_API CoilHeatingFourPipeBeam : public StraightComponent
  {
   public:
    explicit CoilHeatingFourPipeBeam(const Model& model);

    virtual ~CoilHeatingFourPipeBeam() override = default;
    CoilHeatingFourPipeBeam(const CoilHeatingFourPipeBeam& other) = default;
    CoilHeatingFourPipeBeam(CoilHeatingFourPipeBeam&& other) = default;
    CoilHeatingFourPipeBeam& operator=(const CoilHeatingFourPipeBeam&) = default;
    CoilHeatingFourPipeBeam& operator=(CoilHeatingFourPipeBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilHeatingFourPipeBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingFourPipeBeam(std::shared_ptr<detail::CoilHeatingFourPipeBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
