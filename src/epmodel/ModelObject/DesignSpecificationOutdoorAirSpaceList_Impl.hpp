/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_IMPL_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Space;
  class DesignSpecificationOutdoorAir;

  namespace detail {

    class EPMODEL_API DesignSpecificationOutdoorAirSpaceList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DesignSpecificationOutdoorAirSpaceList_Impl() override = default;

      std::vector<openstudio::epmodel::Space> spaces() const;
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir>
        designSpecificationOutdoorAir(const openstudio::epmodel::Space& space) const;
      bool setDesignSpecificationOutdoorAir(const openstudio::epmodel::Space& space,
                                            const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);
      void clearDesignSpecificationOutdoorAirEntries();
      bool removeSpace(const openstudio::epmodel::Space& space);

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
