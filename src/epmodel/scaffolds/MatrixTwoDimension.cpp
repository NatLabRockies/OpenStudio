/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MatrixTwoDimension.hpp"
#include "scaffolds/MatrixTwoDimension_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Matrix_TwoDimension_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

MatrixTwoDimension::MatrixTwoDimension(const Model& model) : ModelObject(MatrixTwoDimension::iddObjectType(), model) {}

MatrixTwoDimension::MatrixTwoDimension(std::shared_ptr<detail::MatrixTwoDimension_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType MatrixTwoDimension::iddObjectType() {
  return IddObjectType::Matrix_TwoDimension;
}

int MatrixTwoDimension::numberofRows() const {
  return getImpl<detail::MatrixTwoDimension_Impl>()->numberofRows();
}

bool MatrixTwoDimension::setNumberofRows(int numberofRows) {
  return getImpl<detail::MatrixTwoDimension_Impl>()->setNumberofRows(numberofRows);
}

int MatrixTwoDimension::numberofColumns() const {
  return getImpl<detail::MatrixTwoDimension_Impl>()->numberofColumns();
}

bool MatrixTwoDimension::setNumberofColumns(int numberofColumns) {
  return getImpl<detail::MatrixTwoDimension_Impl>()->setNumberofColumns(numberofColumns);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int MatrixTwoDimension_Impl::numberofRows() const {
  const auto value = getInt(openstudio::Matrix_TwoDimensionFields::NumberofRows, true);
  OS_ASSERT(value);
  return *value;
}

bool MatrixTwoDimension_Impl::setNumberofRows(int numberofRows) {
  const bool result = setInt(openstudio::Matrix_TwoDimensionFields::NumberofRows, numberofRows);
  OS_ASSERT(result);
  return result;
}

int MatrixTwoDimension_Impl::numberofColumns() const {
  const auto value = getInt(openstudio::Matrix_TwoDimensionFields::NumberofColumns, true);
  OS_ASSERT(value);
  return *value;
}

bool MatrixTwoDimension_Impl::setNumberofColumns(int numberofColumns) {
  const bool result = setInt(openstudio::Matrix_TwoDimensionFields::NumberofColumns, numberofColumns);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
