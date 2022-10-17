cmd = 'vale --output=line --sort --normalize --relative'

When(/^I test "(.*)"$/) do |rule|
  step %(I cd to "../../fixtures/#{rule}")
  step %(I run `#{cmd} .`)
end