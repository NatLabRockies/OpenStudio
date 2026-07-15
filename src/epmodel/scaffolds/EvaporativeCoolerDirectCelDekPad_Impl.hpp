/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTCELDEKPAD_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTCELDEKPAD_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API EvaporativeCoolerDirectCelDekPad_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~EvaporativeCoolerDirectCelDekPad_Impl() override = default;

      boost::optional<double> directPadArea() const;
      bool isDirectPadAreaAutosized() const;
      bool setDirectPadArea(double directPadArea);
      void resetDirectPadArea();
      void autosizeDirectPadArea();

      boost::optional<double> directPadDepth() const;
      bool isDirectPadDepthAutosized() const;
      bool setDirectPadDepth(double directPadDepth);
      void resetDirectPadDepth();
      void autosizeDirectPadDepth();

      double recirculatingWaterPumpPowerConsumption() const;
      bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

      boost::optional<std::string> controlType() const;
      bool setControlType(const std::string& controlType);
      void resetControlType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
