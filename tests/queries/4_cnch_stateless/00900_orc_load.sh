#!/usr/bin/env bash

CUR_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
# shellcheck source=../shell_config.sh
. "$CUR_DIR"/../shell_config.sh

DATA_FILE=$CUR_DIR/data_orc/test.orc

${CLICKHOUSE_CLIENT} --query="DROP TABLE IF EXISTS orc_load"
${CLICKHOUSE_CLIENT} --query="CREATE TABLE orc_load (int Int32, smallint Int8, bigint Int64, float Float32, double Float64, date Date, y String) ENGINE = CnchMergeTree() order by tuple()"
cat "$DATA_FILE"  | ${CLICKHOUSE_CLIENT} -q "insert into orc_load format ORC"
timeout 3 ${CLICKHOUSE_CLIENT} -q "insert into orc_load format ORC" < $DATA_FILE
${CLICKHOUSE_CLIENT} --query="select * from orc_load"

${CLICKHOUSE_CLIENT} --query="drop table orc_load"
