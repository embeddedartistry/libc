cmd = 'vale --config documentation.vale.ini --output=line --sort --normalize --relative'

When(/^Doc test "(.*)"$/) do |rule|
  step %(I cd to "../../fixtures/#{rule}")
  step %(I run `#{cmd} .`)
end
