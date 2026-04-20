/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVAC_EXHAUSTCONTROL_IMPL_HPP
#define EPMODEL_ZONEHVAC_EXHAUSTCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACExhaustControl_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACExhaustControl_Impl() override = default;

      std::vector<std::string> flowControlTypeValues() const;

      std::string flowControlType() const;
      bool isFlowControlTypeDefaulted() const;
      bool setFlowControlType(const std::string& flowControlType);
      void resetFlowControlType();

      boost::optional<double> designExhaustFlowRate() const;
      bool isDesignExhaustFlowRateAutosized() const;
      bool setDesignExhaustFlowRate(double designExhaustFlowRate);
      void autosizeDesignExhaustFlowRate();
      void resetDesignExhaustFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
