/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLEROBJECTREFERENCE_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLEROBJECTREFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantChillerObjectReference_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantChillerObjectReference_Impl() override = default;

      std::string chillerObjectType() const;
      bool isChillerObjectTypeDefaulted() const;
      bool setChillerObjectType(const std::string& chillerObjectType);
      void resetChillerObjectType();

      boost::optional<double> priority() const;
      bool setPriority(double priority);
      void resetPriority();

      std::vector<std::string> chillerObjectTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
