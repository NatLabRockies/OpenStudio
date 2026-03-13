/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCOMPRESSOR_IMPL_HPP
#define EPMODEL_REFRIGERATIONCOMPRESSOR_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationCompressor_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationCompressor_Impl() override = default;

      boost::optional<double> ratedSuperheat() const;
      bool setRatedSuperheat(double ratedSuperheat);
      void resetRatedSuperheat();

      boost::optional<double> ratedReturnGasTemperature() const;
      bool setRatedReturnGasTemperature(double ratedReturnGasTemperature);
      void resetRatedReturnGasTemperature();

      boost::optional<double> ratedLiquidTemperature() const;
      bool setRatedLiquidTemperature(double ratedLiquidTemperature);
      void resetRatedLiquidTemperature();

      boost::optional<double> ratedSubcooling() const;
      bool setRatedSubcooling(double ratedSubcooling);
      void resetRatedSubcooling();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      std::string modeofOperation() const;
      bool isModeofOperationDefaulted() const;
      bool setModeofOperation(const std::string& modeofOperation);
      void resetModeofOperation();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
