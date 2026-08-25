/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIAL_IMPL_HPP
#define EPMODEL_MATERIAL_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Material_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~Material_Impl() override = default;

      virtual double thickness() const;
      virtual bool setThickness(double value);

      virtual boost::optional<double> getVisibleTransmittance() const;
      virtual boost::optional<double> interiorVisibleAbsorptance() const;
      virtual boost::optional<double> exteriorVisibleAbsorptance() const;

     private:
      REGISTER_LOGGER("openstudio.epmodel.Material");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
