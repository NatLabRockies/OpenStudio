/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCOMPRESSOR_HPP
#define EPMODEL_REFRIGERATIONCOMPRESSOR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCompressor_Impl;
  }

/** \brief Defines a compressor used by a refrigeration system.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationcompressor,Refrigeration:Compressor}
 *
 * \par Important behavior
 * Rated superheat, return-gas, liquid, subcooling, operation mode, and end-use fields are stored directly on the object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationCompressor</code>.
 * <b>Not yet available:</b> Compressor-capacity and power-curve relationships and refrigeration-system attachment/removal methods are not exposed.
 *
 * \par Known limitations
 * System membership and compressor staging are managed by the referencing refrigeration-system object.
 */
  class EPMODEL_API RefrigerationCompressor : public ParentObject
  {
   public:
    explicit RefrigerationCompressor(const Model& model);

    virtual ~RefrigerationCompressor() override = default;
    RefrigerationCompressor(const RefrigerationCompressor&) = default;
    RefrigerationCompressor(RefrigerationCompressor&&) = default;
    RefrigerationCompressor& operator=(const RefrigerationCompressor&) = default;
    RefrigerationCompressor& operator=(RefrigerationCompressor&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> modeofOperationValues();


    /** @name Scalar Accessors */
    //@{

    // Rated Superheat
    boost::optional<double> ratedSuperheat() const;
    bool setRatedSuperheat(double ratedSuperheat);
    void resetRatedSuperheat();

    // Rated Return Gas Temperature
    boost::optional<double> ratedReturnGasTemperature() const;
    bool setRatedReturnGasTemperature(double ratedReturnGasTemperature);
    void resetRatedReturnGasTemperature();

    // Rated Liquid Temperature
    boost::optional<double> ratedLiquidTemperature() const;
    bool setRatedLiquidTemperature(double ratedLiquidTemperature);
    void resetRatedLiquidTemperature();

    // Rated Subcooling
    boost::optional<double> ratedSubcooling() const;
    bool setRatedSubcooling(double ratedSubcooling);
    void resetRatedSubcooling();

    // End-use Subcategory
    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    // Mode of Operation
    std::string modeofOperation() const;
    bool isModeofOperationDefaulted() const;
    bool setModeofOperation(const std::string& modeofOperation);
    void resetModeofOperation();

    //@}

   protected:
    using ImplType = detail::RefrigerationCompressor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationCompressor(std::shared_ptr<detail::RefrigerationCompressor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
