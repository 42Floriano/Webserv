#!/bin/bash
# =====================================
# Webserv Tests for Working Configs
# =====================================

FAILED=0
PASSED=0
LEAKED=0
NO_LEAKS=0

compare_files() {
    local got="$1" expected="$2" label="$3"
    if cmp -s "$got" "$expected"; then
        echo "✅ [$label] Files match"
        PASSED=$((PASSED+1))
    else
        echo "❌ [$label] Files differ"
        diff -u "$expected" "$got" | head -n 10
        FAILED=1
    fi
}

check_valgrind_leaks() {
    local log="$1" name="$2"
    local def_line still_line
    def_line=$(grep "definitely lost:" "$log" | head -n 1)
    still_line=$(grep "still reachable:" "$log" | head -n 1)

    echo "🔍 [$name] Leak summary:"
    echo "   $def_line"
    echo "   $still_line"

    if echo "$def_line" | grep -q "definitely lost: 0 bytes" && \
       echo "$still_line" | grep -q "still reachable: 0 bytes"; then
        echo "✅ [$name] No leaks"
        NO_LEAKS=$((NO_LEAKS+1))
    else
        echo "❌ [$name] Leaks detected!"
        LEAKED=$((LEAKED+1))
        FAILED=1
    fi
}

for CONF in "$CONFIG_DIR_W"/*.conf; do
    CONF_NAME=$(basename "$CONF" .conf)
    echo "🧪 Testing working config: $CONF_NAME"
    echo "----------------------------------------"

    LOG_FILE="$LOG_DIR/$CONF_NAME.log"
    VAL_LOG="$VALGRIND_LOG_DIR/$CONF_NAME.valgrind.log"

    if [ "$VALGRIND_ENABLED" = true ]; then
        $VALGRIND_CMD "$WEBSERV" $LOG_FLAGS "$CONF" >"$LOG_FILE" 2>"$VAL_LOG" &
    else
        "$WEBSERV" $LOG_FLAGS "$CONF" >"$LOG_FILE" 2>&1 &
    fi
    PID=$!
    sleep 2

    if ! kill -0 "$PID" 2>/dev/null; then
        echo "❌ Failed to start"
        FAILED=1
        continue
    fi

    echo "✅ Server started"
    echo ""

    # ---- HTTP Tests ----
    STATUS=$(curl -s -o "$RESPONSE_DIR/root.html" -w "%{http_code}" "http://$SERVER_IP:$SERVER_PORT/")
    [ "$STATUS" -eq 200 ] && echo "✅ [GET /] 200 OK" || { echo "❌ [GET /] failed ($STATUS)"; FAILED=1; }

    STATUS=$(curl -s -o "$RESPONSE_DIR/Fame.mp3" -w "%{http_code}" "http://$SERVER_IP:$SERVER_PORT/Fame.mp3")
    [ "$STATUS" -eq 200 ] && echo "✅ [GET /Fame.mp3] OK" || { echo "❌ [GET /Fame.mp3] failed ($STATUS)"; FAILED=1; }

    echo "Test upload" > /tmp/test_post.txt
    STATUS=$(curl -s -o /dev/null -w "%{http_code}" -X POST -d @/tmp/test_post.txt "http://$SERVER_IP:$SERVER_PORT/upload/test")
    [ "$STATUS" -eq 201 ] || [ "$STATUS" -eq 200 ] && echo "✅ [POST /upload/test]" || { echo "❌ [POST /upload/test]"; FAILED=1; }

    STATUS=$(curl -s -o /dev/null -w "%{http_code}" -X DELETE "http://$SERVER_IP:$SERVER_PORT/upload/test")
    [ "$STATUS" -eq 200 ] || [ "$STATUS" -eq 204 ] && echo "✅ [DELETE /upload/test]" || { echo "❌ [DELETE /upload/test]"; FAILED=1; }

    STATUS=$(curl -s -o /dev/null -w "%{http_code}" "http://$SERVER_IP:$SERVER_PORT/asdg")
    [ "$STATUS" -ge 400 ] && echo "✅ [GET /asdg] Error page OK" || { echo "❌ [GET /asdg] failed ($STATUS)"; FAILED=1; }

    STATUS=$(curl -s -D /tmp/headers.txt -o /dev/null -w "%{http_code}" "http://$SERVER_IP:$SERVER_PORT/return/")
    if [ "$STATUS" -eq 301 ]; then
        echo "✅ [GET /return/] redirect OK"
        LOCATION=$(grep -i "Location:" /tmp/headers.txt | awk '{print $2}' | tr -d '\r\n')
        [ "$LOCATION" = "/" ] && echo "✅ Redirect target OK" || echo "❌ Wrong redirect location ($LOCATION)"
    else
        echo "❌ [GET /return/] expected 301 got $STATUS"
        FAILED=1
    fi

    kill "$PID"
    wait "$PID" 2>/dev/null

    if [ "$VALGRIND_ENABLED" = true ]; then
        check_valgrind_leaks "$VAL_LOG" "$CONF_NAME"
    fi

    echo "----------------------------------------"
    echo ""
done

# --- Write result for main script ---
if [ "$FAILED" -eq 0 ]; then
    echo 0 > "$LOG_DIR/working_result.tmp"
else
    echo 1 > "$LOG_DIR/working_result.tmp"
fi
