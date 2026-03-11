/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ROOFIRRIGATION_IMPL_HPP
#define EPMODEL_ROOFIRRIGATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoofIrrigation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoofIrrigation_Impl() override = default;

      boost::optional<std::string> irrigationModelType() const;
      bool setIrrigationModelType(const std::string& irrigationModelType);
      void resetIrrigationModelType();

      double irrigationMaximumSaturationThreshold() const;
      bool isIrrigationMaximumSaturationThresholdDefaulted() const;
      bool setIrrigationMaximumSaturationThreshold(double irrigationMaximumSaturationThreshold);
      void resetIrrigationMaximumSaturationThreshold();

      std::vector<std::string> irrigationModelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
