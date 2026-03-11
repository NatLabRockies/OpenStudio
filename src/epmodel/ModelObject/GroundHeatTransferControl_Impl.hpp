/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERCONTROL_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferControl_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferControl_Impl() override = default;

  bool runBasementPreprocessor() const;
  bool isRunBasementPreprocessorDefaulted() const;
  bool setRunBasementPreprocessor(bool runBasementPreprocessor);
  void resetRunBasementPreprocessor();

  bool runSlabPreprocessor() const;
  bool isRunSlabPreprocessorDefaulted() const;
  bool setRunSlabPreprocessor(bool runSlabPreprocessor);
  void resetRunSlabPreprocessor();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
