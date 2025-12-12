#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

people_def = PeopleDefinition.new(m)
people = People.new(people_def)
clo_sch = OpenStudio::Model::ScheduleConstant.new(m)
clo_sch.setName("Clothing Insulation Schedule")
people.setClothingInsulationSchedule(clo_sch)

m.save('test_vt_People.osm', true)
