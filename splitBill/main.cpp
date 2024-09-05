#include <iostream>
#include "Header.h"

void distribute (AmountType type, double totalAmount, std::vector<Person>& people){
    
    // prepare lambda for return value
    auto amount = [&type](Person x){
        switch (type) {
            case AmountType::Original:
                return x.getPayment().m_original;
                break;
            case AmountType::Tax:
                return x.getPayment().m_tax;
                break;
            case AmountType::Tip:
                return x.getPayment().m_tip;
                break;
            default:
                return x.getPayment().m_total;
                break;
        }
    };
    
    // prepare lambda to set value
    auto setValue = [&type](Person& x, double update) {
        switch (type) {
            case AmountType::Original:
                x.setOriginal(update);
                break;
            case AmountType::Tax:
                x.setTax(update);
                break;
            case AmountType::Tip:
                x.setTip(update);
                break;
            default:
                x.setTotal(update);
                break;
        }
    };
    
    if(totalAmount == 0){
        for (auto& person : people) {
            setValue(person, 0);
        }
        return;
    }

    // calculate the difference between sum of raw value and bill value
    double smallsSum = std::accumulate(people.begin(), people.end(), 0.0, [&amount](double sum, const Person& person) {
        return sum + std::floor(amount(person) * 100) / 100;
    });
    double remains = totalAmount - smallsSum;
    
    // sort from large to small
    std::sort(people.begin(),people.end(),[&amount](Person x, Person y){
        double oneDiff = amount(x) - std::floor(amount(x) * 100) / 100;
        double twoDiff = amount(y) - std::floor(amount(y) * 100) / 100;
        if(oneDiff == twoDiff){
            return amount(x) > amount(y);
        }else{
            return oneDiff > twoDiff;
        }});
    
    // assign the difference
    std::transform(people.begin(), people.end(), people.begin(), [&remains, &amount, &setValue](Person& x) {
        double currentAmount = amount(x);
        double updatedAmount = std::floor(currentAmount * 100) / 100;
        if (remains > 0) {
            updatedAmount += 0.01;
            remains -= 0.01;
        }
        setValue(x, updatedAmount);
        return x;
    });
    
    // sort by id
    std::sort(people.begin(),people.end(),[](Person x, Person y){
        return x.getID() < y.getID();
    });
    
}

int main() {
    std::vector<Person>people;
    Payment bill;
    
    // create people by names
    bool inputDone = false;
    do {
        std::string name;
        std::cout << "Enter a name (or '0' to finish): ";
        std::cin >> name;
        if (name != "0") {
            people.push_back(Person(name));
        }else{
            inputDone = true;
        }
    } while (!inputDone);
    inputDone = false;
    
    // collect item prices
    do {
        double price = 0;
        std::cout << "Enter item price (or '0' to finish): ";
        std::cin >> price;
        
        if (price != 0) {
            // collect people to pay for
            // display list of people
            for (auto person : people) {
                std::cout
                << "< "
                << person.getID() << " : "
                << person.getName() << " > ";
            }
            std::cout << "< " << people.size() + 1 << " : All >" << std::endl;
            std::vector<int>id_vec;
            int id;
            do {
                std::cout << "Enter the person to pay for this item (or '0' to finish): ";
                std::cin >> id;
                if(id == (people.size() + 1)){
                    for (auto person : people) {
                        id_vec.push_back(person.getID());
                    }
                    inputDone = true;
                }else if (id != 0){
                    id_vec.push_back(id);
                }else{
                    inputDone = true;
                }
            } while (!inputDone);
            inputDone = false;
            
            // update their original amount
            for (auto id : id_vec) {
                for (auto& person : people) {
                    if (person.getID() == id) {
                        person += (round(price/id_vec.size() * 100000 + 0.5)/100000);
                    }
                }
            }
        }else{
            inputDone = true;
        }
    } while (!inputDone);
    inputDone = false;
    
    double buffer = 0;
    std::cout << "Enter Subtotal: ";
    std::cin >> buffer;
    bill.m_original = buffer;
    
    std::cout << "Enter HST: ";
    std::cin >> buffer;
    bill.m_tax = buffer;
    
    std::cout << "Enter Tip: ";
    std::cin >> buffer;
    bill.m_tip = buffer;
    
    for (auto& person : people) {
        person.startTax();
    }
    
    for (auto& person : people) {
        person.setTip(round(bill.m_tip/people.size()* 100000 + 0.5)/100000);
    }
    
    distribute(AmountType::Original, bill.m_original, people);
    distribute(AmountType::Tax, bill.m_tax, people);
    distribute(AmountType::Tip, bill.m_tip, people);
    
    for (auto& person : people) {
        person.finalise();
    }
    
    // input paid amount
    for (auto person : people) {
        std::cout
        << "< "
        << person.getID() << " : "
        << person.getName() << " > ";
    }
    std::cout << std::endl;
    int id;
    double paid;
    do {
        std::cout << "Enter the person who paid (or '0' to finish): ";
        std::cin >> id;
        if (id != 0){
            std::cout << "Enter the amount paid: ";
            std::cin >> paid;
            for (auto& person : people) {
                if(person.getID() == id){
                    person.setPaid(paid);
                }
            }
        }else{
            inputDone = true;
        }
    } while (!inputDone);
    inputDone = false;
    
    // prepare lambda for amount receivable
    auto receivable = [](Person x){
        return x.getPaid() - x.getPayment().m_total;
    };
    
    // sort from payable to receivable
    std::sort(people.begin(),people.end(),[&receivable](Person x, Person y){
        return receivable(x) < receivable(y);
    });
    
    size_t receive = people.size() - 1;
    size_t pay = people.size() - 1;
    while (receivable(people[pay]) >= 0) {
        pay--;
    }

    bool done = false;
    do {
        // receivable amount is larger
        if (receivable(people[receive]) + receivable(people[pay]) >= 0) {
            std::cout << people[pay].getName() << " pays "
                        << (-1) * receivable(people[pay]) << " to "
                        << people[receive].getName() << std::endl;
            people[receive].setPaid(receivable(people[pay]));
            people[pay].setPaid(people[pay].getPayment().m_total);
            if(pay != 0){
                pay--;
            }else{
                done = true;
            }
        }
        // payable amount is larger
        else{
            std::cout << people[pay].getName() << " pays "
                        << receivable(people[receive]) << " to "
                        << people[receive].getName() << std::endl;
            people[pay].setPaid(receivable(people[receive]));
            people[receive].setPaid(people[receive].getPayment().m_total);
            if(receivable(people[receive - 1]) != 0){
                receive--;
            }else{
                done = true;
            }
        }
    } while (!done);
    
    return 0;
}
