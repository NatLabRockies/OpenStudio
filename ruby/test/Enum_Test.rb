########################################################################################################################
#  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
#  See also https://openstudio.net/license
########################################################################################################################

require 'openstudio'

require 'minitest/autorun'

class Enum_Test < Minitest::Test

  # def setup
  # end

  # def teardown
  # end

  def test_idd_object_type
    e = OpenStudio::IddObjectType.new("LeadInput")
    assert_equal(e.value(), 2)
    assert_equal("LeadInput", e.valueName())
    assert_equal("Lead Input", e.valueDescription())

    e = "Site_Location".to_IddObjectType
    assert_equal("Site_Location", e.valueName())
    assert_equal("Site:Location", e.valueDescription())

    assert_raises(RuntimeError){"Bob".to_IddObjectType}
  end

  def test_enum_hash
    # Test for #5522
    m1 = OpenStudio::MeasureType.new("ModelMeasure")
    m2 = OpenStudio::MeasureType.new("ModelMeasure")
    m_other = OpenStudio::MeasureType.new("EnergyPlusMeasure")

    assert_equal(m1, m2)
    assert_equal(m1.hash, m2.hash)
    assert(m1.eql?(m2))
    refute_equal(m1, m_other)
    refute_equal(m1.hash, m_other.hash)
    refute(m1.eql?(m_other))

    measures = [m1, m2]
    assert_equal(1, measures.group_by { |m| m.value }.size)
    assert_equal(1, measures.group_by { |m| m }.size)

    measures << m_other
    assert_equal(2, measures.group_by { |m| m.value }.size)
    assert_equal(2, measures.group_by { |m| m }.size)
  end
end


