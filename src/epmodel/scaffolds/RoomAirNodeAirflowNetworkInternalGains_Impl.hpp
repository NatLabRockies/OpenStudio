/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORKINTERNALGAINS_IMPL_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORKINTERNALGAINS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoomAirNodeAirflowNetworkInternalGains_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirNodeAirflowNetworkInternalGains_Impl() override = default;

      boost::optional<std::string> internalGainObject1Type() const;
      bool setInternalGainObject1Type(const std::string& internalGainObject1Type);
      void resetInternalGainObject1Type();

      boost::optional<std::string> internalGainObject1Name() const;
      bool setInternalGainObject1Name(const std::string& internalGainObject1Name);
      void resetInternalGainObject1Name();

      boost::optional<double> fractionOfGainsToNode1() const;
      bool setFractionOfGainsToNode1(double fractionOfGainsToNode1);
      void resetFractionOfGainsToNode1();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
