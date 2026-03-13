/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALARRAY_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALARRAY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerVerticalArray_Impl;
  }

  class EPMODEL_API GroundHeatExchangerVerticalArray : public ModelObject
  {
   public:
    explicit GroundHeatExchangerVerticalArray(const Model& model);

    virtual ~GroundHeatExchangerVerticalArray() override = default;
    GroundHeatExchangerVerticalArray(const GroundHeatExchangerVerticalArray& other) = default;
    GroundHeatExchangerVerticalArray(GroundHeatExchangerVerticalArray&& other) = default;
    GroundHeatExchangerVerticalArray& operator=(const GroundHeatExchangerVerticalArray&) = default;
    GroundHeatExchangerVerticalArray& operator=(GroundHeatExchangerVerticalArray&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Vertical:Array numeric fields.
    // - Field Mapping: GHE:Vertical:Properties Object Name is an object-list relationship field and is excluded.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    int numberofBoreholesinXDirection() const;
    bool setNumberofBoreholesinXDirection(int numberofBoreholesinXDirection);

    int numberofBoreholesinYDirection() const;
    bool setNumberofBoreholesinYDirection(int numberofBoreholesinYDirection);

    double boreholeSpacing() const;
    bool setBoreholeSpacing(double boreholeSpacing);

   protected:
    using ImplType = detail::GroundHeatExchangerVerticalArray_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerVerticalArray(std::shared_ptr<detail::GroundHeatExchangerVerticalArray_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
