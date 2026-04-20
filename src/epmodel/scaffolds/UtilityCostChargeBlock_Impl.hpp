/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTCHARGEBLOCK_IMPL_HPP
#define EPMODEL_UTILITYCOSTCHARGEBLOCK_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostChargeBlock_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostChargeBlock_Impl() override = default;

      std::string sourceVariable() const;
      bool setSourceVariable(const std::string& sourceVariable);

      std::string season() const;
      bool setSeason(const std::string& season);
      bool isSeasonDefaulted() const;
      void resetSeason();

      std::string categoryVariableName() const;
      bool setCategoryVariableName(const std::string& categoryVariableName);

      boost::optional<std::string> remainingIntoVariable() const;
      bool setRemainingIntoVariable(const std::string& remainingIntoVariable);
      void resetRemainingIntoVariable();

      boost::optional<std::string> blockSizeMultiplierValueorVariableName() const;
      bool setBlockSizeMultiplierValueorVariableName(const std::string& blockSizeMultiplierValueorVariableName);
      void resetBlockSizeMultiplierValueorVariableName();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
