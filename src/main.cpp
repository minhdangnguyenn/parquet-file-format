#include "../include/parser.h"

int main() {
    Parser parser = Parser();
    std::string path = "../weather.parquet";

    arrow::Status status = parser.run(path);
}
