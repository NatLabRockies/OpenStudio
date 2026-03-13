/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGZONEDETAILED_IMPL_HPP
#define EPMODEL_SHADINGZONEDETAILED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadingZoneDetailed_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingZoneDetailed_Impl() override = default;

      /** @name Number of Vertices */
      //@{
      boost::optional<int> numberofVertices() const;
      bool setNumberofVertices(int numberofVertices);
      bool isNumberofVerticesAutocalculated() const;
      void autocalculateNumberofVertices();
      void resetNumberofVertices();
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
