<?php
// Set the content type to text/plain
header("Content-Type: text/plain");

// Output a simple message
echo "Hello, this is a test of the CGI script!\n";

// Display server and environment variables
echo "Server Information:\n";
foreach ($_SERVER as $key => $value) {
    echo "$key: $value\n";
}
?>
