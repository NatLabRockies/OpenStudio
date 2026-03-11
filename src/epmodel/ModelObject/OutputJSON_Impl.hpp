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

  std::string optionType() const;

  bool outputJSON() const;
  bool outputCBOR() const;
  bool outputMessagePack() const;

  bool setOptionType(const std::string& optionType);
  bool setOutputJSON(bool outputJSON);
  bool setOutputCBOR(bool outputCBOR);
  bool setOutputMessagePack(bool outputMessagePack);

  std::vector<std::string> optionTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
