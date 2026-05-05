/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELHUMIDISTATOFFSET_IMPL_HPP
#define EPMODEL_FAULTMODELHUMIDISTATOFFSET_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelHumidistatOffset_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelHumidistatOffset_Impl() override = default;

      std::string humidistatOffsetType() const;
      bool isHumidistatOffsetTypeDefaulted() const;
      bool setHumidistatOffsetType(const std::string& humidistatOffsetType);
      void resetHumidistatOffsetType();

      double referenceHumidistatOffset() const;
      bool isReferenceHumidistatOffsetDefaulted() const;
      bool setReferenceHumidistatOffset(double referenceHumidistatOffset);
      void resetReferenceHumidistatOffset();

      std::vector<std::string> humidistatOffsetTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
