//Victoria Parra, Assignment 2, Loan Calculator, 2/9/2024

#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

//Gets the input information for the load from the user
void GetInputsFromUser(double &apr, double &P, int &n)
{
    //Ask user to enter APR
    cout << "Enter your APR: " << endl;
    cin >> apr;
    cout << "You entered: " << apr << endl;
    
    //Ask user to enter principal amount
    cout << "Enter the principal amount borrowed (P): " << endl;
    cin >> P;
    
    //Ask user to enter total number of payments
    //monthly payments
    cout << "Enter the total number of payments (n): " << endl;
    cin >> n;
}

//function that calculates and returns monthly interest rate (r)
double Calculate_Monthly_Interest_Rate(double APR)
{
    //formula to calculate monthly interest rate: "r"
    //dividing by 12 places it into a monthly interest rate
    //dividing by 100 puts it in decimal form
    double r = pow( 1 + (APR / 100.0), 1.0/12.0) - 1;
    
    return r;
}

//Calculates the monthly payment for the loan based on the user inputs.
double Calculate_Monthly_Payment(double P, double r, int n) 
{
    //P is the initial principal laon amount
    //r is the monthly interest rate for APR 
    //n is the total number of months that the loan is suppose to be for
    double M = P * r * ((pow(1 + r, n)) / (pow(1 + r, n) - 1));
    
    return M; 
}


//Calculates the monthly interest and principal towards balance.
void Calculate_Interest_and_PrincipalBalance(double P, double r, double m, double &monthly_towards_Interest, double &monthly_towards_Principal)
{
    monthly_towards_Interest = P * r;
    monthly_towards_Principal = m - monthly_towards_Interest;
}

//Keep track of total interest and payments made.
void Keep_Track_Totals(double m, double monthly_towards_Interest, double &total_interest, double &total_payments)
{
    total_interest += monthly_towards_Interest;
    total_payments += m;
}

void print_loan_monthly_total(int paymentCount, double beginning_balance, double monthly_interest, double monthly_principal)
{
    if(paymentCount == 1)
    {
        cout << setw(5)<< "PaymentCount"<< setw(20) << "Beginning Balance" << setw(15) << "Interest" << setw(20) << "Principal" <<setw(20) << "Ending Balance" << endl;
    }
    
    cout << fixed << setprecision(2) << setw(5) <<paymentCount << setw(20) << beginning_balance << setw(20) << monthly_interest << setw(20) << monthly_principal << setw(18) << (beginning_balance -  monthly_principal)<<endl;
}

void print_loan_total_summary(double m, double total_payments, double total_interest)
{
    
    cout<<endl;
    cout<<"Payment Every Month"<<setw(15)<<m<<endl;
    cout<<"Total Payments"<<setw(20)<<total_payments<<endl;
    cout<<"Total Interest"<<setw(20)<<total_interest<<endl;
}

int main()
{
    
    //Loan fixed rate and monthy calculation
    double r = 0.00;
    double m = 0.00;
    
    //User inputs for loan details
    double apr = 0.00;
    double P = 0.00;
    double beginning_balance = 0.00;
    int n = 0;
    
    //monnthly interest and principal calculation
    double monthly_towards_Interest = 0.00;
    double monthly_towards_Principal = 0.00;
    
    //Accumulated totals for interest and payments
    double total_interest = 0.00;
    double total_payments = 0.00;
    
    GetInputsFromUser(apr, P,  n);
    
    //Calculated fixed rate and monthly payment
    r = Calculate_Monthly_Interest_Rate(apr); 
    m = Calculate_Monthly_Payment(P, r, n);
    
    
    beginning_balance = P;
    
    
    //Call this in a for loop
    for(int i=0; i < n; i++)
    {
        Calculate_Interest_and_PrincipalBalance(beginning_balance, r, m,  monthly_towards_Interest, monthly_towards_Principal);
    
        Keep_Track_Totals(m, monthly_towards_Interest, total_interest, total_payments);
        
        print_loan_monthly_total(i+1, beginning_balance, monthly_towards_Interest, monthly_towards_Principal);
    
        //Update Beginning Balance
        beginning_balance -= monthly_towards_Principal;
        
    }

    
    print_loan_total_summary(m, total_payments, total_interest);
    
    
}

