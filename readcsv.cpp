#include "readcsv.h"
typedef struct infor{
    string timestamp; //время звонка
    string msisdn_origin; //кто совершил звонок
    string msisdn_dest; //кому звонили
    string call_duration; //длительность звонка в минутах
    string sms_number; //количество отправленных смс для абонента msisdn_origin
}bill_infor;

    float call_out ;
    float call_in;
    int sms;
    string call_1, call_2;

void readCSV(string num)
{
    ifstream it("data.csv");
    if(!it.is_open()){
        cout << "ERROR: File open!!" << endl;
    }

    string line;
    struct infor client;

    while(getline(it, line)){
        stringstream ss(line);
        getline(ss, client.timestamp, ',');
        getline(ss, client.msisdn_origin, ',');
        getline(ss, client.msisdn_dest, ',');
        getline(ss, client.call_duration, ',');
        getline(ss, client.sms_number, ',');

        if(client.msisdn_origin == num){
            call_out = atof(client.call_duration.c_str());
            sms = atoi(client.sms_number.c_str());
            call_1 =line;

        }

        if(client.msisdn_dest == num){
            call_in = atof(client.call_duration.c_str());
            call_2 = line;
        }
    }
        it.close();
}
void show_call(string num){
    readCSV(num);
    cout << "Information on your calls: " << endl << "timestamp, msisdn_origin, msisdn_dest, call_duration, sms_number " << endl;
    cout << "Call out: " << call_1 << endl;
    cout << "Call in: " << call_2 << endl;

}
void tariff(string num){
    float sum;
    int call_out_coef = 2; //2руб/минута исходящие звонки,
    int call_in_coef = 1; //0руб/минута входящие первые 50 минут, далее 1руб/минута, 
    int call_in_free = 50;
    int sms_coef =1; //смс - 1руб/шт
    

    readCSV(num);
    cout << "Call in duration: " << call_in <<  endl;
    cout << "Call out duration: " << call_out <<  endl;
    cout << "Number of SMS: " << sms <<  endl;
    
    if(call_in < call_in_free){
    sum =  call_out*call_out_coef + sms*sms_coef;
    }
    else sum = (call_in -call_in_free)*call_in_coef +call_out*call_out_coef +sms*sms_coef;
    cout << "Invoices: " << sum;

}
