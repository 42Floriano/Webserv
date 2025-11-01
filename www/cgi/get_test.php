#!/usr/bin/php
<?php
// get_test.php
// curl a lancer : curl -i "http://127.0.0.1:8080/cgi/get_test.php?name=Mathieu&test=ok"

header('Content-Type: text/html; charset=utf-8');

function h($s) {
    return htmlspecialchars((string)$s, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8');
}

echo "<!doctype html>\n<html><head><meta charset='utf-8'><title>GET Test</title></head><body>";
echo "<h1>GET Test CGI Script (PHP)</h1>";

echo "<h2>Variables d'environnement</h2><pre>";
foreach ($_SERVER as $k => $v) {
    echo h($k) . " = " . h($v) . "\n";
}
echo "</pre>";

echo "<h2>Paramètres GET</h2>";
if (!empty($_GET)) {
    echo "<ul>";
    foreach ($_GET as $k => $v) {
        echo "<li><strong>" . h($k) . "</strong> = " . h($v) . "</li>";
    }
    echo "</ul>";
} else {
    echo "<p>(aucun paramètre GET)</p>";
}

echo "<h2>Raw QUERY_STRING</h2><pre>" . h($_SERVER['QUERY_STRING'] ?? '') . "</pre>";

echo "</body></html>";
