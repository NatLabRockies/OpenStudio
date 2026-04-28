/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERVENTILATION_IMPL_HPP
#define EPMODEL_DEMANDMANAGERVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DemandManagerVentilation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DemandManagerVentilation_Impl() override = default;

      std::vector<std::string> limitControlValues() const;
      std::vector<std::string> selectionControlValues() const;

      std::string limitControl() const;
      bool setLimitControl(const std::string& limitControl);

      boost::optional<int> minimumLimitDuration() const;
      bool setMinimumLimitDuration(int minimumLimitDuration);
      void resetMinimumLimitDuration();

      boost::optional<double> fixedRate() const;
      bool setFixedRate(double fixedRate);
      void resetFixedRate();

      boost::optional<double> reductionRatio() const;
      bool setReductionRatio(double reductionRatio);
      void resetReductionRatio();

      boost::optional<double> limitStepChange() const;
      bool setLimitStepChange(double limitStepChange);
      void resetLimitStepChange();

      std::string selectionControl() const;
      bool isSelectionControlDefaulted() const;
      bool setSelectionControl(const std::string& selectionControl);
      void resetSelectionControl();

      boost::optional<int> rotationDuration() const;
      bool setRotationDuration(int rotationDuration);
      void resetRotationDuration();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
