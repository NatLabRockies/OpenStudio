/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACELIST_HPP
#define EPMODEL_SPACELIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Space;

  namespace detail {
    class SpaceList_Impl;
  }

  class EPMODEL_API SpaceList : public ModelObject
  {
   public:
    explicit SpaceList(const Model& model);

    virtual ~SpaceList() override = default;
    SpaceList(const SpaceList& other) = default;
    SpaceList(SpaceList&& other) = default;
    SpaceList& operator=(const SpaceList&) = default;
    SpaceList& operator=(SpaceList&&) = default;

    static IddObjectType iddObjectType();

    /** Add a Space to this SpaceList. */
    bool addSpace(const Space& space);

    /** Returns all Spaces in this SpaceList. */
    std::vector<Space> spaces() const;

   protected:
    using ImplType = detail::SpaceList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceList(std::shared_ptr<detail::SpaceList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
