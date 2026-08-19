/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSPLITTER_HPP
#define EPMODEL_AIRLOOPHVACSPLITTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACSplitter_Impl;
  }

  /** \brief Represents the EnergyPlus AirLoopHVAC:Splitter object.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacsplitter,AirLoopHVAC:Splitter}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirLoopHVACSplitter : public ModelObject
  {
   public:
    explicit AirLoopHVACSplitter(const Model& model);

    virtual ~AirLoopHVACSplitter() override = default;
    AirLoopHVACSplitter(const AirLoopHVACSplitter& other) = default;
    AirLoopHVACSplitter(AirLoopHVACSplitter&& other) = default;
    AirLoopHVACSplitter& operator=(const AirLoopHVACSplitter&) = default;
    AirLoopHVACSplitter& operator=(AirLoopHVACSplitter&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::AirLoopHVACSplitter_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACSplitter(std::shared_ptr<detail::AirLoopHVACSplitter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
