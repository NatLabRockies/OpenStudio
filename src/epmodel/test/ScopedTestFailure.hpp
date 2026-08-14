/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TEST_SCOPEDTESTFAILURE_HPP
#define EPMODEL_TEST_SCOPEDTESTFAILURE_HPP

#include "../Model.hpp"
#include "../Model_Impl.hpp"
#include "../TestFailurePoint.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {
namespace test {

  class ScopedTestFailure
  {
   public:
    ScopedTestFailure(const Model& model, detail::TestFailurePoint point)
      : m_modelImpl(model.getImpl<detail::Model_Impl>()), m_previousPoint(m_modelImpl->m_testFailurePoint) {
      OS_ASSERT(point != detail::TestFailurePoint::None);
      m_modelImpl->m_testFailurePoint = point;
    }

    ScopedTestFailure(const ScopedTestFailure&) = delete;
    ScopedTestFailure& operator=(const ScopedTestFailure&) = delete;
    ScopedTestFailure(ScopedTestFailure&&) = delete;
    ScopedTestFailure& operator=(ScopedTestFailure&&) = delete;

    ~ScopedTestFailure() {
      m_modelImpl->m_testFailurePoint = m_previousPoint;
    }

   private:
    std::shared_ptr<detail::Model_Impl> m_modelImpl;
    detail::TestFailurePoint m_previousPoint;
  };

}  // namespace test
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_TEST_SCOPEDTESTFAILURE_HPP
