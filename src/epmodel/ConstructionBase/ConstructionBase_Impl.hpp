/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONBASE_IMPL_HPP
#define EPMODEL_CONSTRUCTIONBASE_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ConstructionBase_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~ConstructionBase_Impl() override = default;

      virtual bool isOpaque() const = 0;
      virtual bool isFenestration() const = 0;
      virtual bool isSolarDiffusing() const = 0;
      virtual bool isModelPartition() const = 0;

      /** Returns true if the construction has RoofVegetation as the outer layer. */
      virtual bool isGreenRoof() const;

     private:
      REGISTER_LOGGER("openstudio.epmodel.ConstructionBase");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
