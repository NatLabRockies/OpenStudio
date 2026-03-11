/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWINDOWDATAFILE_IMPL_HPP
#define EPMODEL_CONSTRUCTIONWINDOWDATAFILE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ConstructionWindowDataFile_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ConstructionWindowDataFile_Impl() override = default;

  boost::optional<std::string> fileName() const;
  bool setFileName(const std::string& fileName);
  void resetFileName();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
