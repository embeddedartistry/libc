cmd = 'vale --config blog.vale.ini --output=line --sort --normalize --relative'

When(/^Blog test "(.*)"$/) do |rule|
  step %(I cd to "../../fixtures/#{rule}")
  step %(I run `#{cmd} .`)
end
