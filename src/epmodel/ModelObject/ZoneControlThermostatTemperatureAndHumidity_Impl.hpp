/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATTEMPERATUREANDHUMIDITY_IMPL_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATTEMPERATUREANDHUMIDITY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneControlThermostatTemperatureAndHumidity_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneControlThermostatTemperatureAndHumidity_Impl() override = default;

      std::string dehumidificationControlType() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      bool isDehumidificationControlTypeDefaulted() const;
      void resetDehumidificationControlType();

      std::string overcoolRangeInputMethod() const;
      bool setOvercoolRangeInputMethod(const std::string& overcoolRangeInputMethod);
      bool isOvercoolRangeInputMethodDefaulted() const;
      void resetOvercoolRangeInputMethod();

      boost::optional<double> overcoolConstantRange() const;
      bool setOvercoolConstantRange(double overcoolConstantRange);
      bool isOvercoolConstantRangeDefaulted() const;
      void resetOvercoolConstantRange();

      boost::optional<double> overcoolControlRatio() const;
      bool setOvercoolControlRatio(double overcoolControlRatio);
      bool isOvercoolControlRatioDefaulted() const;
      void resetOvercoolControlRatio();

      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> overcoolRangeInputMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
