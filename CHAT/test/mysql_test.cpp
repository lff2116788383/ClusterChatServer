#include "db.hpp"
#include <iostream>
using namespace std;
int main()
{
    MySQL mysql;
    if(mysql.connect()){
       cout<<"connect mysql"<<endl;
        if(mysql.update(sql)){
            user.setID(mysql_insert_id(mysql.getconnection()));
            return true;
        }
    }
    return false;
}