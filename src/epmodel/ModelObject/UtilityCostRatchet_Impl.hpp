/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTRATCHET_IMPL_HPP
#define EPMODEL_UTILITYCOSTRATCHET_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostRatchet_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostRatchet_Impl() override = default;

      std::string baselineSourceVariable() const;
      bool setBaselineSourceVariable(const std::string& baselineSourceVariable);

      std::string adjustmentSourceVariable() const;
      bool setAdjustmentSourceVariable(const std::string& adjustmentSourceVariable);

      std::string seasonFrom() const;
      bool setSeasonFrom(const std::string& seasonFrom);

      std::string seasonTo() const;
      bool setSeasonTo(const std::string& seasonTo);

      boost::optional<std::string> multiplierValueorVariableName() const;
      bool setMultiplierValueorVariableName(const std::string& multiplierValueorVariableName);
      void resetMultiplierValueorVariableName();

      boost::optional<std::string> offsetValueorVariableName() const;
      bool setOffsetValueorVariableName(const std::string& offsetValueorVariableName);
      void resetOffsetValueorVariableName();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
