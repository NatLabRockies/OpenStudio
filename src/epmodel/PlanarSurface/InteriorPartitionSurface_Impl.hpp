/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INTERIORPARTITIONSURFACE_IMPL_HPP
#define EPMODEL_INTERIORPARTITIONSURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API InteriorPartitionSurface_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~InteriorPartitionSurface_Impl() override = default;

      bool converttoInternalMass() const;
      bool isConverttoInternalMassDefaulted() const;
      bool setConverttoInternalMass(bool converttoInternalMass);
      void resetConverttoInternalMass();

      boost::optional<double> surfaceArea() const;
      bool setSurfaceArea(boost::optional<double> surfaceArea);
      bool setSurfaceArea(double surfaceArea);
      void resetSurfaceArea();

      boost::optional<double> numberofVertices() const;
      bool isNumberofVerticesDefaulted() const;
      bool isNumberofVerticesAutocalculated() const;
      bool setNumberofVertices(boost::optional<double> numberofVertices);
      bool setNumberofVertices(double numberofVertices);
      void resetNumberofVertices();
      void autocalculateNumberofVertices();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
