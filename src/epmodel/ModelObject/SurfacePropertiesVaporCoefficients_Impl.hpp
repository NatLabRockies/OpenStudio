/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTIESVAPORCOEFFICIENTS_IMPL_HPP
#define EPMODEL_SURFACEPROPERTIESVAPORCOEFFICIENTS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertiesVaporCoefficients_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertiesVaporCoefficients_Impl() override = default;

      bool constantExternalVaporTransferCoefficient() const;
      bool isConstantExternalVaporTransferCoefficientDefaulted() const;
      bool setConstantExternalVaporTransferCoefficient(bool constantExternalVaporTransferCoefficient);
      void resetConstantExternalVaporTransferCoefficient();

      double externalVaporCoefficientValue() const;
      bool isExternalVaporCoefficientValueDefaulted() const;
      bool setExternalVaporCoefficientValue(double externalVaporCoefficientValue);
      void resetExternalVaporCoefficientValue();

      bool constantInternalvaporTransferCoefficient() const;
      bool isConstantInternalvaporTransferCoefficientDefaulted() const;
      bool setConstantInternalvaporTransferCoefficient(bool constantInternalvaporTransferCoefficient);
      void resetConstantInternalvaporTransferCoefficient();

      double internalVaporCoefficientValue() const;
      bool isInternalVaporCoefficientValueDefaulted() const;
      bool setInternalVaporCoefficientValue(double internalVaporCoefficientValue);
      void resetInternalVaporCoefficientValue();

      std::vector<std::string> constantExternalVaporTransferCoefficientValues() const;
      std::vector<std::string> constantInternalvaporTransferCoefficientValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
