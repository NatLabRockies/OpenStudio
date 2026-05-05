/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEPRECIPITATION_IMPL_HPP
#define EPMODEL_SITEPRECIPITATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SitePrecipitation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SitePrecipitation_Impl() override = default;

      std::vector<std::string> precipitationModelTypeValues() const;

      boost::optional<std::string> precipitationModelType() const;
      bool setPrecipitationModelType(const std::string& precipitationModelType);
      void resetPrecipitationModelType();

      boost::optional<double> designLevelforTotalAnnualPrecipitation() const;
      bool setDesignLevelforTotalAnnualPrecipitation(double designLevelforTotalAnnualPrecipitation);
      void resetDesignLevelforTotalAnnualPrecipitation();

      boost::optional<double> averageTotalAnnualPrecipitation() const;
      bool setAverageTotalAnnualPrecipitation(double averageTotalAnnualPrecipitation);
      void resetAverageTotalAnnualPrecipitation();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
