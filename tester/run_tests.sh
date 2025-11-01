#!/bin/bash
# =====================================
# Webserv Test Runner — main orchestrator
# =====================================

# --- Default settings ---
USE_VALGRIND=false
RUN_SIEGE=false
SIEGE_DURATION=10
DELETE_LOGS=false
INTERACTIVE=true
IS_DOCKER=false

# --- Parse CLI flags ---
while getopts "fdD" opt; do
  case $opt in
    f)
      echo "⚙️ Full mode enabled: Valgrind + Siege (30s)"
      USE_VALGRIND=true
      RUN_SIEGE=true
      SIEGE_DURATION=30
      INTERACTIVE=false
      ;;
    d)
      echo "🚀 Default mode: no Valgrind, no Siege"
      USE_VALGRIND=false
      RUN_SIEGE=false
      INTERACTIVE=false
      ;;
    D)
      DELETE_LOGS=true
      ;;
    *)
      echo "Usage: $0 [-f] [-d] [-D]"
      echo "  -f : Run everything with Valgrind and Siege (30s)"
      echo "  -d : Run tests only (no Valgrind, no Siege)"
      echo "  -D : Delete all logs and exit"
      exit 1
      ;;
  esac
done

# --- Paths (needed early for -D mode) ---
LOG_DIR=../tester/logs

# --- Delete mode ---
if [ "$DELETE_LOGS" = true ]; then
  echo "🧹 Deleting all logs in $LOG_DIR ..."
  rm -rf "$LOG_DIR"/*
  echo "✅ Logs cleared."
  exit 0
fi

# --- Input handling ---
if [ "$INTERACTIVE" = true ]; then
    echo "🌐 Enter IP address to bind to (default: 127.0.0.1):"
    read -r SERVER_IP
    SERVER_IP=${SERVER_IP:-127.0.0.1}

    echo "🔌 Enter port to use (default: 8080):"
    read -r SERVER_PORT
    SERVER_PORT=${SERVER_PORT:-8080}

    echo "🧩 Enter webserv log flags (default: -ide):"
    read -r LOG_FLAGS
    LOG_FLAGS=${LOG_FLAGS// /}
    if [ -z "$LOG_FLAGS" ]; then
        LOG_FLAGS="-ide"
    elif [[ "$LOG_FLAGS" != -* ]]; then
        LOG_FLAGS="-$LOG_FLAGS"
    fi

    echo ""
    echo "🐋 Are you running inside Docker? (y/N)"
    read -r docker_ans
    if [[ "$docker_ans" =~ ^[Yy]$ ]]; then
        IS_DOCKER=true
        echo "📦 Docker mode enabled — using /configs_docker"
    else
        IS_DOCKER=false
        echo "💻 Host mode — using /configs"
    fi

    echo ""
    echo "🔍 Would you like to run tests with Valgrind? (y/N)"
    read -r val_ans
    if [[ "$val_ans" =~ ^[Yy]$ ]]; then
        USE_VALGRIND=true
    fi

    echo ""
    echo "⚡ Would you like to run a Siege benchmark test? (y/N)"
    echo "⚠️ Siege might not work depending on OS - check: net.inet.ip.portrange.hifirst & net.inet.tcp.msl"
    read -r siege_ans
    if [[ "$siege_ans" =~ ^[Yy]$ ]]; then
        RUN_SIEGE=true
        echo "⏱️ Enter Siege test duration in seconds (default: 10):"
        read -r siege_time
        SIEGE_DURATION=${siege_time:-10}
    fi
else
    SERVER_IP="127.0.0.1"
    SERVER_PORT="8080"
    LOG_FLAGS="-ide"
    IS_DOCKER=false
    echo "🌐 Using defaults: IP=$SERVER_IP, PORT=$SERVER_PORT, LOG_FLAGS=$LOG_FLAGS, Docker=$IS_DOCKER"
fi

# --- Paths ---
if [ "$IS_DOCKER" = true ]; then
    CONFIG_BASE="../tester/configs_docker"
else
    CONFIG_BASE="../tester/configs"
fi

WEBSERV=./../src/webserv
CONFIG_DIR_W="$CONFIG_BASE/02_working"
CONFIG_DIR_F="$CONFIG_BASE/00_faulty"
CONFIG_DIR_S="$CONFIG_BASE/01_single_method"
EXPECTED_DIR=../tester/expected
RESPONSE_DIR="$LOG_DIR/responses"
VALGRIND_LOG_DIR="$LOG_DIR/valgrind"
SIEGE_LOG_DIR="$LOG_DIR/siege"
mkdir -p "$LOG_DIR" "$RESPONSE_DIR" "$VALGRIND_LOG_DIR" "$SIEGE_LOG_DIR"

# --- Check Valgrind availability ---
if [ "$USE_VALGRIND" = true ]; then
    if ! command -v valgrind &>/dev/null; then
        echo "⚠️  Valgrind is not installed! Disabling Valgrind mode..."
        USE_VALGRIND=false
    fi
fi

# --- Check Siege availability ---
if [ "$RUN_SIEGE" = true ]; then
    if ! command -v siege &>/dev/null; then
        echo "⚠️  Siege is not installed! Disabling Siege test..."
        RUN_SIEGE=false
    fi
fi

# --- Valgrind setup ---
if [ "$USE_VALGRIND" = true ]; then
    VALGRIND_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=99"
    VALGRIND_ENABLED=true
    echo "🔍 Valgrind mode enabled."
else
    VALGRIND_CMD=""
    VALGRIND_ENABLED=false
    echo "🚀 Running without Valgrind."
fi

# --- Siege info ---
if [ "$RUN_SIEGE" = true ]; then
    echo "⏱️ Siege benchmark will run for $SIEGE_DURATION seconds after tests."
else
    echo "⏩ Siege test skipped."
fi

# --- Summary banner ---
echo ""
echo "========================================"
echo "🧩 TEST SESSION SUMMARY"
echo "----------------------------------------"
echo "Mode:          $( [ "$INTERACTIVE" = true ] && echo "INTERACTIVE" || ( [ "$USE_VALGRIND" = true ] && echo "FULL" || echo "DEFAULT" ) )"
echo "Docker mode:   $IS_DOCKER"
echo "Valgrind:      $USE_VALGRIND"
echo "Siege:         $RUN_SIEGE"
echo "Siege time:    $SIEGE_DURATION sec"
echo "IP:            $SERVER_IP"
echo "Port:          $SERVER_PORT"
echo "Log flags:     $LOG_FLAGS"
echo "========================================"
echo ""

# --- Export for sub-scripts ---
export SERVER_IP SERVER_PORT LOG_FLAGS VALGRIND_CMD VALGRIND_ENABLED
export WEBSERV CONFIG_DIR_W CONFIG_DIR_F CONFIG_DIR_S EXPECTED_DIR LOG_DIR RESPONSE_DIR VALGRIND_LOG_DIR SIEGE_LOG_DIR SIEGE_DURATION RUN_SIEGE IS_DOCKER

# --- Temporary result files ---
WORKING_RESULT_FILE="$LOG_DIR/working_result.tmp"
FAULTY_RESULT_FILE="$LOG_DIR/faulty_result.tmp"
SINGLE_RESULT_FILE="$LOG_DIR/single_result.tmp"
SIEGE_RESULT_FILE="$SIEGE_LOG_DIR/siege_result.tmp"
> "$WORKING_RESULT_FILE"
> "$FAULTY_RESULT_FILE"
> "$SINGLE_RESULT_FILE"
> "$SIEGE_RESULT_FILE"

# --- 1️⃣ Run faulty configs ---
bash ../tester/tests/test_faulty.sh > >(tee "$LOG_DIR/test_faulty.log")
FAULTY_EXIT=$(cat "$FAULTY_RESULT_FILE")

# --- 3️⃣ Run working configs ---
bash ../tester/tests/test_working.sh > >(tee "$LOG_DIR/test_working.log")
WORKING_EXIT=$(cat "$WORKING_RESULT_FILE")

# --- 4️⃣ Optional Siege benchmark ---
SIEGE_EXIT=0
if [ "$RUN_SIEGE" = true ]; then
    echo ""
    echo "⚙️ Running Siege performance test..."
    bash ../tester/tests/test_siege.sh > >(tee "$SIEGE_LOG_DIR/siege_test.log")
    if [ -f "$SIEGE_RESULT_FILE" ]; then
        SIEGE_EXIT=$(cat "$SIEGE_RESULT_FILE")
    fi
fi

# --- Final summary ---
echo ""
echo "========================================"
echo "🧩 FINAL TEST SUMMARY"
echo "========================================"

if [ "$FAULTY_EXIT" -eq 0 ]; then
    echo "✅ Faulty configs passed"
else
    echo "❌ Faulty configs failed"
fi

if [ "$WORKING_EXIT" -eq 0 ]; then
    echo "✅ Working configs passed"
else
    echo "❌ Working configs failed"
fi

if [ "$RUN_SIEGE" = true ]; then
    if [ "$SIEGE_EXIT" -eq 0 ]; then
        echo "✅ Siege performance test passed"
    else
        echo "❌ Siege performance test failed"
        echo "⚠️ Siege might not work depending on OS - check: net.inet.ip.portrange.hifirst & net.inet.tcp.msl"
    fi
fi

echo "----------------------------------------"
echo "🗂 Logs stored in: $LOG_DIR"
echo "🧠 Valgrind logs: $VALGRIND_LOG_DIR"
if [ "$RUN_SIEGE" = true ]; then
    echo "💥 Siege logs:    $SIEGE_LOG_DIR"
fi
echo "----------------------------------------"

EXIT_CODE=0
if [ "$FAULTY_EXIT" -ne 0 ] || [ "$WORKING_EXIT" -ne 0 ] || [ "$SIEGE_EXIT" -ne 0 ]; then
    EXIT_CODE=1
fi

if [ "$EXIT_CODE" -eq 0 ]; then
    echo "✅ All tests passed successfully!"
else
    echo "❌ Some tests failed — check logs for details."
fi

echo "========================================"
exit $EXIT_CODE
