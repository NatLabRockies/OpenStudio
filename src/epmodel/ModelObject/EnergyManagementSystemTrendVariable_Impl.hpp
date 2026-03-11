/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API EnergyManagementSystemTrendVariable_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EnergyManagementSystemTrendVariable_Impl() override = default;

  std::string emsVariableName() const;
  bool setEMSVariableName(const std::string& eMSVariableName);

  int numberOfTimestepsToBeLogged() const;
  bool setNumberOfTimestepsToBeLogged(int numberofTimestepstobeLogged);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
