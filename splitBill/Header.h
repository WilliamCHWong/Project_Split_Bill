#ifndef Header_h
#define Header_h
#define TAXRATE 0.13

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

enum class AmountType {
    Original,
    Tax,
    Tip,
    Total
};

class Payment {
public:
    double m_original;
    double m_tax;
    double m_tip;
    double m_total;
    
    // empty constructor
    Payment(){
        m_original = 0;
        m_tax = 0;
        m_tip = 0;
        m_total = 0;
    }
    
};

class Person {
    static int m_nextID;
    int m_ID;
    std::string m_name;
    Payment m_payment;
    double m_paid;
public:
    Person(const std::string& name)
        : m_name(name), m_payment() {
        m_ID = m_nextID++;
        m_paid = 0;
    }

    int getID ()const{
        return m_ID;
    }

    std::string getName() const {
        return m_name;
    }

    void setName(const std::string& name) {
        m_name = name;
    }

    double getPaid() const {
        return m_paid;
    }
    
    void setPaid (double update){
        m_paid += update;
    }
    
    Payment getPayment() const {
        return m_payment;
    }
    
    void setOriginal (double original){
        m_payment.m_original = original;
    }
    
    void setTax (double tax){
        m_payment.m_tax = tax;
    }
    
    void setTip (double tip){
        m_payment.m_tip = tip;
    }
    
    void setTotal (double total){
        m_payment.m_total = total;
    }
    
    Person& operator += (double amount){
        m_payment.m_original += amount;
        return *this;
    }
    
    void startTax(){
        m_payment.m_tax = (m_payment.m_original) * TAXRATE;
    }
    
    void finalise(){
        m_payment.m_total = m_payment.m_original + m_payment.m_tax + m_payment.m_tip;
    }
};

int Person::m_nextID = 1;

#endif
