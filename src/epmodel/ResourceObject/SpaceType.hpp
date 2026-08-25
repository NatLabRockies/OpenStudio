/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACETYPE_HPP
#define EPMODEL_SPACETYPE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceType_Impl;
  }

  /** \brief Names a group of spaces for EnergyPlus processing.
   *
   * \par EnergyPlus object
   * \epobject{group-thermal-zone-description-geometry.html#spacelist,SpaceList}. Despite its OpenStudio name, this EPModel type
   * encapsulates SpaceList rather than a standalone EnergyPlus SpaceType
   * object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SpaceType</code>, whose object is an OpenStudio
   * resource with extensive space-load and standards relationships. EPModel
   * currently exposes only inherited name access; those Model relationships
   * and load helpers are not available.
   *
   * \par Known limitations
   * Spaces cannot yet be added, removed, or queried through this wrapper.
   */
  class EPMODEL_API SpaceType : public ModelObject
  {
   public:
    explicit SpaceType(const Model& model);

    virtual ~SpaceType() override = default;
    SpaceType(const SpaceType& other) = default;
    SpaceType(SpaceType&& other) = default;
    SpaceType& operator=(const SpaceType&) = default;
    SpaceType& operator=(SpaceType&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::SpaceType_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceType(std::shared_ptr<detail::SpaceType_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
