#pragma once
#include <arrow/filesystem/filesystem.h>
#include <arrow/filesystem/localfs.h>
#include <arrow/io/api.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <memory>
#include <parquet/arrow/reader.h>

class Parser {
  public:
    ~Parser();
    Parser();

    arrow::Status run(std::string path);
    arrow::Status printRows(std::shared_ptr<arrow::Table> table);
};
