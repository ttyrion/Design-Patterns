// builder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

class BankAccount {
public:
    class Builder {
    public:
        Builder(long number) {
            this->account_number = number;
        }

        Builder& WithOwner(const std::wstring& owner) {
            this->owner = owner;
            return *this;
        }

        Builder& AtBranch(const std::wstring& branch) {
            this->branch = branch;
            return *this;
        }

        Builder& OpeningBalance(const double balance) {
            this->balance = balance;
            return *this;
        }

        Builder& AtMonthlyRate(const double rate) {
            this->interest_rate = rate;
            return *this;
        }
        
        BankAccount Create() {
            BankAccount account;
            account.account_number = this->account_number;
            account.owner = this->owner;
            account.branch = this->branch;
            account.balance = this->balance;
            account.interest_rate = this->interest_rate;

            return account;
        }

    private:
        long account_number;
        std::wstring owner;
        std::wstring branch;  //optional
        double balance;
        double interest_rate;
    };

private:
    BankAccount() {};

    long account_number;
    std::wstring owner;
    std::wstring branch;
    double balance;
    double interest_rate;
};

int main()
{
    //Now it's impossible to swap the 1000.00 and 2.5 which have the same type but very different meaning
    //when calling an traditional constructor
    
    //create a back account
    BankAccount account_X = BankAccount::Builder(1234L).WithOwner(L"Mary")
                          .AtBranch(L"Shanghai").OpeningBalance(1000.00).AtMonthlyRate(2.5).Create();

    //ignore the optional branch member
    BankAccount account_Y = BankAccount::Builder(5358L).WithOwner(L"Jame").OpeningBalance(1000.00).AtMonthlyRate(2.5).Create();

    return 0;
}

