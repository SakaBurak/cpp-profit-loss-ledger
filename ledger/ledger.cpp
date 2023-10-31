#include <iostream>
#include <string>

using namespace std;

double calculateVAT(double grossIncome, string location);
double calculateProfit(double grossIncome, double expenses, string location);
double calculateCorporateTax(double profit);
double calculateNetProfit(double grossIncome, double expenses, string location);
double calculateDividend(double netProfit, int numOfShareholders);
bool getCompanyData(string& companyName, string& location, double& grossIncome, double& expenses, int& numOfShareholders);
void outputCompanyResults(string companyName, double netProfit, double vat, double corporateTax, double capitalIncrease, int numOfShareholders);

int main() {
    cout<<"This accounting program calculates the state taxes and dividends for the company shareholders." <<endl;

    string companyName1, location1, companyName2, location2;
    double grossIncome1, expenses1, grossIncome2, expenses2;
    int numOfShareholders1, numOfShareholders2;

    if (!getCompanyData(companyName1, location1, grossIncome1, expenses1, numOfShareholders1)) {
        //cout << "Invalid input for the first company. Program crashed." << endl;
        return 0; //return 1;
    }

    if (!getCompanyData(companyName2, location2, grossIncome2, expenses2, numOfShareholders2)) {
        //cout << "Invalid input for the second company. Program crashed." << endl;
        return 0; //return 1;
    }

    double vat1 = calculateVAT(grossIncome1, location1);
    double profit1 = calculateProfit(grossIncome1, expenses1, location1);
    double corporateTax1 = calculateCorporateTax(profit1);
    double netProfit1 = calculateNetProfit(grossIncome1, expenses1, location1);
    double dividend1 = calculateDividend(netProfit1, numOfShareholders1);
    double capitalIncrease1 = 0.5 * netProfit1;

    double vat2 = calculateVAT(grossIncome2, location2);
    double profit2 = calculateProfit(grossIncome2, expenses2, location2);
    double corporateTax2 = calculateCorporateTax(profit2);
    double netProfit2 = calculateNetProfit(grossIncome2, expenses2, location2);
    double dividend2 = calculateDividend(netProfit2, numOfShareholders2);
    double capitalIncrease2 = 0.5 * netProfit2;

    cout<<"------------ "<< companyName1 <<" Financial Report ------------"<<endl;
    outputCompanyResults(companyName1, netProfit1, vat1, corporateTax1, capitalIncrease1, numOfShareholders1);
    cout<<endl;
	
    cout<<"------------ " << companyName2 <<" Financial Report ------------"<<endl;
    outputCompanyResults(companyName2, netProfit2, vat2, corporateTax2, capitalIncrease2, numOfShareholders2);
    cout<<endl;

    if (netProfit1 > netProfit2) {
        cout<<companyName1<<" has a superior financial performance in terms of net profit compared to "<<companyName2<<"."<<endl;
    } else if (netProfit2 > netProfit1) {
        cout<<companyName2<<" has a superior financial performance in terms of net profit compared to "<<companyName1<<"."<<endl;
    } else {
        cout<<"Both companies have equal performance in terms of net profit."<<endl;
    }

    return 0;
}

double calculateVAT(double grossIncome, string location) {
    if (location == "local") {
        return 0.15 * grossIncome;
    } else if (location == "foreign") {
        return 0.18 * grossIncome;
    } else {
        return 0; // Invalid location
    }
}

double calculateProfit(double grossIncome, double expenses, string location) {
    double vat = calculateVAT(grossIncome, location);
    return grossIncome - expenses - vat;
}

double calculateCorporateTax(double profit) {
    if (profit <= 10000) {
        return 0.10 * profit;
    } else if (profit <= 25000) {
        return 0.15 * profit;
    } else if (profit <= 50000) {
        return 0.20 * profit;
    } else {
        return 0.25 * profit;
    }
}

double calculateNetProfit(double grossIncome, double expenses, string location) {
    double profit = calculateProfit(grossIncome, expenses, location);
    double corporateTax = calculateCorporateTax(profit);
    return profit - corporateTax;
}

double calculateDividend(double netProfit, int numOfShareholders) {
    double dividend = 0.5 * netProfit;
    double shareholderDividendTax = 0.15*dividend;
    return dividend / numOfShareholders;
}

bool getCompanyData(string& companyName, string& location, double& grossIncome, double& expenses, int& numOfShareholders) {
    cout<<"Please enter the name of the company: ";
    cin>>companyName;
    cout<<"Is the company local or foreign? ";
    cin>>location;
    if(location != "local" && location != "foreign") {
        cout<<"Invalid location input."<<endl;
        return false;
    }
    cout<<"Please enter the gross income of " << companyName << ": ";
    cin>>grossIncome;
    if(grossIncome <= 0) {
        cout<<"Invalid input for gross income."<<endl;
        return false;
    }
    cout<<"Please enter expenses of "<<companyName<<": ";
    cin>>expenses;
    if (expenses < 0) {
        cout << "Invalid input for expenses." <<endl;
        return false;
    }
    cout<<"Please enter the number of shareholders: ";
    cin>>numOfShareholders;
    if(numOfShareholders < 1) {
        cout<<"Invalid input for the number of shareholders."<<endl;
        return false;
    }
    cout<<endl;
    return true;
}

void outputCompanyResults(string companyName, double netProfit, double vat, double corporateTax, double capitalIncrease, int numOfShareholders) {
	//double shareholderDividendTax = 0.15 * (0.5 * netProfit);
	if(netProfit==0){
		cout<<"Net Profit: "<<netProfit<<" TL. (Break Even)"<<endl;
        cout<<"VAT: " << vat<< " TL."<<endl;
        cout<<"Corporate Tax: "<<corporateTax<<" TL."<<endl;
        cout<<"Capital Increase:"<< capitalIncrease << " TL."<<endl;
        cout<<numOfShareholders<<" shareholders will have a share of: 0 TL."<<endl;
	}
	else if(netProfit<0){
		cout<<"Net Loss: "<<netProfit<<" TL."<<endl;
        cout<<"VAT: "<<vat<<" TL."<<endl;
        cout<<"Corporate Tax: "<<corporateTax<<" TL."<<endl;
        cout<<"Capital Increase: "<<capitalIncrease<<" TL."<<endl;
        cout<<numOfShareholders<<" shareholders will have a share of: 0 TL."<<endl;
	}
	else{
		cout<<"Net Profit: "<<netProfit<<" TL."<<endl;
        cout<<"VAT: "<<vat<<" TL."<<endl;
        cout<<"Corporate Tax: "<<corporateTax<<" TL."<<endl;
        cout<<"Capital Increase: "<<capitalIncrease<<" TL."<<endl;
        cout<<numOfShareholders<<" shareholders will have a share of: "<<((capitalIncrease - (0.15 * (0.5 * netProfit))) / numOfShareholders)<<" TL."<<endl;
	}
    /*cout<<"Net Profit: "<<netProfit<<" TL."<<endl;
    cout<<"VAT: "<< vat <<" TL."<<endl;
    cout<<"Corporate Tax: "<<corporateTax<<" TL."<<endl;
    cout<<"Capital Increase: "<<capitalIncrease<<" TL."<<endl;
    cout<<numOfShareholders<<" shareholders will have a share of: "<<((capitalIncrease - shareholderDividendTax) / numOfShareholders)<<" TL."<<endl;*/
}

