/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctUserDefined_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalSingleDuctUserDefined_Impl() override = default;

  int numberofPlantLoopConnections() const;
  bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
