#include "../include/parser.h"
#include <arrow/chunked_array.h>
#include <arrow/record_batch.h>
#include <arrow/result.h>
#include <arrow/scalar.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <iostream>
#include <memory>

Parser::Parser() {}
Parser::~Parser() {}

arrow::Status Parser::run(std::string path) {
    arrow::MemoryPool *pool = arrow::default_memory_pool();

    std::shared_ptr<arrow::io::RandomAccessFile> input;
    ARROW_ASSIGN_OR_RAISE(input, arrow::io::ReadableFile::Open(path));
    std::unique_ptr<parquet::arrow::FileReader> reader;

    ARROW_ASSIGN_OR_RAISE(reader, parquet::arrow::OpenFile(input, pool));
    std::shared_ptr<arrow::Table> table;

    ARROW_ASSIGN_OR_RAISE(table, reader->ReadTable());
    std::cout << " # Rows: " << table->num_rows() << std::endl;

    return this->printRows(table);
}

arrow::Status Parser::printRows(std::shared_ptr<arrow::Table> table) {
    auto reader = arrow::TableBatchReader(*table);
    std::shared_ptr<arrow::RecordBatch> batch;

    while (true) {
        ARROW_ASSIGN_OR_RAISE(batch, reader.Next());
        if (!batch) {
            break;
        }

        auto schema = table->schema();

        // print column names
        for (int i = 0; i < schema->num_fields(); i++) {
            std::cout << schema->field(i)->name() << "\t";
        }
        std::cout << "\n";

        // print separator
        for (int i = 0; i < schema->num_fields(); i++) {
            std::cout << "--------\t";
        }
        std::cout << "\n";

        // print rows
        for (int64_t row = 0; row < table->num_rows(); row++) {
            for (int col = 0; col < table->num_columns(); col++) {
                auto scalar = table->column(col)->GetScalar(row).ValueOrDie();

                std::cout << scalar->ToString() << "\t";
            }
            std::cout << "\n";
        }
    }

    return arrow::Status::OK();
}
