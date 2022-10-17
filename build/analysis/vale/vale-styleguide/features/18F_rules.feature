Feature: Rules

  Scenario: Craft sentences at 25 words or fewer, whenever possible.
    When I test "SentenceLength"
    Then the output should contain exactly:
      """
      test.md:3:53:18F.SentenceLength:Craft sentences at 25 words or fewer, whenever possible.
      """

  Scenario: Heading capitalization
    When I test "Headings"
    Then the output should contain exactly:
      """
      test.md:5:4:18F.Headings:'This Is Not In Sentence Case' should be in sentence case.
      """

  Scenario: Use of contractions
    When I test "Contractions"
    Then the output should contain exactly:
      """
      test.md:3:1:18F.Contractions:Use "that's" instead of "That is".
      """

  Scenario: Acronym defintions
    When I test "UnexpandedAcronyms"
    Then the output should contain exactly:
      """
      test.md:5:38:18F.UnexpandedAcronyms:'DOJJ' should be parenthetically defined.
      """

  Scenario: Punctuation and quotations
    When I test "Quotes"
    Then the output should contain exactly:
      """
      test.md:6:25:18F.Quotes:Punctuation should be inside the quotes.
      """

  Scenario: Sentence spacing
    When I test "Spacing"
    Then the output should contain exactly:
      """
      test.md:1:43:18F.Spacing:'. T' should have one space.
      test.md:3:18:18F.Spacing:'.W' should have one space.
      """

  Scenario: Use of trademarks
    When I test "Brands"
    Then the output should contain exactly:
      """
      test.md:1:17:18F.Brands:Use 'tissue' instead of 'Kleenex'.
      """

  Scenario: Hyphenated ages
    When I test "Ages"
    Then the output should contain exactly:
      """
      test.md:1:28:18F.Ages:Avoid hyphens in ages unless it clarifies the text.
      """

  Scenario: Words to avoid
    When I test "Clarity"
    Then the output should contain exactly:
      """
      test.md:1:16:18F.Clarity:Avoid using 'deploy', unless you’re talking about the military or software.
      """

  Scenario: Punctuation in abbreviations
    When I test "Abbreviations"
    Then the output should contain exactly:
      """
      test.md:1:18:18F.Abbreviations:Use 'U.S.' instead of 'USA'.
      """

  Scenario: Specific words and phrases
    When I test "Terms"
    Then the output should contain exactly:
      """
      test.md:1:7:18F.Terms:Prefer 'back end' over 'back-end'.
      """

  Scenario: 'to-do' vs. 'to do'
    When I test "ToDo"
    Then the output should contain exactly:
      """
      test.md:1:12:18F.ToDo:Use 'to-do' instead of 'to do'.
      """

  Scenario: 'drop down' vs. 'drop-down'.
    When I test "DropDown"
    Then the output should contain exactly:
      """
      test.md:1:27:18F.DropDown:Use 'drop-down' instead of 'drop down'.
      test.md:3:27:18F.DropDown:Use 'drop down' instead of 'drop-down'.
      test.md:5:9:18F.DropDown:Use 'drop-down' or 'drop down' instead of 'dropdown'.
      """
