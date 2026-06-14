use parquet::{
    basic::{ConvertedType, Repetition, Type as PhysicalType},
    schema::{parser, printer, types::Type},
};
use std::sync::Arc;

pub struct Metadata {}

impl Metadata {
    pub fn new() -> Metadata {
        Metadata {}
    }

    pub fn create(&self, field_a: &str, field_b: &str) -> Type {
        // build field a
        let field_a = Type::primitive_type_builder(field_a, PhysicalType::BYTE_ARRAY)
            .with_converted_type(ConvertedType::UTF8)
            .with_repetition(Repetition::OPTIONAL)
            .build()
            .unwrap();

        // build field b
        let field_b = Type::primitive_type_builder(field_b, PhysicalType::INT32)
            .with_repetition(Repetition::REQUIRED)
            .build()
            .unwrap();

        // create a new schema and group both fields into it
        let schema = Type::group_type_builder("schema")
            .with_fields(vec![Arc::new(field_a), Arc::new(field_b)])
            .build()
            .unwrap();

        return schema;
    }
}
