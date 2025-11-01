#!/bin/bash
# =====================================
# Webserv Single-Method Config Tester
# =====================================

SINGLE_DIR=../tester/configs/01_single_method
EXPECTED_DIR=${EXPECTED_DIR:-../tester/expected}
LOG_DIR=${LOG_DIR:-../tester/logs}
RESPONSE_DIR="$LOG_DIR/responses_single"
mkdir -p "$RESPONSE_DIR"

SINGLE_RESULT_FILE="$LOG_DIR/single_result.tmp"
> "$SINGLE_RESULT_FILE"

FAILED=0
PASSED=0

# --- Cleanup ---
cleanup() {
    if [ -n "$PID" ] && kill -0 "$PID" 2>/dev/null; then
        kill "$PID"
        wait "$PID" 2>/dev/null
    fi
}
trap cleanup EXIT

# --- Helper: compare response file with expected ---
compare_response() {
    local got="$1"
    local expected="$2"
    local label="$3"

    if [ ! -f "$expected" ]; then
        echo "⚠️ [$label] Expected file missing: $expected"
        return
    fi

    if cmp -s "$got" "$expected"; then
        echo "✅ [$label] Matches expected output"
        PASSED=$((PASSED+1))
    else
        echo "❌ [$label] Output differs from expected"
        diff -u "$expected" "$got" | head -n 10
        FAILED=1
    fi
}

# --- Helper: send and check request ---
test_request() {
    local method=$1
    local url=$2
    local expected_status=$3
    local label=$4
    local outfile="$RESPONSE_DIR/${method}_${label// /_}.html"

    STATUS=$(curl -s -D "$outfile.headers" -o "$outfile" -w "%{http_code}" -X "$method" "$url")
    if [ "$STATUS" -eq "$expected_status" ]; then
        echo "✅ [$method] $label ($STATUS)"
        PASSED=$((PASSED+1))
    else
        echo "❌ [$method] $label — expected $expected_status, got $STATUS"
        FAILED=1
    fi

    # Check error page content if applicable
    if [[ "$STATUS" -ge 400 ]]; then
        ERR_FILE="$EXPECTED_DIR/error_${STATUS}.html"
        if [ -f "$ERR_FILE" ]; then
            compare_response "$outfile" "$ERR_FILE" "$method $label error page"
        fi
    fi
}

# --- Loop through configs ---
for CONF in "$SINGLE_DIR"/*.conf; do
    CONF_NAME=$(basename "$CONF")
    echo ""
    echo "🧪 Testing single-method config: $CONF_NAME"
    echo "----------------------------------------"

    # Detect allowed method (portable for macOS & Linux)
    ALLOWED_METHOD=$(grep -E 'methods[[:space:]]+' "$CONF" | head -n 1 | sed -E 's/.*methods[[:space:]]+([A-Z]+).*/\1/')
    REDIRECT_PATH=$(grep -E 'return[[:space:]]+301' "$CONF" | head -n 1 | sed -E 's/.*return[[:space:]]+301[[:space:]]+([^;[:space:]]+).*/\1/')

    if [ -z "$ALLOWED_METHOD" ]; then
        echo "⚠️ Could not determine allowed method in $CONF_NAME — skipping"
        continue
    fi
    echo "→ Allowed method: $ALLOWED_METHOD"

    if [ -n "$REDIRECT_PATH" ]; then
        echo "→ Redirection route detected: 301 → $REDIRECT_PATH"
    fi

    # Launch server
    $VALGRIND_CMD $WEBSERV $LOG_FLAGS "$CONF" >"$LOG_DIR/${CONF_NAME%.conf}_single.log" 2>&1 &
    PID=$!
    sleep 1

    if ! kill -0 "$PID" 2>/dev/null; then
        echo "❌ Failed to start webserv for $CONF_NAME"
        FAILED=1
        continue
    fi

    URL="http://$SERVER_IP:$SERVER_PORT/"

    # --- Test methods based on config ---
    echo "→ Sending requests..."
    for METHOD in GET POST DELETE; do
        case "$METHOD" in
            GET)
                EXPECTED=$([[ "$ALLOWED_METHOD" == "GET" ]] && echo 200 || echo 405)
                test_request "GET" "$URL" "$EXPECTED" "root"
                ;;
            POST)
                echo "Test content" > /tmp/test_post.txt
                EXPECTED=$([[ "$ALLOWED_METHOD" == "POST" ]] && echo 201 || echo 405)
                STATUS=$(curl -s -o /dev/null -w "%{http_code}" -X POST -d @/tmp/test_post.txt "$URL")
                if [ "$STATUS" -eq "$EXPECTED" ]; then
                    echo "✅ [POST] root ($STATUS)"
                    PASSED=$((PASSED+1))
                else
                    echo "❌ [POST] root — expected $EXPECTED, got $STATUS"
                    FAILED=1
                fi
                ;;
            DELETE)
                EXPECTED=$([[ "$ALLOWED_METHOD" == "DELETE" ]] && echo 200 || echo 405)
                test_request "DELETE" "$URL" "$EXPECTED" "root"
                ;;
        esac
    done

    # --- Test redirect route if defined ---
    if [ -n "$REDIRECT_PATH" ]; then
        echo ""
        echo "→ Testing redirect route"
        REDIRECT_FILE="$RESPONSE_DIR/redirect_${CONF_NAME%.conf}.headers"
        STATUS=$(curl -s -D "$REDIRECT_FILE" -o /dev/null -w "%{http_code}" "$URL")

        if [ "$STATUS" -eq 301 ]; then
            echo "✅ [GET /] returned 301 redirect"
            LOCATION=$(grep -i "^Location:" "$REDIRECT_FILE" | tr -d '\r\n' | awk '{print $2}')
            if [ "$LOCATION" == "$REDIRECT_PATH" ]; then
                echo "✅ Redirect Location header is correct ($REDIRECT_PATH)"
                PASSED=$((PASSED+1))
            else
                echo "❌ Redirect Location header incorrect → '$LOCATION'"
                FAILED=1
            fi
        else
            echo "❌ [GET /] expected 301 but got $STATUS"
            FAILED=1
        fi
    fi

    echo "→ Stopping server..."
    kill "$PID"
    wait "$PID" 2>/dev/null
    echo "----------------------------------------"
done

# --- Final result ---
if [ "$FAILED" -eq 0 ]; then
    echo "✅ All single-method tests passed!"
    echo 0 > "$SINGLE_RESULT_FILE"
else
    echo "❌ Some single-method tests failed."
    echo 1 > "$SINGLE_RESULT_FILE"
fi

echo ""
echo "🧩 Single-method tests complete."
echo "Logs stored in $LOG_DIR"
echo "========================================"
exit $FAILED
