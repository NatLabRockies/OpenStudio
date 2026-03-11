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

    // Schema Alignment Notes:
    // - API: preserve openstudio::model::RefrigerationCompressor scalar accessors for the numeric rating fields plus end-use subcategory
    //   and mode of operation.
    // - Field Mapping: these scalars map directly to Refrigeration:Compressor fields enumerated in Refrigeration_Compressor_FieldEnums and
    //   are confirmed by ForwardTranslateRefrigerationCompressor.cpp.
    // - Field Mapping: curve attachment fields (Refrigeration Compressor Power Curve Name, Refrigeration Compressor Capacity Curve Name,
    //   Transcritical Compressor Power Curve Name, Transcritical Compressor Capacity Curve Name) remain relationship-like and are excluded
    //   from this scalar-only scaffold.

    /** @name Getters */
    //@{
    boost::optional<double> ratedSuperheat() const;
    boost::optional<double> ratedReturnGasTemperature() const;
    boost::optional<double> ratedLiquidTemperature() const;
    boost::optional<double> ratedSubcooling() const;

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;

    std::string modeofOperation() const;
    bool isModeofOperationDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setRatedSuperheat(double ratedSuperheat);
    void resetRatedSuperheat();

    bool setRatedReturnGasTemperature(double ratedReturnGasTemperature);
    void resetRatedReturnGasTemperature();

    bool setRatedLiquidTemperature(double ratedLiquidTemperature);
    void resetRatedLiquidTemperature();

    bool setRatedSubcooling(double ratedSubcooling);
    void resetRatedSubcooling();

    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

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
