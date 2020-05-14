#!/usr/bin/env sh

# REQUIRES: preload, shell, dynamic-shell
# RUN: %{intercept} --verbose --output %t.json -- %{shell} %s --sleep %{sleep} --true %{true}
# RUN: assert_intercepted %t.json count -ge 2
# RUN: assert_intercepted %t.json contains -program %{true}
# TODO: assert_intercepted %t.json contains -program %{sleep}

for i in "$@"
do
  case $i in
    --sleep)
      SLEEP=$2
      shift
      shift
      ;;
    --true)
      TRUE=$2
      shift
      shift
      ;;
    *)
      # unknown option
      ;;
  esac
done

echo "SLEEP     = $SLEEP"
echo "TRUE      = $TRUE"

if [ -z "$SLEEP" ]; then
  echo "SLEEP is not defined";
  exit 1;
fi

if [ -z "$TRUE" ]; then
  echo "TRUE is not defined";
  exit 1;
fi

# do the test
$SLEEP 5 &
kill %1;
wait;

$TRUE