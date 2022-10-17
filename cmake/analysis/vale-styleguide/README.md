# vale-boilerplate [![Travis branch](https://img.shields.io/travis/errata-ai/vale-boilerplate.svg?style=flat-square)](https://travis-ci.org/errata-ai/vale-boilerplate) ![GitHub release](https://img.shields.io/github/release/ValeLint/vale.svg?style=flat-square) ![license](https://img.shields.io/github/license/mashape/apistatus.svg?style=flat-square)

This repository is meant to serve as a starting point for creating and maintaining your own [Vale-compatible](https://github.com/ValeLint/vale) style guide. It includes a (fairly) complete implementation of the [18F Content Guide](https://content-guide.18f.gov/), including example rules for all of Vale's [extension points](https://errata.ai/vale/styles/#extension-points) and a unit test suite using [Cucumber](https://cucumber.io/), [`yamllint`](https://github.com/adrienverge/yamllint), and [Travis CI](https://travis-ci.org/).

## Dependencies

### yamllint

You can install `yamllint` through Homebrew:

```
$ brew install yamllint
```

### Cucumber

To install Cucumber on OSX, run:

```
gem update --system
gem install rspec --no-ri --no-rdoc
gem install watir-webdriver --no-ri --no-rdoc
gem install cucumber --no-ri --no-rdoc
gem install aruba
```

## Repository Structure

<dl>
  <dt><a href="https://github.com/ValeLint/vale-boilerplate/tree/master/src/18F"><code>/src</code></a></dt>
  <dd>The <a href="http://yaml.org/">YAML</a>-based rule implementations that make up our style (in this case, 18F).</dd>

  <dt><a href="https://github.com/ValeLint/vale-boilerplate/tree/master/fixtures"><code>/fixtures</code></a></dt>
  <dd>The individual unit tests. Each directory should be named after a rule found in <code>/src</code> and include its own <code>.vale.ini</code> file that isolates its target rule.</dd>

  <dt><a href="https://github.com/ValeLint/vale-boilerplate/tree/master/features"><code>/features</code></a></dt>
  <dd>The <a href="https://github.com/cucumber/cucumber/wiki/Step-Definitions">Cucumber Step Definitions</a> we use to test our fixtures. Essentially, we use the <a href="https://github.com/cucumber/aruba">aruba</a> framework to test Vale's output after running it on each of our fixture directories.</dd>
</dl>

## Extension Points

|   `check`    |                    Implementation(s)                   |
|:------------:|:---------------------------------------------------:|
| [`existence`](https://errata-ai.github.io/vale/styles/#existence)  | [`Spacing.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/Spacing.yml) |
| [`substitution`](https://errata-ai.github.io/vale/styles/#substitution)  | [`Terms.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/Terms.yml), [`DropDown.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/DropDown.yml) (POS tags) |
| [`occurrence`](https://errata-ai.github.io/vale/styles/#occurrence)  | [`SentenceLength.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/SentenceLength.yml) |
| [`repetition`](https://errata-ai.github.io/vale/styles/#repetition)  | [`Repetition.yml`](https://github.com/ValeLint/vale/blob/master/rule/Repetition.yml) |
| [`consistency`](https://errata-ai.github.io/vale/styles/#consistency)  | [`Spelling.yml`](https://github.com/ValeLint/vale/blob/master/styles/demo/Spelling.yml) |
| [`capitalization`](https://errata-ai.github.io/vale/styles/#capitalization)  | [`Headings.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/Headings.yml) |
| [`readability`](https://errata-ai.github.io/vale/styles/#readability)  | [`Reading.yml`](https://github.com/ValeLint/vale/blob/master/styles/demo/Reading.yml) |
| [`conditional`](https://errata-ai.github.io/vale/styles/#conditional)  | [`UnexpandedAcronyms.yml`](https://github.com/ValeLint/vale-boilerplate/blob/master/src/18F/UnexpandedAcronyms.yml) |
| [`spelling`](https://errata-ai.github.io/vale/styles/#spelling)  | [`Spellcheck.yml`](https://github.com/ValeLint/vale/blob/master/styles/demo/Spellcheck.yml) |

## Test Process

To check the style guide, run the following commands:

* `yamllint src`
* `cucumber'
