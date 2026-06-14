use parquet::{
    basic::{ConvertedType, Repetition, Type as PhysicalType},
    schema::{parser, printer, types::Type},
};
use std::sync::Arc;

fn main() {
    // build field a
    let field_a = Type::primitive_type_builder("a", PhysicalType::BYTE_ARRAY)
        .with_converted_type(ConvertedType::UTF8)
        .with_repetition(Repetition::OPTIONAL)
        .build()
        .unwrap();

    // build field b
    let field_b = Type::primitive_type_builder("b", PhysicalType::INT32)
        .with_repetition(Repetition::REQUIRED)
        .build()
        .unwrap();

    // create a new schema and group both fields into it
    let schema = Type::group_type_builder("schema")
        .with_fields(vec![Arc::new(field_a), Arc::new(field_b)])
        .build()
        .unwrap();

    let mut buf = Vec::new();
    printer::print_schema(&mut buf, &schema);

    let string_schema = String::from_utf8(buf).unwrap();
    println!("{}", string_schema); // convert and print the schema

    let parsed_schema = parser::parse_message_type(&string_schema).unwrap(); // parse string back to schema type
    assert_eq!(schema, parsed_schema);
}
