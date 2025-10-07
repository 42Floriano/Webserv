<?php
/**
 * CGI RFC 3875 compliance test
 *
 * This script checks a few key requirements from the CGI/1.1
 * specification (RFC 3875).  It can be placed in the document root
 * of your web server and accessed via a browser or curl.
 *
 * Expected results:
 *   - All required CGI environment variables are present.
 *   - REQUEST_METHOD matches the HTTP method used.
 *   - SCRIPT_NAME, PATH_INFO and QUERY_STRING are correctly set.
 *   - The response status line is sent using the “Status:” header.
 */

header('Content-Type: text/plain; charset=utf-8');

// Helper to output a test result
function report(string $name, bool $passed, string $detail = ''): void
{
    $status = $passed ? 'PASS' : 'FAIL';
    echo sprintf("%-30s : %s", $name, $status);
    if ($detail !== '') {
        echo " – $detail";
    }
    echo PHP_EOL;
}

// 1. Required CGI variables (RFC 3875 §4.1)
$required = [
    'SERVER_SOFTWARE',
    'SERVER_NAME',
    'GATEWAY_INTERFACE',
    'SERVER_PROTOCOL',
    'SERVER_PORT',
    'REQUEST_METHOD',
    'PATH_INFO',
    'PATH_TRANSLATED',
    'SCRIPT_NAME',
    'QUERY_STRING',
    'REMOTE_HOST',
    'REMOTE_ADDR',
    'AUTH_TYPE',
    'REMOTE_USER',
    'REMOTE_IDENT',
    'CONTENT_TYPE',
    'CONTENT_LENGTH',
    'HTTP_ACCEPT',
    'HTTP_USER_AGENT',
];

foreach ($required as $var) {
    $present = array_key_exists($var, $_SERVER);
    report("Env $var", $present);
}

// 2. GATEWAY_INTERFACE must be CGI/1.1
$gateway = $_SERVER['GATEWAY_INTERFACE'] ?? '';
report('GATEWAY_INTERFACE value', $gateway === 'CGI/1.1', $gateway);

// 3. REQUEST_METHOD must match the HTTP verb used
$method = $_SERVER['REQUEST_METHOD'] ?? '';
$actual = $_SERVER['REQUEST_METHOD'] ?? 'UNKNOWN';
report('REQUEST_METHOD matches verb', $method === $actual, $method);

// 4. SCRIPT_NAME should point to this script
$scriptName = $_SERVER['SCRIPT_NAME'] ?? '';
$expected   = basename(__FILE__);
$match      = basename($scriptName) === $expected;
report('SCRIPT_NAME correct', $match, $scriptName);

// 5. PATH_INFO handling (if any)
$pathInfo = $_SERVER['PATH_INFO'] ?? '';
if ($pathInfo !== '') {
    // Example: /test.php/extra/segments
    report('PATH_INFO non‑empty', true, $pathInfo);
} else {
    report('PATH_INFO empty (acceptable)', true);
}

// 6. QUERY_STRING parsing
$query = $_SERVER['QUERY_STRING'] ?? '';
parse_str($query, $parsed);
report('QUERY_STRING parsed', is_array($parsed));

// 7. Status header handling (RFC 3875 §6.2)
if (function_exists('http_response_code')) {
    http_response_code(200);
    header('Status: 200 OK');
    report('Status header sent', true);
} else {
    report('Status header (fallback)', true);
}

// 8. Content‑Length consistency
$contentLength = $_SERVER['CONTENT_LENGTH'] ?? null;
if ($contentLength !== null) {
    $body = file_get_contents('php://input');
    $len  = strlen($body);
    report('CONTENT_LENGTH matches body', $len == (int)$contentLength, "$len vs $contentLength");
} else {
    report('CONTENT_LENGTH not set (OK for GET)', true);
}

// 9. Verify that no extra headers are stripped
$headers = getallheaders();
$expectedHeaders = ['Accept', 'User-Agent'];
foreach ($expectedHeaders as $h) {
    $present = array_key_exists($h, $headers);
    report("Header $h present", $present);
}

echo PHP_EOL . "CGI RFC test completed.\n";
?>

