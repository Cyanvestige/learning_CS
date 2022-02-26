/* Exercise 7.26: Define Sales_data::avg_price as an inline function.*/
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <iostream>
#include <string>
struct Sales_data;
std::istream &read(std::istream&, Sales_data&);

struct Sales_data{
    // explicitly initializes the members to the values we have provided as in-class initializers
    Sales_data(): bookNo(""), units_sold(0), revenue(0.0){ }
    Sales_data(const std::string &s): bookNo(s) { }
    Sales_data(const std::string &s, unsigned n, double p): 
                bookNo(s), units_sold(n), revenue(p*n) { }
    Sales_data(std::istream &is) { 
        read(is, *this); 
    }
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// added "inline"
inline
double Sales_data::avg_price() const{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

std::ostream &print(std::ostream&, const Sales_data&);

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
std::istream &read(std::istream& is, Sales_data& item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
#endif