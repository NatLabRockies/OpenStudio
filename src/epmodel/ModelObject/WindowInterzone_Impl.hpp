/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWINTERZONE_IMPL_HPP
#define EPMODEL_WINDOWINTERZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowInterzone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowInterzone_Impl() override = default;

      double multiplier() const;
      bool isMultiplierDefaulted() const;
      boost::optional<double> startingXCoordinate() const;
      boost::optional<double> startingZCoordinate() const;
      boost::optional<double> length() const;
      boost::optional<double> height() const;

      bool setMultiplier(double multiplier);
      bool setStartingXCoordinate(double startingXCoordinate);
      bool setStartingZCoordinate(double startingZCoordinate);
      bool setLength(double length);
      bool setHeight(double height);

      void resetMultiplier();
      void resetStartingXCoordinate();
      void resetStartingZCoordinate();
      void resetLength();
      void resetHeight();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
