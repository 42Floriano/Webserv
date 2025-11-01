#!/usr/bin/php
<?php
// CGI header
echo "diocane: " . $_SERVER['CONTENT_LENGTH'] . "\n";

header("Content-Type: text/plain");

// Read raw POST body from stdin
$stdin = fopen("php://input", "rb");
$body = stream_get_contents($stdin);
fclose($stdin);

// Print it back to the client
echo $body;