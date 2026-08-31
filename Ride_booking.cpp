#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Location{
    int lat;
    int lang;
    public:
    Location(){};
    Location(int i,int j){
        lat=i;
        lang=j;
    }
    int get_lat(){
        return lat;
    }
    int get_lng(){
        return lang;
    }
    void set_location(int p,int l){
        lat=p;
        lang=l;
    }
    
};




class Request{
    string name;
    string to;
    string from;
    Location loc;

    public:
    Request(){};
    Request(string n,string t,string f,Location l){
        name=n;
        to=t;
        loc=l;
        from=f;
    }
    string get_name(){
        return name;
    }
    string get_to(){
        return to;
    }
    string get_from(){
        return from;
    }
    Location get_location(){
        return loc;
    }
    

};




class status{
    public:
    virtual bool execute_next(Request,int)=0;

};
class completed: public status{
    public:
    bool execute_next(Request r,int amt) override{
        cout<<"payment completed"<<endl;
        cout<<"details stored in the database"<<endl;
        return true;
    }
};
class payment_processing: public status{
    public:
    bool execute_next(Request r,int amt) override{
        status* next=new completed();
        cout<<"processing payment"<<endl;
        bool result= next->execute_next(r,amt);
        delete next;
        return result;
    }
};
class completing: public status{
    
    public:
    bool execute_next(Request r,int amt) override{
        status* next = new payment_processing();
        bool result=next->execute_next(r,amt);
        delete next;
        return result;

    }
};





class Ride{
    Request r;
    status* s=nullptr;
    int distance;
    int amount;
    Request req;
    public:

    void start_ride(Request req){
        r=req;
        s=new completing();
        cout<<"Displaying to the user"<<endl;
    }
    bool complete_ride(){
        int temp_lat=10;
        int temp_lng=56;
        // Here we will be calculating the distance using request object and the current location 

        Location loc=req.get_location();
        int src_lat=loc.get_lat();
        int src_lng=loc.get_lng();
        
        distance = abs(src_lat-temp_lat) +abs(src_lng-temp_lng);    
        amount=distance*20;
        return s->execute_next(req,amount);

    }

    ~Ride(){
        delete s;
    }

};



class Ride_factory{
    
    public:
    Ride* get_ride(Request req){
        Ride *temp=new Ride();
        temp->start_ride(req);
        return temp;
    }

};
enum state{idle,busy};




class Driver{
    Location location;
    string name;
    Ride* ride=nullptr;
    state state=idle;
    Request*  current_request=nullptr;
    Ride_factory rf;
    public:
    Driver(){};
    Driver(string n){
        name=n;
    }

    bool handle_request(Request req){
        if(state==busy){
            return false;
        }
        current_request=new Request(req);
        ride=rf.get_ride(req);
        // In future we can add many types of rides we want
        state=busy;
        return true;

    }
    Location get_location(){
        location.set_location(rand()%(200-0+1),rand()%(200-0+1));

        return location;
    }

    bool end_ride(){
        if(state==idle){return false;}

        cout<<"ending ride"<<endl;
        bool iscomplete= ride->complete_ride();
        if(iscomplete){
            delete current_request;
            delete ride;
            current_request=nullptr;
            state=idle;
            return true;
        }
        return false;
     
    }
    string get_name(){
        return name;
    }


};


class Driver_Factory{
    private:
        Driver_Factory(){}
    
    public:
    Driver_Factory(const Driver_Factory&) = delete;
    Driver_Factory& operator=(const Driver_Factory&)=delete;

    static Driver_Factory& getInstance(){
        static Driver_Factory instance;
        return instance;
    }

    Driver* get_driver(string name){
        return  new Driver(name);     
    }
    
};



class strategy {
public:
    virtual void get_order(vector<Driver*>& drivers, Request req) = 0;
    virtual ~strategy() = default;
};


class shortest_radius : public strategy {
public:

    void get_order(vector<Driver*>& drivers, Request req) override {

        Location userLoc = req.get_location();

        int user_lat = userLoc.get_lat();
        int user_lng = userLoc.get_lng();

        sort(drivers.begin(), drivers.end(),
            [user_lat, user_lng](Driver* d1, Driver* d2) {

                Location loc1 = d1->get_location();
                Location loc2 = d2->get_location();

                int driver1_lat = loc1.get_lat();
                int driver1_lng = loc1.get_lng();

                int driver2_lat = loc2.get_lat();
                int driver2_lng = loc2.get_lng();

                int dist1 =
                    abs(driver1_lat - user_lat) +
                    abs(driver1_lng - user_lng);

                int dist2 =
                    abs(driver2_lat - user_lat) +
                    abs(driver2_lng - user_lng);

                return dist1 < dist2;
            });
    }
};


class less_traffic : public strategy {
public:

 void get_order(vector<Driver*>& drivers, Request req) override {

        Location userLoc = req.get_location();

        int user_lat = userLoc.get_lat();
        int user_lng = userLoc.get_lng();

        sort(drivers.begin(), drivers.end(),
            [user_lat, user_lng](Driver* d1, Driver* d2) {

                Location loc1 = d1->get_location();
                Location loc2 = d2->get_location();

                int driver1_lat = loc1.get_lat();
                int driver1_lng = loc1.get_lng();

                int driver2_lat = loc2.get_lat();
                int driver2_lng = loc2.get_lng();

                int dist1 =
                    abs(driver1_lat - user_lat) +
                    abs(driver1_lng - user_lng);

                int dist2 =
                    abs(driver2_lat - user_lat) +
                    abs(driver2_lng - user_lng);

                return dist1 < dist2;
            });
    }
};



class Driver_manager{
    vector<Driver* > drivers;
    strategy* s=new shortest_radius();

    Driver_manager(){}
    
    public:
    Driver_manager(const Driver_manager&) = delete;
    Driver_manager& operator=(const Driver_manager&)=delete;

    static Driver_manager& getInstance(){
        static Driver_manager instance;
        return instance;
    }


   
    void add_driver(string name){
       Driver_Factory& df=Driver_Factory::getInstance();
        Driver* d=df.get_driver(name);
        drivers.push_back(d);
        
    }

    void remove_driver(string name){
        for(int i=0;i<drivers.size();i++){
            if(drivers.at(i)->get_name()==name){
                delete drivers[i];
                drivers.erase(drivers.begin()+i);
                break;
            }
        }
    }

    void set_strategy(strategy* str){
        delete s;
        s=str;
    }

    strategy* get_strategy(){
        return s;
    }

    bool notify(Request req){
        s->get_order(drivers,req);
        for(Driver* d:drivers){
            if(d->handle_request(req)){
                cout<<"Driver assigned"<<endl;
                return true;
            }
        }
        return false;
    }

    ~Driver_manager(){
        for(Driver* d:drivers){
            delete d;
        }
        delete s;
    }

};

class Main_manager{

    Main_manager(){}
    
    public:
    Main_manager(const Main_manager&) = delete;
    Main_manager& operator=(const Main_manager&)=delete;

    static Main_manager& getInstance(){
        static Main_manager instance;
        return instance;
    }
    
    bool Request_ride(Request req){
        Driver_manager& dm=Driver_manager::getInstance();
        cout<<"Ride requested"<<endl;
        return dm.notify(req);
    }
};

class service{
    public:
    bool find_ride(Request req){
        Main_manager& mm=Main_manager::getInstance();
        return mm.Request_ride(req);
    }
};

class controller{
    service s;
    public:
    void execute_service(Request req){
        if(s.find_ride(req)){
            cout<<"Ride confirmed. Notification sent"<<endl;
        }else{
            cout<<"Driver not avilable. please try after some time"<<endl;
        }
    }
    
};

class client{
    controller c;
    Request* req=nullptr;
    public:
    void set_request(string name,string to, string from, Location l){
        req=new Request(name,to,from,l);
    }
    void request_ride(){
        c.execute_service(*req);
    }
};





int main() {

    Driver_manager& dm = Driver_manager::getInstance();

    dm.add_driver("Driver_A");
    dm.add_driver("Driver_B");
    dm.add_driver("Driver_C");

    client c;

    Location userLocation(50, 50);

    c.set_request(
        "Samarth",       // user name
        "Airport",       // destination
        "Home",          // source
        userLocation     // user's current location
    );

    c.request_ride();

    cout << "\n--- Ending Ride ---\n";
    
    return 0;
}