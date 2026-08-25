# insert your copyright here

require 'openstudio'
require 'minitest/autorun'
require 'fileutils'

require_relative '../measure'

class ModelMeasureNameTest < Minitest::Test
  # def setup
  # end

  # def teardown
  # end

  def test_number_of_arguments_and_argument_names
    # create an instance of the measure
    measure = ModelMeasureName.new

    # make an empty model
    model = OpenStudio::EPModel::Model.new

    # get arguments and test that they are what we are expecting
    arguments = measure.arguments(model)
    assert_equal(1, arguments.size)
    assert_equal('space_name', arguments[0].name)
  end

  def test_bad_argument_values
    # create an instance of the measure
    measure = ModelMeasureName.new

    # create runner with empty OSW
    osw = OpenStudio::WorkflowJSON.new
    runner = OpenStudio::Measure::OSRunner.new(osw)

    # make an empty model
    model = OpenStudio::EPModel::Model.new

    # get arguments
    arguments = measure.arguments(model)
    argument_map = OpenStudio::Measure.convertOSArgumentVectorToMap(arguments)

    # create hash of argument values
    args_hash = {}
    args_hash['space_name'] = ''

    # populate argument with specified hash value if specified
    arguments.each do |arg|
      temp_arg_var = arg.clone
      if args_hash.key?(arg.name)
        assert(temp_arg_var.setValue(args_hash[arg.name]))
      end
      argument_map[arg.name] = temp_arg_var
    end

    # run the measure
    measure.run(model, runner, argument_map)
    result = runner.result

    # show the output
    result.showOutput

    # assert that it did fail
    assert_equal('Fail', result.value.valueName)
    assert_equal(1, result.stepErrors.size)
    assert_match(/empty space name/i, result.stepErrors.first)
  end

  def test_good_argument_values
    # create an instance of the measure
    measure = ModelMeasureName.new

    # create runner with empty OSW
    osw = OpenStudio::WorkflowJSON.new
    runner = OpenStudio::Measure::OSRunner.new(osw)

    # create a small seed model
    model = OpenStudio::EPModel::Model.new
    4.times do |index|
      space = OpenStudio::EPModel::Space.new(model)
      space.setName("Seed Space #{index + 1}")
    end

    # store the number of spaces in the seed model
    num_spaces_seed = model.getSpaces.size

    # get arguments
    arguments = measure.arguments(model)
    argument_map = OpenStudio::Measure.convertOSArgumentVectorToMap(arguments)

    # create hash of argument values.
    # If the argument has a default that you want to use, you don't need it in the hash
    args_hash = {}
    args_hash['space_name'] = 'New Space'
    # using defaults values from measure.rb for other arguments

    # populate argument with specified hash value if specified
    arguments.each do |arg|
      temp_arg_var = arg.clone
      if args_hash.key?(arg.name)
        assert(temp_arg_var.setValue(args_hash[arg.name]))
      end
      argument_map[arg.name] = temp_arg_var
    end

    # Ensure the model did not start with a space named like requested
    refute_includes(model.getSpaces.map(&:nameString), "New Space")

    # run the measure
    measure.run(model, runner, argument_map)
    result = runner.result

    # show the output
    result.showOutput

    # assert that it ran correctly
    assert_equal('Success', result.value.valueName)
    assert_equal(1, result.stepInfo.size)
    assert_empty(result.stepWarnings)

    # check that there is now 1 extra space
    assert_equal(1, model.getSpaces.size - num_spaces_seed)
    assert_includes(model.getSpaces.map(&:nameString), "New Space")

    refute_empty(result.stepInitialCondition)
    assert_equal('The building started with 4 spaces.', result.stepInitialCondition.get)

    refute_empty(result.stepFinalCondition)
    assert_equal('The building finished with 5 spaces.', result.stepFinalCondition.get)

    # save the model to test output directory
    output_directory = "#{File.dirname(__FILE__)}/output"
    FileUtils.mkdir_p(output_directory)
    model.save(OpenStudio::Path.new("#{output_directory}/test_output.idf"), true)
  end
end
