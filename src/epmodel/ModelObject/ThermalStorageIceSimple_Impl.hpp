/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEICESIMPLE_IMPL_HPP
#define EPMODEL_THERMALSTORAGEICESIMPLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermalStorageIceSimple_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalStorageIceSimple_Impl() override = default;

      boost::optional<double> capacity() const;
      bool setCapacity(double capacity);
      bool isCapacityAutosized() const;
      void autosizeCapacity();

      std::string iceStorageType() const;
      bool setIceStorageType(const std::string& iceStorageType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
