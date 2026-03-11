/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMOUTPUTVARIABLE_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMOUTPUTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API EnergyManagementSystemOutputVariable_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EnergyManagementSystemOutputVariable_Impl() override = default;

  std::string emsVariableName() const;
  bool setEMSVariableName(const std::string& eMSVariableName);

  std::string typeOfDataInVariable() const;
  bool setTypeOfDataInVariable(const std::string& typeofDatainVariable);

  std::string updateFrequency() const;
  bool setUpdateFrequency(const std::string& updateFrequency);

  std::string units() const;
  bool setUnits(const std::string& units);
  void resetUnits();

  std::vector<std::string> typeOfDataInVariableValues() const;
  std::vector<std::string> updateFrequencyValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
