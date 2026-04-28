/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferSlabInsulation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferSlabInsulation_Impl() override = default;

      double rINSRvalueofunderslabinsulation() const;
      bool isRINSRvalueofunderslabinsulationDefaulted() const;
      bool setRINSRvalueofunderslabinsulation(double rINSRvalueofunderslabinsulation);
      void resetRINSRvalueofunderslabinsulation();

      double dINSWidthofstripofunderslabinsulation() const;
      bool isDINSWidthofstripofunderslabinsulationDefaulted() const;
      bool setDINSWidthofstripofunderslabinsulation(double dINSWidthofstripofunderslabinsulation);
      void resetDINSWidthofstripofunderslabinsulation();

      double rVINSRvalueofverticalinsulation() const;
      bool isRVINSRvalueofverticalinsulationDefaulted() const;
      bool setRVINSRvalueofverticalinsulation(double rVINSRvalueofverticalinsulation);
      void resetRVINSRvalueofverticalinsulation();

      double zVINSDepthofverticalinsulation() const;
      bool isZVINSDepthofverticalinsulationDefaulted() const;
      bool setZVINSDepthofverticalinsulation(double zVINSDepthofverticalinsulation);
      void resetZVINSDepthofverticalinsulation();

      std::string iVINSFlagIsthereverticalinsulation() const;
      bool isIVINSFlagIsthereverticalinsulationDefaulted() const;
      bool setIVINSFlagIsthereverticalinsulation(const std::string& iVINSFlagIsthereverticalinsulation);
      void resetIVINSFlagIsthereverticalinsulation();

      std::vector<std::string> iVINSFlagIsthereverticalinsulationValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
