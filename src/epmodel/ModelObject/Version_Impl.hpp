/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_VERSION_IMPL_HPP
#define EPMODEL_VERSION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Version_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Version_Impl() override = default;

      std::string versionIdentifier() const;
      bool isVersionIdentifierDefaulted() const;
      bool setVersionIdentifier(const std::string& versionIdentifier);
      void resetVersionIdentifier();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
