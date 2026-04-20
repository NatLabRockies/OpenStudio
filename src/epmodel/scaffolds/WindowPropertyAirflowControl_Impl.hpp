/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYAIRFLOWCONTROL_IMPL_HPP
#define EPMODEL_WINDOWPROPERTYAIRFLOWCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowPropertyAirflowControl_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowPropertyAirflowControl_Impl() override = default;

      std::string airflowSource() const;
      bool isAirflowSourceDefaulted() const;
      bool setAirflowSource(const std::string& airflowSource);
      void resetAirflowSource();

      std::string airflowDestination() const;
      bool isAirflowDestinationDefaulted() const;
      bool setAirflowDestination(const std::string& airflowDestination);
      void resetAirflowDestination();

      double maximumFlowRate() const;
      bool isMaximumFlowRateDefaulted() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();

      std::string airflowControlType() const;
      bool isAirflowControlTypeDefaulted() const;
      bool setAirflowControlType(const std::string& airflowControlType);
      void resetAirflowControlType();

      bool airflowIsScheduled() const;
      bool isAirflowIsScheduledDefaulted() const;
      bool setAirflowIsScheduled(bool airflowIsScheduled);
      void resetAirflowIsScheduled();

      std::vector<std::string> airflowSourceValues() const;
      std::vector<std::string> airflowDestinationValues() const;
      std::vector<std::string> airflowControlTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
