#!/usr/bin/env python3

import cgi
import os

print("Content-type: text/html\r\n")

form = cgi.FieldStorage()

if "file" in form:
	fileitem = form["file"]
	if fileitem.filename:
		filename = os.path.basename(fileitem.filename)
		os.makedirs("uploads", exist_ok=True)
		with open (f"uploads/{filename}", "wb") as f:
			f.write(fileitem.file.read())
		print(f"<h1>File '{filename}' uploaded successfully!</h1>")
	else:
		print("<h1>No files selected!</h1>")
else:
	print(""" 
	<form enctype="multipart/form-data" method="post">
		<input type="file" name="file" />
		<input type="submit" value="Upload" />
	</form>
	""")
