Feature: Rules

  Scenario: Craft sentences at 25 words or fewer, whenever possible.
    When Blog test "SentenceLength"
    Then the output should contain exactly:
      """
      test.md:3:53:blog.SentenceLength:Craft sentences at 25 words or fewer, whenever possible.
      """

  Scenario: Heading capitalization
    When Blog test "Headings"
    Then the output should contain exactly:
      """
      test.md:5:4:blog.Headings:'This Is Not In Sentence Case' should be in sentence case.
      """

  Scenario: Use of contractions
    When Blog test "Contractions"
    Then the output should contain exactly:
      """
      test.md:3:1:blog.Contractions:Use "that's" instead of "That is".
      """

  Scenario: Acronym defintions
    When Blog test "UnexpandedAcronyms"
    Then the output should contain exactly:
      """
      test.md:5:38:blog.UnexpandedAcronyms:'DOJJ' should be parenthetically defined.
      """

  Scenario: Punctuation and quotations
    When Blog test "Quotes"
    Then the output should contain exactly:
      """
      test.md:6:25:blog.Quotes:Punctuation should be inside the quotes.
      """

  Scenario: Sentence spacing
    When Blog test "Spacing"
    Then the output should contain exactly:
      """
      test.md:1:43:blog.Spacing:'. T' should have one space.
      test.md:3:18:blog.Spacing:'.W' should have one space.
      """

  Scenario: Use of trademarks
    When Blog test "Brands"
    Then the output should contain exactly:
      """
      test.md:1:17:blog.Brands:Use 'tissue' instead of 'Kleenex'.
      """

  Scenario: Hyphenated ages
    When Blog test "Ages"
    Then the output should contain exactly:
      """
      test.md:1:28:blog.Ages:Avoid hyphens in ages unless it clarifies the text.
      """

  Scenario: Words to avoid
    When Blog test "Clarity"
    Then the output should contain exactly:
      """
      test.md:1:16:blog.Clarity:Avoid using 'deploy', unless you’re talking about the military or software.
      """

  Scenario: Punctuation in abbreviations
    When Blog test "Abbreviations"
    Then the output should contain exactly:
      """
      test.md:1:18:blog.Abbreviations:Use 'U.S.' instead of 'USA'.
      """

  Scenario: Specific words and phrases
    When Blog test "Terms"
    Then the output should contain exactly:
      """
      test.md:1:7:blog.Terms:Prefer 'back end' over 'back-end'.
      """

  Scenario: 'to-do' vs. 'to do'
    When Blog test "ToDo"
    Then the output should contain exactly:
      """
      test.md:1:12:blog.ToDo:Use 'to-do' instead of 'to do'.
      """

  Scenario: 'drop down' vs. 'drop-down'.
    When Blog test "DropDown"
    Then the output should contain exactly:
      """
      test.md:1:27:blog.DropDown:Use 'drop-down' instead of 'drop down'.
      test.md:3:27:blog.DropDown:Use 'drop down' instead of 'drop-down'.
      test.md:5:9:blog.DropDown:Use 'drop-down' or 'drop down' instead of 'dropdown'.
      """
