/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORT_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImport_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExternalInterfaceFunctionalMockupUnitImport_Impl() override = default;

  double fMUTimeout() const;
  bool isFMUTimeoutDefaulted() const;

  int fMULoggingOn() const;
  bool isFMULoggingOnDefaulted() const;

  std::string fMUFileName() const;

  bool setFMUTimeout(double fMUTimeout);
  void resetFMUTimeout();

  bool setFMULoggingOn(int fMULoggingOn);
  void resetFMULoggingOn();

  bool setFMUFileName(const std::string& fMUName);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
