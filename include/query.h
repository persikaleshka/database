#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <map>
#include <iostream>
#include <memory>

class Query {
public:
    virtual ~Query() = default;
    virtual std::string get_type() const = 0;
    virtual void print() const = 0;
    virtual void set_table(const std::string& table) = 0;
    virtual void set_where(const std::string& condition) = 0;
};

struct JoinClause {
    std::string table1;
    std::string table2;
    std::string condition;

    JoinClause() = default;
    JoinClause(const std::string& t1, const std::string& t2, const std::string& cond)
        : table1(t1), table2(t2), condition(cond) {}
};

class SelectQuery : public Query {
public:
    std::vector<std::string> columns;
    std::string table;
    std::vector<JoinClause> joins;
    std::string where_conditions;

    SelectQuery() = default;

    std::string get_type() const override { return "SELECT"; }

    void set_columns(const std::vector<std::string>& cols) {
        columns = cols;
    }

    void set_join(const std::string& table1, const std::string& table2, const std::string& condition) {
        joins.emplace_back(table1, table2, condition);
    }

    void set_where(const std::string& condition) override {
        where_conditions = condition;
    }

    void set_table(const std::string& tbl) override {
        table = tbl;
    }

    void print() const override {
        std::cout << "Query Type: SELECT\n";

        std::cout << "Columns: ";
        for (const auto& col : columns) {
            std::cout << col << " ";
        }
        std::cout << "\nTable: " << table << "\n";
        if (!joins.empty()) {
            std::cout << "Joins:\n";
            for (const auto& join : joins) {
                std::cout << "  JOIN " << join.table1 << " WITH " << join.table2
                          << " ON " << join.condition << "\n";
            }
        }
        if (!where_conditions.empty()) {
            std::cout << "Where Conditions: " << where_conditions << "\n";
        }
    }
};

class InsertQuery : public Query {
public:
    std::string table;
    std::map<std::string, std::string> values;

    InsertQuery() = default;

    std::string get_type() const override { return "INSERT"; }

    void set_table(const std::string& tbl) override {
        table = tbl;
    }

    void set_values(const std::map<std::string, std::string>& vals) {
        values = vals;
    }

    void set_where(const std::string&) override {}

    void print() const override {
        std::cout << "Query Type: INSERT\n";
        std::cout << "Table: " << table << "\n";
        std::cout << "Values:\n";
        for (const auto& [key, value] : values) {
            std::cout << "  " << key << " = " << value << "\n";
        }
    }
};

class UpdateQuery : public Query {
public:
    std::string table;
    std::map<std::string, std::string> assignments;
    std::string where_conditions;

    UpdateQuery() = default;

    std::string get_type() const override { return "UPDATE"; }

    void set_table(const std::string& tbl) override {
        table = tbl;
    }

    void set_assignments(const std::map<std::string, std::string>& assigns) {
        assignments = assigns;
    }

    void set_where(const std::string& condition) override {
        where_conditions = condition;
    }

    void print() const override {
        std::cout << "Query Type: UPDATE\n";
        std::cout << "Table: " << table << "\n";
        std::cout << "Assignments:\n";
        for (const auto& [key, value] : assignments) {
            std::cout << "  " << key << " = " << value << "\n";
        }
        if (!where_conditions.empty()) {
            std::cout << "Where Conditions: " << where_conditions << "\n";
        }
    }
};

class DeleteQuery : public Query {
public:
    std::string table;
    std::string where_conditions;

    DeleteQuery() = default;

    std::string get_type() const override { return "DELETE"; }

    void set_table(const std::string& tbl) override {
        table = tbl;
    }

    void set_where(const std::string& condition) override {
        where_conditions = condition;
    }

    void print() const override {
        std::cout << "Query Type: DELETE\n";
        std::cout << "Table: " << table << "\n";
        if (!where_conditions.empty()) {
            std::cout << "Where Conditions: " << where_conditions << "\n";
        }
    }
};

#endif // QUERY_H
