/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEEXTERNALNODE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEEXTERNALNODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneExternalNode_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneExternalNode_Impl() override = default;

      double externalNodeHeight() const;
      bool isExternalNodeHeightDefaulted() const;
      bool setExternalNodeHeight(double externalNodeHeight);
      void resetExternalNodeHeight();

      bool symmetricWindPressureCoefficientCurve() const;
      bool isSymmetricWindPressureCoefficientCurveDefaulted() const;
      bool setSymmetricWindPressureCoefficientCurve(bool symmetricWindPressureCoefficientCurve);
      void resetSymmetricWindPressureCoefficientCurve();

      std::string windAngleType() const;
      bool isWindAngleTypeDefaulted() const;
      bool setWindAngleType(const std::string& windAngleType);
      void resetWindAngleType();

      std::vector<std::string> windAngleTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
