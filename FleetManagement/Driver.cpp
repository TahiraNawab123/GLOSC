#include <iostream>
using namespace std;
#include <string>
#include "Driver.h"
 Driver::Driver() {
      driverId= 0;
      driverName= "Unknown";
      isAvailable= true;
      assignedVehicleId= -1;
    }

Driver::Driver(int id, string name){
      driverId= id;
      driverName= name;
      isAvailable= true;
      assignedVehicleId= -1;
}
//assign vehicle
void Driver::assignVehicle(int vehicleId){
   if(isAvailable==false){
    cout<<"Driver already assigned! \n";
   }
   assignedVehicleId=vehicleId;
   isAvailable=false;
}

void Driver::FreeDriver(){//free the driver after the trip

    if(isAvailable == true){
        cout<<"Driver is already free!\n";
        return;
    }
       assignedVehicleId = -1;
       isAvailable = true;
}

void Driver::displayDriverInfo(){//display
cout<<"\n=======Driver Details=======\n";
cout<<"Driver ID: "<<driverId<<endl;
cout<<"Driver Name: "<<driverName<<endl;
cout<<"Is Drive Avaiable: "<<(isAvailable?"Yes": "No")<<endl;
cout<<"Assigned Vehicle ID: ";
if(assignedVehicleId==-1){
    cout<<"None";
}
else{
    cout<<assignedVehicleId;
}
cout<<endl;
}

Driver* findDriverById(Driver drivers[], int driverCount,int id){
  
for(int i=0; i< driverCount;i++){
if(drivers[i].driverId==id){
    return &drivers[i];//return the address of matching element
    }
  }
    return nullptr;

   }

