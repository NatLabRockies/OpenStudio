/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACMIXER_HPP
#define EPMODEL_AIRLOOPHVACMIXER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACMixer_Impl;
  }

  /** \brief Represents the EnergyPlus AirLoopHVAC:Mixer object.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacmixer,AirLoopHVAC:Mixer}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirLoopHVACMixer : public ModelObject
  {
   public:
    explicit AirLoopHVACMixer(const Model& model);

    virtual ~AirLoopHVACMixer() override = default;
    AirLoopHVACMixer(const AirLoopHVACMixer& other) = default;
    AirLoopHVACMixer(AirLoopHVACMixer&& other) = default;
    AirLoopHVACMixer& operator=(const AirLoopHVACMixer&) = default;
    AirLoopHVACMixer& operator=(AirLoopHVACMixer&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::AirLoopHVACMixer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACMixer(std::shared_ptr<detail::AirLoopHVACMixer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
