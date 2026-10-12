#!/usr/bin/env bash
# Translator implemented via AWK for simpler parsing

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 example.c" >&2
  exit 1
fi

awk '
function trim(s) { gsub(/^[ \t]+|[ \t]+$/, "", s); return s }
BEGIN { print "#!/usr/bin/env bash"; }
{
  line = trim($0)
  if (line == "") next
  # handle a combined close+else+open like: "} else {"
  if (match(line, /^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$/)) { print "else"; next }
  if (line ~ /^#/) { print "# " line; next }
  if (line ~ /^(int|void)[ \t]+main[ \t]*\(.*\)/) next

  # int var = value;
  if (match(line, /^[ \t]*int[ \t]+([A-Za-z_][A-Za-z0-9_]*)[ \t]*=[ \t]*(.*);[ \t]*$/, m)) {
    var = m[1]; val = m[2]; print var "=" val; next
  }
  # int var;
  if (match(line, /^[ \t]*int[ \t]+([A-Za-z_][A-Za-z0-9_]*)[ \t]*;[ \t]*$/, m)) {
    print m[1] "="; next
  }
  # printf("text\n");
  if (match(line, /^[ \t]*printf\("([^"]*)"\)[ \t]*;[ \t]*$/, m)) {
    gsub(/"/, "\"", m[1]); print "echo -e \"" m[1] "\""; next
  }
  # printf("fmt", var);
  if (match(line, /^[ \t]*printf\("([^"]*)"[ \t]*,[ \t]*([A-Za-z_][A-Za-z0-9_]*)\)[ \t]*;[ \t]*$/, m)) {
    fmt = m[1]; var = m[2]; gsub(/%[dfs]/, "%s", fmt); gsub(/"/, "\\\"", fmt)
    print "printf \"" fmt "\\n\" \"\$" var "\""; next
  }
  # scanf("%d", &var);
  if (match(line, /^[ \t]*scanf\("%d"[ \t]*,[ \t]*&?([A-Za-z_][A-Za-z0-9_]*)\)[ \t]*;[ \t]*$/, m)) {
    print "read " m[1]; next
  }
  # if (a < b) {
  if (match(line, /^[ \t]*if[ \t]*\(([^)]+)\)[ \t]*\{[ \t]*$/, m)) {
    cond = m[1]
      # handle "} else {" on single line
      if (match(line, /^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$/)) { print "else"; next }
    if (match(cond, /^[ \t]*([A-Za-z_][A-Za-z0-9_]*)[ \t]*(==|!=|<=|>=|<|>)[ \t]*([A-Za-z_0-9]+)[ \t]*$/, c)) {
      left=c[1]; op=c[2]; right=c[3]
      if (op=="==") op2="-eq"
      else if (op=="!=") op2="-ne"
      else if (op=="<") op2="-lt"
      else if (op==">") op2="-gt"
      else if (op=="<=") op2="-le"
      else if (op==">=") op2="-ge"
      lefts = "\"\$" left "\""
      if (right ~ /^[0-9]+$/) rights = "\"" right "\""; else rights = "\"\$" right "\""
      print "if [ " lefts " " op2 " " rights " ]; then"
    } else {
      print "echo \"[diagnostic] Unsupported condition: " cond "\" >&2"
      print "if true; then"
    }
    stack[++st] = "if"; next
  }
  # else {
  if (match(line, /^[ \t]*else[ \t]*\{[ \t]*$/)) { print "else"; next }
  # while (cond) {
  if (match(line, /^[ \t]*while[ \t]*\(([^)]+)\)[ \t]*\{[ \t]*$/, m)) {
    cond = m[1]
      # handle "} else {" on single line
      if (match(line, /^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$/)) { print "else"; next }
    if (match(cond, /^[ \t]*([A-Za-z_][A-Za-z0-9_]*)[ \t]*(==|!=|<=|>=|<|>)[ \t]*([A-Za-z_0-9]+)[ \t]*$/, c)) {
      left=c[1]; op=c[2]; right=c[3]
      if (op=="==") op2="-eq"
      else if (op=="!=") op2="-ne"
      else if (op=="<") op2="-lt"
      else if (op==">") op2="-gt"
      else if (op=="<=") op2="-le"
      else if (op==">=") op2="-ge"
      lefts = "\"\$" left "\""
      if (right ~ /^[0-9]+$/) rights = "\"" right "\""; else rights = "\"\$" right "\""
      print "while [ " lefts " " op2 " " rights " ]; do"
    } else {
      print "echo \"[diagnostic] Unsupported condition: " cond "\" >&2"
      print "while true; do"
    }
    stack[++st] = "while"; next
  }
  # for(init; cond; incr) {
  if (match(line, /^[ \t]*for[ \t]*\(([^;]+);([^;]+);([^)]+)\)[ \t]*\{[ \t]*$/, m)) {
    init = m[1]; cond = m[2]; incr = m[3]
    gsub(/^[ \t]+|[ \t]+$/, "", init)
    gsub(/^int[ \t]+/, "", init)
    print init
    if (match(cond, /^[ \t]*([A-Za-z_][A-Za-z0-9_]*)[ \t]*(==|!=|<=|>=|<|>)[ \t]*([A-Za-z_0-9]+)[ \t]*$/, c)) {
      left=c[1]; op=c[2]; right=c[3]
      if (op=="==") op2="-eq"
      else if (op=="!=") op2="-ne"
      else if (op=="<") op2="-lt"
      else if (op==">") op2="-gt"
      else if (op=="<=") op2="-le"
      else if (op==">=") op2="-ge"
      print "while [ \"\$" left "\" " op2 " \"" right "\" ]; do"
      stack[++st] = "for::" incr
    } else {
      print "echo \"[diagnostic] Unsupported for-cond: " cond "\" >&2"
      print "while true; do"
      stack[++st] = "for::" incr
    }
    next
  }
  # closing brace
  if (match(line, /^[ \t]*\}[ \t]*$/)) {
    if (st <= 0) { next }
    typ = stack[st--]
    if (typ == "if") print "fi"
    else if (typ == "while") print "done"
    else if (typ ~ /^for::/) { sub(/^for::/, "", typ); print typ; print "done" }
    else print "# }"
    next
  }
  # return N;
  if (match(line, /^[ \t]*return[ \t]+([0-9]+)[ \t]*;[ \t]*$/, m)) { print "exit " m[1]; next }
  # fallback: strip trailing semicolon
  gsub(/;[ \t]*$/, "", line)
  print line
}
' "$1"

