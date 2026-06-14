#include "../include/parser.h"
#include <iostream>

int main() {
    Parser parser = Parser();
    std::string path = "../../weather.parquet";

    arrow::Status status = parser.run(path);
    if (!status.ok()) {
        std::cerr << "Error: " << status.ToString() << std::endl;
        return 1;
    }
}
