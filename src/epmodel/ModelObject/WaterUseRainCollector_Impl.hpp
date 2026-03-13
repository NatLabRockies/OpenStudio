/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSERAINCOLLECTOR_IMPL_HPP
#define EPMODEL_WATERUSERAINCOLLECTOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WaterUseRainCollector_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterUseRainCollector_Impl() override = default;

      std::vector<std::string> lossFactorModeValues() const;

      boost::optional<std::string> lossFactorMode() const;
      bool setLossFactorMode(const std::string& lossFactorMode);

      boost::optional<double> collectionLossFactor() const;
      bool setCollectionLossFactor(double collectionLossFactor);

      boost::optional<double> maximumCollectionRate() const;
      bool setMaximumCollectionRate(double maximumCollectionRate);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
