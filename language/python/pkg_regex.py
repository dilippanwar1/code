import re


# 're.RegexObject.findall(string[, pos[, endpos]])', where RegexObject is
# typically returned from re.compile().
def CompileFindall():
  TOKEN_REGEX_PATTERN = '{{(?P<token_name>[A-Za-z0-9_]+)}}'
  TEMPLATE_TOKEN_SUBSTRING_REGEX = re.compile(TOKEN_REGEX_PATTERN)
  TEMPLATE_TOKEN_FULL_MATCH_REGEX = re.compile('^%s$' % TOKEN_REGEX_PATTERN)

  values = ['notatoken', '{{atoken}}']
  # output: [] ['atoken']
  for value in values:
    print TEMPLATE_TOKEN_SUBSTRING_REGEX.findall(value),
  print


# re.sub(pattern, repl, string, count=0, flags=0). Replace `pattern` in
# `string` with `repl`, with optional `count` and `flag`.
def Substitute():
  print re.sub('.*a', 'b', 'aaaaaaaaabc') # bbc


if __name__ == "__main__":
  CompileFindall()
  Substitute()
