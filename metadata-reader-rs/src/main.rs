mod metadata;
use metadata::Metadata;
use parquet::schema::{parser, printer};

fn main() {
    let metadata = Metadata::new();
    let schema = metadata.create("a", "b");

    let mut buf = Vec::new();
    printer::print_schema(&mut buf, &schema);

    let string_schema = String::from_utf8(buf).unwrap();
    println!("{}", string_schema); // convert and print the schema

    let parsed_schema = parser::parse_message_type(&string_schema).unwrap(); // parse string back to schema type
    assert_eq!(schema, parsed_schema);
}
