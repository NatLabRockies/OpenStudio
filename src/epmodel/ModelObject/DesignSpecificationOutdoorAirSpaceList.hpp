/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Space;
  class DesignSpecificationOutdoorAir;

  namespace detail {
    class DesignSpecificationOutdoorAirSpaceList_Impl;
  }

  /** \brief Represents <code>DesignSpecification:OutdoorAir:SpaceList</code>.
   *
   * \par EnergyPlus object
   * Represents \epobject{group-design-objects.html#designspecificationoutdoorairspacelist,DesignSpecification:OutdoorAir:SpaceList}.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>DesignSpecification:OutdoorAir:SpaceList</code>; this wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Relationship-row mutation and higher-level topology conveniences remain owner-managed or unavailable through this wrapper.
   */
  class EPMODEL_API DesignSpecificationOutdoorAirSpaceList : public ModelObject
  {
   public:
    explicit DesignSpecificationOutdoorAirSpaceList(const Model& model);

    virtual ~DesignSpecificationOutdoorAirSpaceList() override = default;
    DesignSpecificationOutdoorAirSpaceList(const DesignSpecificationOutdoorAirSpaceList& other) = default;
    DesignSpecificationOutdoorAirSpaceList(DesignSpecificationOutdoorAirSpaceList&& other) = default;
    DesignSpecificationOutdoorAirSpaceList& operator=(const DesignSpecificationOutdoorAirSpaceList&) = default;
    DesignSpecificationOutdoorAirSpaceList& operator=(DesignSpecificationOutdoorAirSpaceList&&) = default;

    static IddObjectType iddObjectType();
    std::vector<Space> spaces() const;
    boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAir(const Space& space) const;

   protected:
    using ImplType = detail::DesignSpecificationOutdoorAirSpaceList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit DesignSpecificationOutdoorAirSpaceList(std::shared_ptr<detail::DesignSpecificationOutdoorAirSpaceList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
