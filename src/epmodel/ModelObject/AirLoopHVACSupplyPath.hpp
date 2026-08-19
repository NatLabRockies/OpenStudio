/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPATH_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPATH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class Model;

  namespace detail {
    class AirLoopHVACSupplyPath_Impl;
  }

  /** \brief Represents the EnergyPlus AirLoopHVAC:SupplyPath object.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacsupplypath,AirLoopHVAC:SupplyPath}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirLoopHVACSupplyPath : public ModelObject
  {
   public:
    explicit AirLoopHVACSupplyPath(const Model& model);

    virtual ~AirLoopHVACSupplyPath() override = default;
    AirLoopHVACSupplyPath(const AirLoopHVACSupplyPath& other) = default;
    AirLoopHVACSupplyPath(AirLoopHVACSupplyPath&& other) = default;
    AirLoopHVACSupplyPath& operator=(const AirLoopHVACSupplyPath&) = default;
    AirLoopHVACSupplyPath& operator=(AirLoopHVACSupplyPath&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
    std::vector<openstudio::epmodel::ModelObject> components() const;
    bool removeComponent(const openstudio::epmodel::ModelObject& component);

   protected:
    using ImplType = detail::AirLoopHVACSupplyPath_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit AirLoopHVACSupplyPath(std::shared_ptr<detail::AirLoopHVACSupplyPath_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
