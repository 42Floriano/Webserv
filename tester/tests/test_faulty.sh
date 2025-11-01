#!/bin/bash
# =====================================
# Webserv Tests for Faulty Configs
# =====================================

FAILED=0
PASSED=0

for CONF in "$CONFIG_DIR_F"/*.conf; do
    CONF_NAME=$(basename "$CONF" .conf)
    echo "🧪 Testing faulty config: $CONF_NAME"
    echo "----------------------------------------"

    LOG_FILE="$LOG_DIR/$CONF_NAME.log"
    VAL_LOG="$VALGRIND_LOG_DIR/$CONF_NAME.valgrind.log"

    if [ "$VALGRIND_ENABLED" = true ]; then
        $VALGRIND_CMD "$WEBSERV" $LOG_FLAGS "$CONF" >"$LOG_FILE" 2>"$VAL_LOG" &
    else
        "$WEBSERV" $LOG_FLAGS "$CONF" >"$LOG_FILE" 2>&1 &
    fi
    PID=$!
    sleep 1

    if kill -0 "$PID" 2>/dev/null; then
        echo "❌ Faulty config started unexpectedly"
        kill "$PID"
        wait "$PID" 2>/dev/null
        FAILED=1
    else
        echo "✅ Faulty config failed as expected"
        PASSED=$((PASSED+1))
    fi

    echo "----------------------------------------"
    echo ""
done

if [ "$FAILED" -eq 0 ]; then
    echo 0 > "$LOG_DIR/faulty_result.tmp"
else
    echo 1 > "$LOG_DIR/faulty_result.tmp"
fi
