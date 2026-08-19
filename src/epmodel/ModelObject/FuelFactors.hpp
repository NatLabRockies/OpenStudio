/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FUELFACTORS_HPP
#define EPMODEL_FUELFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FuelFactors_Impl;
  }

  /** \brief Represents <code>FuelFactors</code>.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#fuelfactors,FuelFactors}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::FuelFactors</code>.
   * **Not yet available:** Model relationship and extensible-list conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API FuelFactors : public ModelObject
  {
   public:
    explicit FuelFactors(const Model& model);

    virtual ~FuelFactors() override = default;
    FuelFactors(const FuelFactors& other) = default;
    FuelFactors(FuelFactors&& other) = default;
    FuelFactors& operator=(const FuelFactors&) = default;
    FuelFactors& operator=(FuelFactors&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> existingFuelResourceNameValues();
    std::string existingFuelResourceName() const;
    bool setExistingFuelResourceName(const std::string& existingFuelResourceName);

    double sourceEnergyFactor() const;
    bool setSourceEnergyFactor(double sourceEnergyFactor);

    double cO2EmissionFactor() const;
    bool setCO2EmissionFactor(double cO2EmissionFactor);

    double cOEmissionFactor() const;
    bool setCOEmissionFactor(double cOEmissionFactor);

    double cH4EmissionFactor() const;
    bool setCH4EmissionFactor(double cH4EmissionFactor);

    double nOxEmissionFactor() const;
    bool setNOxEmissionFactor(double nOxEmissionFactor);

    double n2OEmissionFactor() const;
    bool setN2OEmissionFactor(double n2OEmissionFactor);

    double sO2EmissionFactor() const;
    bool setSO2EmissionFactor(double sO2EmissionFactor);

    double pMEmissionFactor() const;
    bool setPMEmissionFactor(double pMEmissionFactor);

    double pM10EmissionFactor() const;
    bool setPM10EmissionFactor(double pM10EmissionFactor);

    double pM25EmissionFactor() const;
    bool setPM25EmissionFactor(double pM25EmissionFactor);

    double nH3EmissionFactor() const;
    bool setNH3EmissionFactor(double nH3EmissionFactor);

    double nMVOCEmissionFactor() const;
    bool setNMVOCEmissionFactor(double nMVOCEmissionFactor);

    double hgEmissionFactor() const;
    bool setHgEmissionFactor(double hgEmissionFactor);

    double pbEmissionFactor() const;
    bool setPbEmissionFactor(double pbEmissionFactor);

    double waterEmissionFactor() const;
    bool setWaterEmissionFactor(double waterEmissionFactor);

    double nuclearHighLevelEmissionFactor() const;
    bool setNuclearHighLevelEmissionFactor(double nuclearHighLevelEmissionFactor);

    double nuclearLowLevelEmissionFactor() const;
    bool setNuclearLowLevelEmissionFactor(double nuclearLowLevelEmissionFactor);

   protected:
    using ImplType = detail::FuelFactors_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FuelFactors(std::shared_ptr<detail::FuelFactors_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
