/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTJSON_IMPL_HPP
#define EPMODEL_OUTPUTJSON_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputJSON_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputJSON_Impl() override = default;

      std::vector<std::string> optionTypeValues() const;

      std::string optionType() const;
      bool setOptionType(const std::string& optionType);

      bool outputJSON() const;
      bool setOutputJSON(bool outputJSON);

      bool outputCBOR() const;
      bool setOutputCBOR(bool outputCBOR);

      bool outputMessagePack() const;
      bool setOutputMessagePack(bool outputMessagePack);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
