/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATRIXTWODIMENSION_HPP
#define EPMODEL_MATRIXTWODIMENSION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MatrixTwoDimension_Impl;
}

class EPMODEL_API MatrixTwoDimension : public ModelObject
{
 public:
  explicit MatrixTwoDimension(const Model& model);

  virtual ~MatrixTwoDimension() override = default;
  MatrixTwoDimension(const MatrixTwoDimension& other) = default;
  MatrixTwoDimension(MatrixTwoDimension&& other) = default;
  MatrixTwoDimension& operator=(const MatrixTwoDimension&) = default;
  MatrixTwoDimension& operator=(MatrixTwoDimension&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: numberofRows and numberofColumns map directly to Matrix:TwoDimension scalar fields.
  // - Field Mapping: Extensible Value entries are intentionally excluded from simple scalar accessor scaffolding.
  // - TODO(parity): Add non-scalar extensible APIs for matrix value data in a future parity pass.
  int numberofRows() const;
  bool setNumberofRows(int numberofRows);

  int numberofColumns() const;
  bool setNumberofColumns(int numberofColumns);

 protected:
  using ImplType = detail::MatrixTwoDimension_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MatrixTwoDimension(std::shared_ptr<detail::MatrixTwoDimension_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
