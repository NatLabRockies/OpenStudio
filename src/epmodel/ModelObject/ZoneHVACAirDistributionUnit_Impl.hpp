/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACAIRDISTRIBUTIONUNIT_IMPL_HPP
#define EPMODEL_ZONEHVACAIRDISTRIBUTIONUNIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class ModelObject;
  class Node;
  namespace detail {

    class EPMODEL_API ZoneHVACAirDistributionUnit_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACAirDistributionUnit_Impl() override = default;

      bool setAirTerminal(const openstudio::epmodel::ModelObject& airTerminal);
      bool setOutletNode(const openstudio::epmodel::Node& node);
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
