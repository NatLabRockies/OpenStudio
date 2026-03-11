/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODE_IMPL_HPP
#define EPMODEL_ROOMAIRNODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoomAirNode_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirNode_Impl() override = default;

      std::string nodeType() const;
      bool setNodeType(const std::string& nodeType);

      double heightOfNodalControlVolumeCenter() const;
      bool setHeightOfNodalControlVolumeCenter(double heightOfNodalControlVolumeCenter);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
