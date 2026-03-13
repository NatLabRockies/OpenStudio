/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SKYTEMPERATURE_IMPL_HPP
#define EPMODEL_SKYTEMPERATURE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SkyTemperature_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SkyTemperature_Impl() override = default;

      std::vector<std::string> calculationTypeValues() const;

      std::string calculationType() const;
      bool setCalculationType(const std::string& calculationType);
      bool isCalculationTypeDefaulted() const;
      void resetCalculationType();

      bool useWeatherFileHorizontalIR() const;
      bool setUseWeatherFileHorizontalIR(bool useWeatherFileHorizontalIR);
      bool isUseWeatherFileHorizontalIRDefaulted() const;
      void resetUseWeatherFileHorizontalIR();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
