/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEREFRIGERATIONDOORMIXING_IMPL_HPP
#define EPMODEL_ZONEREFRIGERATIONDOORMIXING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneRefrigerationDoorMixing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneRefrigerationDoorMixing_Impl() override = default;

      double doorHeight() const;
      bool isDoorHeightDefaulted() const;
      bool setDoorHeight(double doorHeight);
      void resetDoorHeight();

      double doorArea() const;
      bool isDoorAreaDefaulted() const;
      bool setDoorArea(double doorArea);
      void resetDoorArea();

      std::string doorProtectionType() const;
      bool isDoorProtectionTypeDefaulted() const;
      bool setDoorProtectionType(const std::string& doorProtectionType);
      void resetDoorProtectionType();

      std::vector<std::string> doorProtectionTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
