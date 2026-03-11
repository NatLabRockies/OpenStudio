/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerVerticalArray.hpp"
#include "GroundHeatExchangerVerticalArray_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Vertical_Array_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatExchangerVerticalArray::GroundHeatExchangerVerticalArray(const Model& model)
  : ModelObject(GroundHeatExchangerVerticalArray::iddObjectType(), model) {
  bool ok = true;
  ok = setNumberofBoreholesinXDirection(10);
  OS_ASSERT(ok);
  ok = setNumberofBoreholesinYDirection(12);
  OS_ASSERT(ok);
  ok = setBoreholeSpacing(6.0);
  OS_ASSERT(ok);
}

GroundHeatExchangerVerticalArray::GroundHeatExchangerVerticalArray(std::shared_ptr<detail::GroundHeatExchangerVerticalArray_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatExchangerVerticalArray::iddObjectType() {
  return IddObjectType::GroundHeatExchanger_Vertical_Array;
}

int GroundHeatExchangerVerticalArray::numberofBoreholesinXDirection() const {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->numberofBoreholesinXDirection();
}

int GroundHeatExchangerVerticalArray::numberofBoreholesinYDirection() const {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->numberofBoreholesinYDirection();
}

double GroundHeatExchangerVerticalArray::boreholeSpacing() const {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->boreholeSpacing();
}

bool GroundHeatExchangerVerticalArray::setNumberofBoreholesinXDirection(int numberofBoreholesinXDirection) {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->setNumberofBoreholesinXDirection(numberofBoreholesinXDirection);
}

bool GroundHeatExchangerVerticalArray::setNumberofBoreholesinYDirection(int numberofBoreholesinYDirection) {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->setNumberofBoreholesinYDirection(numberofBoreholesinYDirection);
}

bool GroundHeatExchangerVerticalArray::setBoreholeSpacing(double boreholeSpacing) {
  return getImpl<detail::GroundHeatExchangerVerticalArray_Impl>()->setBoreholeSpacing(boreholeSpacing);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int GroundHeatExchangerVerticalArray_Impl::numberofBoreholesinXDirection() const {
  const auto value = getInt(openstudio::GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinXDirection, true);
  OS_ASSERT(value);
  return *value;
}

int GroundHeatExchangerVerticalArray_Impl::numberofBoreholesinYDirection() const {
  const auto value = getInt(openstudio::GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinYDirection, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalArray_Impl::boreholeSpacing() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_ArrayFields::BoreholeSpacing, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatExchangerVerticalArray_Impl::setNumberofBoreholesinXDirection(int numberofBoreholesinXDirection) {
  return setInt(openstudio::GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinXDirection, numberofBoreholesinXDirection);
}

bool GroundHeatExchangerVerticalArray_Impl::setNumberofBoreholesinYDirection(int numberofBoreholesinYDirection) {
  return setInt(openstudio::GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinYDirection, numberofBoreholesinYDirection);
}

bool GroundHeatExchangerVerticalArray_Impl::setBoreholeSpacing(double boreholeSpacing) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_ArrayFields::BoreholeSpacing, boreholeSpacing);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
